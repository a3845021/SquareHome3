/*
 * MenuScene.cpp
 *
 *  Created on: 2014Äê12ÔÂ14ÈÕ
 *      Author: mark_chen
 */

#include "WelPage.h"
#include "cocos2d.h"
#include "PlayLayer.h"

USING_NS_CC;
 
bool WelPage::init(){
	auto bg = Sprite::create("playui/welpage.png");
	bg->setPosition(ccp(720/2, 1280/2));
	this->addChild(bg);

	CCDelayTime * delayAction = CCDelayTime::create(3);
	CCCallFunc * callFunc = CCCallFunc::create(this, callfunc_selector(WelPage::start));
		//(pSelectorTarget, selector);
	this->runAction(CCSequence::createWithTwoActions(delayAction, callFunc));



	return true;
}

Scene* WelPage::scene(){
	Scene* scene = Scene::create();
	Layer* layer = WelPage::create();
	scene->addChild(layer);
	return scene;
}

WelPage::WelPage()
{
}


WelPage::~WelPage()
{
}
void WelPage::start(){
	//Director::sharedDirector()->replaceScene(1.0f,PlayLayer::scene());
	//Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayLayer::scene()));
	auto scene = MainScene::createScene();
	Director::getInstance()->replaceScene(CCTransitionProgressInOut::create(1.2, scene));
}

