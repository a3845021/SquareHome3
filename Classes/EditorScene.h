#pragma once

#include"cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;



class EditorScene : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(EditorScene);
	virtual bool init();

	void menuStartCallback(Ref *pSender);
	void menuSetCallback(Ref *pSender);
	void menuExitCallback(Ref *pSender);
	void menuEditorModeCallback(Ref *pSender);
	void menuClearCallback(Ref *pSender);


	void onChangedRadioButtonSelect(cocos2d::ui::RadioButton* radioButton, cocos2d::ui::RadioButton::EventType type);
	void initBackground();
	void initRadioButton();

	void setTouchEvent();//触摸事件的相关设置
	bool onTouchBegan(Touch* touch, Event* event);//触摸开始时的回调函数，记录触摸开始点坐标
	void onTouchEnded(Touch* touch, Event* event);//触摸结束时的回调函数，记录触摸结束点的坐标
	void onTouchMove(Touch * touch, Event*event);

	void onGoBack(Ref * sender);
	void clearAllSquare();
	EditorScene();
	~EditorScene();

private:
	cocos2d::ui::RadioButtonGroup* _radioButtonGroup;
	int RadioSelectState = 0;
	int squareType[13][17];
	static int xx;
	static int yy;
};