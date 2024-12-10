#include "Symbol.hpp"

Symbol::Symbol(std::string str) {
    // find template obj
    std::string obj;
    std::stringstream ssPre(str);
    struct {double x, y;} anchor;
    bool foundTemplate = false;
    while (std::getline(ssPre, obj, ';')) {
        if (!obj.starts_with("1,2895,")) continue;
        std::stringstream ssMid(obj);
        std::string key, val;
        double x = 0.0, y = 0.0, scaleOld = 1.0, scaleX = 1.0, scaleY = 1.0, angle = 0.0; 
        // analyze object keys one by one
        while (std::getline(ssMid, key, ',') && std::getline(ssMid, val, ',')) {
            int key1 = std::atoi(key.c_str());
            double val1 = std::atof(val.c_str());
            switch (key1) {
                case 2: x = val1; break;
                case 3: y = val1; break;
                case 6: angle = val1; break;
                case 32: scaleOld = val1; break;
                case 128: scaleX = val1; break;
                case 129: scaleY = val1; break;
                default: break;
            }
        }
        if (scaleOld != 1.0) {
            scaleX = scaleY = scaleOld;
        }

        // todo: what if template block is rotated non 90
        if ((int) std::round(angle) % 180 == 90) {
            std::swap(scaleX, scaleY);
        }

        anchor.x = x - 30 / 2 * scaleX;
        anchor.y = y - 30 / 2 * scaleY;
        m_width = 30 * scaleX;
        
        foundTemplate = true;
        break; 
    }
    if (!foundTemplate) {
        // todo: add code
    }


    // analyze objects one by one
    std::stringstream ssOut;
    
    std::regex re(R"(1,([\.\d]+),2,([\.\d]+),3,([\.\d]+)([^;]*))");
    std::sregex_iterator it(str.begin(), str.end(), re);
    std::sregex_iterator end;
    for (; it != end; it++) {
        std::smatch match = *it;
        short id = std::atoi(match[1].str().c_str());
        double xPos = std::atof(match[2].str().c_str());
        double yPos = std::atof(match[3].str().c_str());
        xPos -= anchor.x;
        yPos -= anchor.y;
        std::string other = match[4].str();
        if (id == 2895) { // template obj
            m_templateObj = std::string("1,2895,2,") + std::to_string(xPos) + std::string(",3,") + std::to_string(yPos) + other;
        } else {
            ssOut << "1," << id << ",2," << xPos << ",3," << yPos << other << ";";
        }
    }

    m_objString = ssOut.str();

    // todo: empty string or string with only template object results in crash
}

CCNode* Symbol::render() {
    auto editor = LevelEditorLayer::get();
    auto base = CCNode::create();
    // https://github.com/FireMario211/Object-Workshop/blob/dad5b6aa4d9190caaf513fe0abea6eb3cbfbcb22/src/nodes/ExtPreviewBG.cpp#L19
    if (m_objString.length() > 0) {
        auto objArray = CCArray::create();
        auto objSprite = editor->m_editorUI->spriteFromObjectString(
            m_objString, false, false, 1000, objArray, nullptr, nullptr);
        editor->updateObjectColors(objArray);
        base->addChildAtPosition(objSprite, Anchor::Center, {0,0});
    }
    return base;
}