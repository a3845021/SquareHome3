#pragma once
#include<iostream>
#include"cocos2d.h"

USING_NS_CC;


class SceneManager
{
public:
	Scene * startScene;
	Scene * gameScene;

	void createScene();//初始化场景
	void toGameScene();//跳转到开始场景

};

