#pragma once
#include<iostream>
#include"cocos2d.h"

USING_NS_CC;


class SceneManager
{
public:
	Scene * startScene;
	Scene * gameScene;

	void createScene();//��ʼ������
	void toGameScene();//��ת����ʼ����

};

