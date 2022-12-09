

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "level.hpp"
#include "textureHolder.hpp"


using namespace sf;

const int BLOCK_WIDTH = 64; // Pixels
const int levelWidth = 50, levelHeight = 50; // In Block Units
void populateLevels(Level*& level);
TextureHolder textureHolder;
int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML window");
    Level* level;
    // Start the game loop
    populateLevels(level);
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

        //Draw Sprites
        try{
        vector<vector<Block>>* blocks = level ->getBlocks();
        for(int x = 0; x< blocks->size();++x){
            for(int y = 0 ; y< blocks->at(x).size();++y){
                window.draw((blocks->at(x)).at(y).getSprite());
            }
        }
        }
        catch(exception& e){
            cerr<<e.what()<<endl;
            cerr<<"Exiting...";
            return -1;
        }


        // Update the window
        window.display();
    }

    return 0;
}

void populateLevels(Level*& level){

    int levelData[levelWidth][levelHeight] = {{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1},{0,0,0,0,0,1,1,1,1,1}};
    
    //*texture = TextureHolder::GetTexture("../Resources/Images/Block.png");
    vector<vector<Block>> map;
    for(int x =	 0 ; x< levelWidth ;x+=1){
        map.push_back(vector<Block>());
        for(int y = 0; y< levelHeight ; y+=1){
            
            if(levelData[x][y] == 0) continue;
            try{
                Block block(TextureHolder::GetTexture("/Users/cianfarrell/Documents/GitHub/finalAssignment/Resources/Images/Block.png"), Vector2i(x*BLOCK_WIDTH,y*BLOCK_WIDTH),Vector2i(BLOCK_WIDTH,BLOCK_WIDTH),true);

            map[x].push_back(block);
            } catch(exception e){
                cerr<<e.what()<<endl;
            }
        }
    }
    level = new Level(map);
}
