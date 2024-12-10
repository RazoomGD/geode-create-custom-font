#include "config.hpp"

#include <Geode/modify/EditorUI.hpp>

#include "popup.cpp"

class $modify(MyEditorUI, EditorUI) {
	
	$override
	bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer)) return false;

		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this, menu_selector(MyEditorUI::onDebugButton)
		);
		auto menu = this->getChildByID("undo-menu");
		menu->addChild(myButton);
		menu->updateLayout();
		
		
		return true;
	}

	void onDebugButton(CCObject*) {
		// FLAlertLayer::create("Geode", "Hello from my custom mod!", "OK")->show();
		auto popup = MyPopup::create("hello world");
		popup->show();

	}
};