
//
//  Created by Cian Farrell on 22/11/2022.
//

#include "textureHolder.hpp"
#include <assert.h>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder(){
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename){
    auto& m = m_s_Instance->m_Textures;
    
    auto keyValuePair = m.find(filename);
    
    if(keyValuePair != m.end()){
        return keyValuePair ->second;
    }
    else{
        auto& texture = m[filename];
        cout<<"Fetching new texture\n";
        
        texture.loadFromFile(filename);
        
        return texture;
    }
}


