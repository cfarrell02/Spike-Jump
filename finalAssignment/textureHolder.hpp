//
//  textureHolder.hpp
//  ZombieArena
//
//  Created by Cian Farrell on 22/11/2022.
//

#ifndef textureHolder_hpp
#define textureHolder_hpp

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

class TextureHolder{
public:
    TextureHolder();
    static sf::Texture& GetTexture(std::string const& filename);
    
private:
    std::map<std::string, sf::Texture> m_Textures;
    static TextureHolder* m_s_Instance;
};

#endif /* textureHolder_hpp */
