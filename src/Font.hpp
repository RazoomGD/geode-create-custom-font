#pragma once

#include <map>

#include "Symbol.hpp"


class Font {
protected:
    std::string m_name; // font name
    float m_vDist; // vertical gap between letters
    float m_hDist; // horizontal gap between letters
    std::map<char, Symbol> m_font; // symbol mappings
    
public:
    Font(std::string name, float vDist, float hDist);

    void addSymbol(char c, Symbol& s);

    CCNode* renderText(std::string text);
};