#pragma once

#include "config.hpp"

#include <sstream>
#include <regex>
#include <cmath>

class Symbol {
protected:
    std::string m_objString;
    std::string m_templateObj;

public:
    float m_width;
    /**
     * Create symbol representation with object string
     * @param str object string
     */
    Symbol(std::string str);

    /**
     * Return CCNode with rendered symbol. (0,0) - coordinates of a left bottom corner of symbol box
     */
    CCNode* render();
};