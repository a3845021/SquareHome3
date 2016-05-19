#include "SceneManager.h"
#include "MenuLayer.h"
#include "PlayLayer.h"


void SceneManager::createScene(){//初始化场景
	startScene = Scene::create();
	auto menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
	log("SceneManager::createScene called");

}
void SceneManager::toGameScene(){//跳转到开始场景
	gameScene = PlayLayer::scene();
	Director::getInstance()->replaceScene(gameScene);
	log("adasdasda----");
}