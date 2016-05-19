#include "SceneManager.h"
#include "MenuLayer.h"
#include "PlayLayer.h"


void SceneManager::createScene(){//��ʼ������
	startScene = Scene::create();
	auto menuLayer = MenuLayer::create();
	menuLayer->tsm = this;
	startScene->addChild(menuLayer);
	log("SceneManager::createScene called");

}
void SceneManager::toGameScene(){//��ת����ʼ����
	gameScene = PlayLayer::scene();
	Director::getInstance()->replaceScene(gameScene);
	log("adasdasda----");
}