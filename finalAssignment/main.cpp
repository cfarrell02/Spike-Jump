
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include "level.hpp"
#include "textureHolder.hpp"

// Here is a small helper for you! Have a look.
using namespace sf;

const int BLOCK_WIDTH = 64;

void populateLevels(Level* level);

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
     Level* level;
    // Start the game loop
    while (window.isOpen())
    {
        populateLevels(level);
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

        // Clear screen
//        map<Vector2i,Block>::iterator iter;
//        map<Vector2i,Block>* map = level->getBlocks();
//        for(iter = map->begin() ; iter != map->end() ; ++ iter){
//            window.draw(iter->second.getSprite());
//        }


        // Update the window
        window.display();
    }

    return 0;
}

void populateLevels(Level* level){
    const int levelWidth = 500, levelHeight = 500;
    int levelData[levelWidth][levelHeight] = {{1,0,1,1,1,1,0,0,0,0},{1,0,0,1,1,1,1,1,0,0}};
    cout<<"Hello";
    map<Vector2i,Block> map;
    for(int x = 0 ; x< levelWidth ;x+=BLOCK_WIDTH){
        for(int y = 0; y< levelHeight ; y+=BLOCK_WIDTH){
            std::cout<<levelData[x][y];
            if(levelData[x][y] == 0) break;
            Block block(TextureHolder::GetTexture("../Resources/Images/Block.png"), Vector2i(x,y),Vector2i(BLOCK_WIDTH,BLOCK_WIDTH),true);
            map.insert(pair<Vector2i,Block>(Vector2i(x,y),block));
        }
        cout<<endl;
    }
    level = new Level(map);
}
