/*
 * MenuScene.h
 *
 *  Created on: 2014��12��14��
 *      Author: mark_chen
 */


#include "cocos2d.h"
#include "MainScene.h"
USING_NS_CC;

class WelPage :
	public cocos2d::Layer
{
public:
	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(WelPage);
	WelPage();
	virtual ~WelPage();
	void start();
};

