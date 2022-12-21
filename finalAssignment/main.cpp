

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "level.hpp"
#include "textureHolder.hpp"
#include "character.hpp"
#include <fstream>
#include <string>
#include <sstream>

using namespace sf;

const int BLOCK_WIDTH = 64; // Pixels
const int CAMERA_DEADZONE = 80;
const int MAX_LIVES = 3;
const float INTERPOLATION_SPEED = .05;
void populateLevel(Level*& level,Character& character,RenderWindow& window, int levelNumber);
vector<vector<int>> retrieveLevelData(string filePath);
TextureHolder textureHolder;

int main(int, char const**)
{
    // Create the main window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width/2;
    resolution.y = VideoMode::getDesktopMode().height/2;
    
    RenderWindow window(VideoMode(resolution.x,resolution.y),"Spike Jump");
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    Level* level;
    
    // Start the game loop
    Clock clock;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Time gameTimeTotal;
    int levelIndex = 1;
    const int finalLevelIndex = 4;
    Character character(MAX_LIVES, 300);
    populateLevel(level , character, window,  levelIndex);
    
    
    //For the home/game over screen
    View hudView(FloatRect (0,0,resolution.x,resolution.y));
    Font font;
    font.loadFromFile("../Resources/Fonts/sansation.ttf");
    
    Text pausedText;
    pausedText.setFont(font);
    pausedText.setCharacterSize(155);
    pausedText.setFillColor(Color::White);
    pausedText.setString("Press Enter \nto continue");
    FloatRect pausedRect = pausedText.getLocalBounds();
    pausedText.setOrigin(pausedRect.left+pausedRect.width/2.0f, pausedRect.top+pausedRect.height/2.0f);
    pausedText.setPosition(resolution.x/2, resolution.y/2);
    
    Text deathText;
    deathText.setFont(font);
    deathText.setCharacterSize(155);
    deathText.setFillColor(Color::Red);
    deathText.setString("You Died");
    FloatRect deathRect = deathText.getLocalBounds();
    deathText.setOrigin(deathRect.left+deathRect.width/2.0f, deathRect.top+deathRect.height/2.0f);
    deathText.setPosition(resolution.x/2, resolution.y/2);
    
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(155);
    gameOverText.setFillColor(Color::White);
    gameOverText.setString("Game Over!\nPress enter to exit!");
    FloatRect gameOverRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverRect.left+gameOverRect.width/2.0f, gameOverRect.top+gameOverRect.height/2.0f);
    gameOverText.setPosition(resolution.x/2, resolution.y/2);
    // Score
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(55);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(resolution.x*.02, resolution.y*.02);
    scoreText.setString("Score: ");
    
    // Lives
    Text liveText;
    liveText.setFont(font);
    liveText.setCharacterSize(55);
    liveText.setFillColor(Color::White);
    liveText.setPosition(resolution.x*.87, resolution.y*.02);
    liveText.setString("Lives: ");
    
    //Background
    Sprite background(TextureHolder::GetTexture("../Resources/Images/greywall.jpg"));
    background.setPosition(0, 0);
    background.setScale(resolution.x/1200, resolution.y/800);
    
    //SFX
    SoundBuffer jumpBuffer, coinBuffer, deathBuffer, musicBuffer;
    jumpBuffer.loadFromFile("../Resources/Sounds/jump.wav");
    coinBuffer.loadFromFile("../Resources/Sounds/coinCollect.wav");
    deathBuffer.loadFromFile("../Resources/Sounds/death.wav");
    musicBuffer.loadFromFile("../Resources/Sounds/music.wav");
    Sound jumpSound, deathSound, coinSound, musicSound;
    jumpSound.setBuffer(jumpBuffer);
    deathSound.setBuffer(deathBuffer);
    coinSound.setBuffer(coinBuffer);
    musicSound.setBuffer(musicBuffer);
    musicSound.setLoop(true);
    musicSound.play();
    
    
    
    
    int scoreFromPrevLevels = 0;
    
    bool paused = true, dead = false,gameOver = false, spacePressed = false;
    int framesSinceLastHUDUpdate = 0;
    
    int fpsMeasurementFrameInterval = 10;
    
    while (window.isOpen())
    {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: pause
            if(event.type == sf::Event::KeyPressed){
                if(!dead){
                    if (event.key.code == sf::Keyboard::Escape) {
                        paused = !paused; // Toggle pause bool
                    }
                    else if(event.key.code == sf::Keyboard::Enter){
                        paused = false; //Enter unpauses
                    }
                }else{
                    if(event.key.code == sf::Keyboard::Enter){ // Reset everything
                        paused = false;
                        dead = false;
                        character.resetLives();
                        character.resetScore();
                    }
                }
                if(gameOver && event.key.code == Keyboard::Enter){
                    return 0;
                }
                
            }
        }

        if(!paused && !dead  && !gameOver){
            //If playing :
                Block* touchingBlock = level->getIntersectingBlockBelow(character.getPosition()); // Block that is being stood on
                bool touchingGround = touchingBlock != nullptr; // is not falling?
                Block* blockAbove = level->getIntersectingBlockAbove(character.getPosition());
                bool canMoveUp = blockAbove == nullptr;
                Block* intersectingBlock = level->getIntersectingBlock(character.getPosition());
                if(intersectingBlock != nullptr ){
                    //Handling interactions with items.
                    if( intersectingBlock->m_LevelExit){
                        if(finalLevelIndex == levelIndex){
                            //End game stuff here
                            
                            cout<<"Game over!!\n";
                            gameOver = true;
                        }else{
                            cout<<"Loading next level!!\n";
                            scoreFromPrevLevels += character.getCoinCount();
                            character.resetScore();
                            delete level;
                            populateLevel(level, character, window, ++levelIndex);
                            mainView.setCenter(character.getPosition().left, character.getPosition().top);
                        }
                    }else if(intersectingBlock->m_isHazard){
                        character.removeLife();
                        character.resetScore();
                        deathSound.play();
                        cout<<character.getLives()<<" Lives remaining\n";
                        populateLevel(level, character, window, levelIndex);
                    }else if(intersectingBlock->isCoin()){
                        character.addCoin();
                        coinSound.play();
                        cout<<character.getCoinCount()+scoreFromPrevLevels<<" coins collected\n";
                        intersectingBlock->remove();
                    }
                }
                Time dt = clock.restart();
                gameTimeTotal += dt;
                float dtAsSeconds = dt.asSeconds();
                
                //character Movement
                if(Keyboard::isKeyPressed(Keyboard::A) && level->canMoveLeft(character.getPosition()))
                    character.moveLeft();
                else character.stopLeft();
                if(Keyboard::isKeyPressed(Keyboard::D) && level->canMoveRight(character.getPosition()))
                    character.moveRight();
                else character.stopRight();
                
                if(Keyboard::isKeyPressed(Keyboard::Space) && !spacePressed){
                    //Handles jump
                    if(touchingGround)
                    jumpSound.play();
                    character.jump(300*dtAsSeconds, touchingGround);
                    spacePressed = true;
                }
                if(!Keyboard::isKeyPressed(Keyboard::Space)) spacePressed = false;
                character.update(dtAsSeconds, touchingGround, canMoveUp);
                //camera movement
                Vector2f position(character.getPosition().left,character.getPosition().top) ;
                if(std::abs(mainView.getCenter().x - position.x) > CAMERA_DEADZONE ||
                   std::abs(mainView.getCenter().y - position.y) > CAMERA_DEADZONE){
                    Vector2f interpolatedPos = mainView.getCenter() + (position - mainView.getCenter())*INTERPOLATION_SPEED;
                    mainView.setCenter(interpolatedPos);
                }
                
                framesSinceLastHUDUpdate++;
                
                //HUD Updates
                if(framesSinceLastHUDUpdate > fpsMeasurementFrameInterval){
                    std::stringstream ssLives;
                    std::stringstream ssScore;
                    
                    ssLives << "Lives: " << character.getLives();
                    liveText.setString(ssLives.str());
                    ssScore << "Score: " << character.getCoinCount()+scoreFromPrevLevels;
                    scoreText.setString(ssScore.str());
                    framesSinceLastHUDUpdate = 0;
                    //Temp death condition
                    if(character.getLives() <= 0){
                        dead = true;
                    }
                }
            }

        
        //Draw Sprites
        
        if(!paused){
            if(!dead){
                if(!gameOver){
                    window.draw(background);
                    window.setView(mainView);
                    window.draw(character.getSprite());
                    vector<vector<Block*>> blocks = level ->getBlocks();
                    for(int x = 0; x< blocks.size();++x){
                        for(int y = 0 ; y< blocks.at(x).size();++y){
                            //if(blocks->at(x).at(y).m_MoveDirection==0)
                            blocks.at(x).at(y)->update();
                            window.draw((blocks.at(x)).at(y)->getSprite());
                        }
                    }
                    //HUD ELEMENTS
                    window.setView(hudView);
                    window.draw(scoreText);
                    window.draw(liveText);
                }else{ //gameover
                    window.draw(background);
                    window.draw(gameOverText);
                }
            }else{ // dead
                window.clear();
                window.draw(deathText);
            }
        }else{ // paused
            window.draw(background);
            window.draw(pausedText);
        }
        // Update the window
        window.display();
        
    }
    delete level;
    level = nullptr;

    return 0;
}

