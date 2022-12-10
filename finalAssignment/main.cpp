

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "level.hpp"
#include "textureHolder.hpp"
#include "character.hpp"


using namespace sf;

const int BLOCK_WIDTH = 64; // Pixels
void populateLevels(Level*& level);
TextureHolder textureHolder;

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1200, 600), "SFML window");
    Level* level;
    // Start the game loop
    populateLevels(level);
    

    Clock clock;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Time gameTimeTotal;
    Character character;
    character.spawn(Vector2i(160,100),BLOCK_WIDTH,(Vector2f) window.getSize());
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
            character.update(dtAsSeconds, mouseScreenPosition, touchingGround);
            
            //character Movement
            
            if(Keyboard::isKeyPressed(Keyboard::A))
                character.moveLeft();
            else character.stopLeft();
            if(Keyboard::isKeyPressed(Keyboard::D))
                character.moveRight();
            else character.stopRight();
            
            if(Keyboard::isKeyPressed(Keyboard::Space))
                character.jump(1,clock, touchingGround);
            
            
        }
        
        

        //Draw Sprites
        window.clear();
    
        
        
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

void populateLevels(Level*& level){

    vector<vector<int>> levelData = {{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1}};
    
    //*texture = TextureHolder::GetTexture("../Resources/Images/Block.png");
    vector<vector<Block>> map;
    for(int x =	 0 ; x<levelData.size() ;x+=1){
        map.push_back(vector<Block>());
        for(int y = 0; y< levelData[x].size() ; y+=1){
            
            if(levelData[x][y] == 0){
                Block block(TextureHolder::GetTexture(""),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),false);
                map[x].push_back(block);
                
            }else{
                Block block(TextureHolder::GetTexture("../Resources/Images/Block.png"),FloatRect(x*BLOCK_WIDTH,y*BLOCK_WIDTH,BLOCK_WIDTH,BLOCK_WIDTH),true);
                map[x].push_back(block);
                
            }
            
        }
    }
    level = new Level(map);
}
