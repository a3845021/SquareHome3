#include "MenuLayer.h"

MenuLayer::MenuLayer()
{
}


MenuLayer::~MenuLayer()
{
}
bool MenuLayer::init(){
	Node * node = CSLoader::createNode("studio/MainScene.csb");
	Layout * layout = static_cast<Layout *>(node->getChildByTag(120));
	for (int i = 0; i < 2; i++){
		log(" MenuLayer::init called%d",i);

		Button * button = static_cast<Button*>(layout->getChildByTag(121 + i));
	//ImageView * button = static_cast<ImageView*>(layout->getChildByTag(121));

		button->addTouchEventListener(CC_CALLBACK_2(MenuLayer::touchCallBack, this));
	}
	this->addChild(node);

	//tsm->toGameScene();
	return true;
}

void MenuLayer::touchCallBack(Ref * sender, Widget::TouchEventType controlEvent){
		log(" MenuLayer::touchCallBack called");
	if (controlEvent == Widget::TouchEventType::ENDED){
		auto button = static_cast<Button*> (sender);
		tsm->toGameScene();
	}
}