void populateLevel(Level*& level,Character& character, RenderWindow& window, int levelNumber){
    
    // Initialize stringstream object with file path for level data file
    std::stringstream ss;
    ss<<"../Resources/Levels/level"<<levelNumber<<".txt";

    // Seed random number generator with current time
    srand((int) time(0));
    // Read level data from file and store in 2D vector of integers
    vector<vector<int>> levelData = retrieveLevelData(ss.str());
    
    

    // Initialize 2D vector of Block pointers
    vector<vector<Block*>> map;

    // Iterate over level data vector
    for(int x = 0 ; x<levelData.size() ;x+=1){
        // Initialize new row in map vector
        map.push_back(vector<Block*>());
        
        // Iterate over row in level data vector
        
        //0 - Blankspace, 1 - Greyblock, 2 - Redblock (temporary), 3 - Level exit, 4 - spike, 5 - coin, 9- playerspawn
        for(int y = 0; y< levelData[x].size() ; y+=1){
            // Generate random index between 1 and 3
            int index = (rand()%3) + 1;

            // Determine type of block to create based on value in level data vector
            if(levelData[x][y] == 0 || levelData[x][y] == 9){
                // Create new Block with default texture and collides flag set to false
                Block* block = new Block(TextureHolder::GetTexture(""),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false);
                // Add Block to map vector
                map[x].push_back(block);

                // If value in level data vector is 9, set character's spawn position
                if(levelData[x][y] == 9)
                    character.spawn(Vector2i(x*BLOCK_WIDTH,y*BLOCK_WIDTH),BLOCK_WIDTH);
            }
            // Create new temporary Block with different texture and collides flag set to true
            else if(levelData[x][y] == 2){
                Block* block = new Block(TextureHolder::GetTexture("../Resources/Images/redBlock1.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),true,1);
                map[x].push_back(block);
            }
            // Create new Block with different texture, exit flag set to true, and collides flag set to false
            else if(levelData[x][y] == 3){
                Block* block = new Block(TextureHolder::GetTexture("../Resources/Images/levelExit.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false,-1,true);
                map[x].push_back(block);
            }
            else if(levelData[x][y] == 4){
                stringstream ss;
                ss << "../Resources/Images/spikes"<<index<<".png";
                Block* block = new Block(TextureHolder::GetTexture(ss.str()),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false,-1,false,true);
                map[x].push_back(block);
            }
            else if(levelData[x][y] == 5){
                Block* block = new Block(TextureHolder::GetTexture("../Resources/Images/coin.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false,-1,false,false,true);
                map[x].push_back(block);
            }
            else{
                stringstream url;
                url<<"../Resources/Images/greyBlock"<<index<<".png";
                Block* block = new Block(TextureHolder::GetTexture(url.str()),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),true);
                map[x].push_back(block);
                
            }
            
        }
    }
    level = new Level(map);
}

vector<vector<int>> retrieveLevelData(string filePath) {
    std::ifstream myfile (filePath);
  vector<vector<int>> result;
  std::string myline;
    

  if ( myfile.is_open() ) {
    // Read the first line of the file
    std::getline (myfile, myline);

    // Create a vector of integers for each character in the line
    for (int i = 0; i < myline.size(); i++) {
      result.push_back(vector<int>());
    }

    // Iterate over the characters in the line
    for (int i = 0; i < myline.size(); i++) {
      // Add the character to the corresponding column of the result vector
      result.at(i).push_back(myline[i] - '0');
    }

    // Read the remaining lines of the file
    while (std::getline (myfile, myline)) {
      // Iterate over the characters in the line
      for (int i = 0; i < myline.size(); i++) {
        // Add the character to the corresponding column of the result vector
        result.at(i).push_back(myline[i] - '0');
      }
    }
  }

  return result;
}
