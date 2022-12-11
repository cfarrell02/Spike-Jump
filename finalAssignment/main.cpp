

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
void populateLevels(Level*& level, int levelNumber);
vector<vector<int>> retrieveLevelData(string filePath);
TextureHolder textureHolder;

int main(int, char const**)
{
    retrieveLevelData("../Resources/Levels/testLevel.txt");
    // Create the main window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x,resolution.y),"Test Game");
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    Level* level;
    // Start the game loop
    populateLevels(level , 1);
    

    Clock clock;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Time gameTimeTotal;
    Character character;
    character.spawn(Vector2i(250,100),BLOCK_WIDTH,(Vector2f) window.getSize());
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
            Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            
            mouseScreenPosition = Mouse::getPosition(window);
            bool touchingGround = level->isTouchingBlock(character.getPosition());
            
            //character Movement
            
            if(Keyboard::isKeyPressed(Keyboard::A) && level->canMoveLeft(character.getPosition()))
                character.moveLeft();
            else character.stopLeft();
            if(Keyboard::isKeyPressed(Keyboard::D) && level->canMoveRight(character.getPosition()))
                character.moveRight();
            else character.stopRight();
            
            if(Keyboard::isKeyPressed(Keyboard::Space))
                character.jump((resolution.y*5)/10000, touchingGround);
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
        
        vector<vector<Block>>* blocks = level ->getBlocks();
        for(int x = 0; x< blocks->size();++x){
            for(int y = 0 ; y< blocks->at(x).size();++y){
                window.draw((blocks->at(x)).at(y).getSprite());
            }
        }
        
        window.draw(character.getSprite());

        
        // Update the window
        window.display();
    }

    return 0;
}

void populateLevels(Level*& level, int levelNumber){
    
    std::stringstream ss;
    ss<<"../Resources/Levels/level"<<levelNumber<<".txt";

    vector<vector<int>> levelData = retrieveLevelData(ss.str());
    //*texture = TextureHolder::GetTexture("../Resources/Images/Block.png");
    vector<vector<Block>> map;
    for(int x =	 0 ; x<levelData.size() ;x+=1){
        map.push_back(vector<Block>());
        for(int y = 0; y< levelData[x].size() ; y+=1){
            if(levelData[x][y] == 0){
                Block block(TextureHolder::GetTexture(""),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false);
                map[x].push_back(block);
                
            }else{
                Block block(TextureHolder::GetTexture("../Resources/Images/greyBlock1.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),true);
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
