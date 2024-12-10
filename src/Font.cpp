#include "Font.hpp"

Font::Font(std::string name, float vDist, float hDist) {
    m_name = name;
    m_vDist = vDist;
    m_hDist = hDist;
}

void Font::addSymbol(char c, Symbol& s) {
    m_font.insert_or_assign(c, s);
}

CCNode* Font::renderText(std::string text) {
    auto base = CCNode::create();
    float pos = 0;
    for (char c : text) {
        auto it = m_font.find(c);
        if (it != m_font.end()) {
            Symbol sym = (*it).second;
            CCNode* symSpr = sym.render();
            base->addChildAtPosition(symSpr, Anchor::Center, {pos, 0});
            pos += sym.m_width + m_hDist;
        } else {
            // todo: add code
        }
    }
    return base;
}