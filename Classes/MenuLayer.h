#pragma once
#include "cocos2d.h"
#include "SceneManager.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

class MenuLayer :
	public Layer
{
public:
	MenuLayer();
	~MenuLayer();

	CREATE_FUNC(MenuLayer);
	virtual bool init();
	void touchCallBack(Ref * sender, Widget::TouchEventType controlEvent);
public:
	SceneManager * tsm;

};

