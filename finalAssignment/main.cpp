

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
    
    RenderWindow window(VideoMode(resolution.x,resolution.y),"Test Game");
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    Level* level;
    // Start the game loop

    

    Clock clock;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Time gameTimeTotal;
    Character character;
    int levelIndex = 1;
    populateLevel(level , character, window,  levelIndex);
    
    
    bool paused = false;
    
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

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        if(!paused){
            Block* touchingBlock = level->getIntersectingBlockBelow(character.getPosition());
            bool touchingGround = touchingBlock != nullptr;
            Block* intersectingBlock = level->getIntersectingBlock(character.getPosition());
            if(intersectingBlock != nullptr && intersectingBlock->m_LevelExit){
                cout<<"Loading next level!!\n";
                delete level;
                populateLevel(level, character, window, ++levelIndex);
            }
            Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            
            mouseScreenPosition = Mouse::getPosition(window);

            
            //character Movement
            if(Keyboard::isKeyPressed(Keyboard::A) && level->canMoveLeft(character.getPosition()))
                character.moveLeft();
            else character.stopLeft();
            if(Keyboard::isKeyPressed(Keyboard::D) && level->canMoveRight(character.getPosition()))
                character.moveRight();
            else character.stopRight();
            
            if(Keyboard::isKeyPressed(Keyboard::Space))
                character.jump(4, touchingGround);
            character.update(dtAsSeconds, mouseScreenPosition, touchingGround);
            //camera movement
            Vector2f position(character.getPosition().left,character.getPosition().top) ;
            if(std::abs(mainView.getCenter().x - position.x) > CAMERA_DEADZONE ||
               std::abs(mainView.getCenter().y - position.y) > CAMERA_DEADZONE){
                Vector2f interpolatedPos = mainView.getCenter() + (position - mainView.getCenter())*INTERPOLATION_SPEED;
                mainView.setCenter(interpolatedPos);
            }
            
            
            
        }
        
        

        //Draw Sprites
        window.clear();
    
        window.setView(mainView);
        //TODO:  Fix this part!!!!! <------
        window.draw(character.getSprite());
        vector<vector<Block*>> blocks = level ->getBlocks();
        for(int x = 0; x< blocks.size();++x){
            for(int y = 0 ; y< blocks.at(x).size();++y){
                //if(blocks->at(x).at(y).m_MoveDirection==0)
                blocks.at(x).at(y)->update();
                
                window.draw((blocks.at(x)).at(y)->getSprite());
            }
        }

        // Update the window
        window.display();
        
    }
    delete level;
    level = nullptr;

    return 0;
}

void populateLevel(Level*& level,Character& character, RenderWindow& window, int levelNumber){
    
    std::stringstream ss;
    ss<<"../Resources/Levels/level"<<levelNumber<<".txt";
    srand((int) time(0));

    vector<vector<int>> levelData = retrieveLevelData(ss.str());
    //*texture = TextureHolder::GetTexture("../Resources/Images/Block.png");
    vector<vector<Block*>> map;
    for(int x =	 0 ; x<levelData.size() ;x+=1){
        map.push_back(vector<Block*>());
        for(int y = 0; y< levelData[x].size() ; y+=1){
            int index = (rand()%3) + 1;
            if(levelData[x][y] == 0 || levelData[x][y] == 9){
                Block* block = new Block(TextureHolder::GetTexture(""),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false);
                map[x].push_back(block);
                if(levelData[x][y] == 9)
                    character.spawn(Vector2i(x*BLOCK_WIDTH,y*BLOCK_WIDTH),BLOCK_WIDTH,(Vector2f) window.getSize());
                
            }else if(levelData[x][y] == 2){
                Block* block = new Block(TextureHolder::GetTexture("../Resources/Images/redBlock1.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),true,1);
                map[x].push_back(block);
            }
            else if(levelData[x][y] == 3){
                Block* block = new Block(TextureHolder::GetTexture("../Resources/Images/levelExit.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false,-1,true);
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
