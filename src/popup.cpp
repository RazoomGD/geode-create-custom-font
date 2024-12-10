#include "Font.hpp"

class Dragger : public CCNode {
private:
    Ref<CCNode> m_controlled;
    Ref<CCNode> m_dragZone;

    bool m_grabbed;
    CCPoint m_startPos;

public:
    static Dragger* create(CCNode* dragZone, CCNode* controlled) {
        auto ret = new Dragger();
        ret->m_controlled = controlled;
        ret->m_dragZone = dragZone;
        ret->addChild(dragZone);
        return ret;
    }

    /**
     * Try to grab the controlled node
     * (should be called on touch begin/move/end)
     * @return true - is grabbed,
     * @return false - otherwise
     */
    bool onTouch(CCTouch* touch, bool isBegin, bool isEnd) {
        if (isBegin || isEnd) m_grabbed = false;
        if (isBegin) {
            auto pos = m_dragZone->convertToNodeSpace(touch->getLocation()); // coordinates in drag_zone
            pos *= m_dragZone->getScale();
            auto rect = m_dragZone->boundingBox();
            if (pos.x > 0 && pos.y > 0 && pos.x < rect.size.width && pos.y < rect.size.height) {
                m_grabbed = true;
                m_startPos = m_controlled->getPosition();
                return true;
            }
        } else if (m_grabbed) { // touch move when the window is grabbed
            m_controlled->setPosition(m_startPos + (touch->getLocation() - touch->getStartLocation()));
            return true;
        }
        return false;
    }
};


// specify parameters for the setup function in the Popup<...> template
class MyPopup : public Popup<std::string const&> {
protected:

    Dragger* m_dragger;
    TextInput* m_textArea;


    bool setup(std::string const& value) override {
        this->setOpacity(0);
        this->setTitle("Hi mom!");

        // add drag zone 
        auto dragZone = CCMenuItemSpriteExtra::create(ButtonSprite::create("Drag Zone"), this, nullptr);
        dragZone->setAnchorPoint(ccp(1,1));
        dragZone->setScale(0.4f);
        m_dragger = Dragger::create(dragZone, m_mainLayer);
        m_mainLayer->addChildAtPosition(m_dragger, Anchor::TopRight);

        // add text input
        m_textArea = TextInput::create(200, "hello\nnew\nline", "chatFont.fnt");
        m_textArea->getInputNode()->setAllowedChars(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?:;)(/\\\"\'`*=+-_%[]<>|@&^#$~");
        m_textArea->setTextAlign(TextInputAlign::Left);
        // m_textArea->setCallback([this](const std::string& str) {
        //     auto str2 = std::regex_replace(str, std::regex(R"(\\n)"), "\n");
            // log::debug("file: popup.hpp:71 - : {}", str2);
        //     this->m_textArea->setString(str2, false);
        // });
         
        m_mainLayer->addChildAtPosition(m_textArea, Anchor::Center, {0, 20});

        auto font = Font("font 1", 10, 10);
        auto symA = Symbol("1,508,2,67.5,3,817.75,20,2,64,1,155,3,21,2;1,508,2,65,3,770.25,20,2,64,1,155,3,6,270,21,2;1,508,2,65,3,785.25,20,2,64,1,155,3,6,270,21,2;1,508,2,67.5,3,797.75,20,2,64,1,155,3,6,180,21,2;1,508,2,65,3,800.25,20,2,64,1,155,3,6,270,21,2;1,508,2,65,3,815.25,20,2,64,1,155,3,6,270,21,2;1,508,2,85,3,800.25,20,2,64,1,155,3,6,90,21,2;1,508,2,85,3,785.25,20,2,64,1,155,3,6,90,21,2;1,508,2,85,3,815.25,20,2,64,1,155,3,6,90,21,2;1,508,2,82.5,3,797.75,20,2,64,1,155,3,6,180,21,2;1,508,2,82.5,3,817.75,20,2,64,1,155,3,21,2;1,508,2,85,3,770.25,20,2,64,1,155,3,6,90,21,2;1,2895,2,75,3,793,20,1,155,5,128,1.177,129,2.344;");
        auto symB = Symbol("1,508,2,155,3,785.25,20,2,64,1,155,3,6,270,21,2;1,508,2,157.5,3,767.75,20,2,64,1,155,3,6,180,21,2;1,508,2,172.5,3,797.75,20,2,64,1,155,3,6,180,21,2;1,508,2,175,3,785.25,20,2,64,1,155,3,6,90,21,2;1,508,2,155,3,800.25,20,2,64,1,155,3,6,270,21,2;1,508,2,155,3,770.25,20,2,64,1,155,3,6,270,21,2;1,508,2,171.12,3,775.87,5,1,20,2,64,1,155,3,6,-45,21,2;1,508,2,175,3,800.25,20,2,64,1,155,3,6,90,21,2;1,508,2,166.88,3,813.87,20,2,64,1,155,3,6,45,21,2;1,508,2,157.5,3,817.75,20,2,64,1,155,3,21,2;1,508,2,166.88,3,771.63,5,1,20,2,64,1,155,3,6,-45,21,2;1,508,2,155,3,815.25,20,2,64,1,155,3,6,270,21,2;1,508,2,171.12,3,809.63,20,2,64,1,155,3,6,45,21,2;1,508,2,157.5,3,797.75,20,2,64,1,155,3,6,180,21,2;1,2895,2,165,3,793,20,1,155,5,128,1.177,129,2.344;");
        auto symC = Symbol("1,508,2,247.5,3,767.75,20,2,64,1,155,3,6,180,21,2;1,508,2,247.5,3,817.75,20,2,64,1,155,3,21,2;1,508,2,262.5,3,767.75,20,2,64,1,155,3,6,180,21,2;1,508,2,245,3,785.25,20,2,64,1,155,3,6,270,21,2;1,508,2,245,3,770.25,20,2,64,1,155,3,6,270,21,2;1,508,2,245,3,800.25,20,2,64,1,155,3,6,270,21,2;1,508,2,245,3,815.25,20,2,64,1,155,3,6,270,21,2;1,508,2,262.5,3,817.75,20,2,64,1,155,3,21,2;1,2895,2,255,3,793,20,1,155,5,128,1.177,129,2.344;");
        font.addSymbol('a', symA);
        font.addSymbol('b', symB);
        font.addSymbol('c', symC);

        auto txt = font.renderText("abcabc");
        m_mainLayer->addChildAtPosition(txt, Anchor::Center, {0, -40});


        return true;
    }


public:

    static MyPopup* create(std::string const& text) {
        auto ret = new MyPopup();
        if (ret->initAnchored(240.f, 160.f, text)) {
            ret->autorelease();
            return ret;
        }

        delete ret;
        return nullptr;
    }

    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        log::debug("file: popup.cpp:108 - : AAAA"); // todo: wtf not working
        if (m_dragger->onTouch(touch, true, false)) return true;
        log::debug("file: popup.cpp:108 - : BBBB");
        return Popup::ccTouchBegan(touch, event);
        // return false
    }

    void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        if (m_dragger->onTouch(touch, false, false)) return;
        Popup::ccTouchMoved(touch, event);
    }

    void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        if (m_dragger->onTouch(touch, false, true)) return;
        Popup::ccTouchEnded(touch, event);
    }


};
