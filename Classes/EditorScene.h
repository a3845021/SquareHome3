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

	void setTouchEvent();//�����¼����������
	bool onTouchBegan(Touch* touch, Event* event);//������ʼʱ�Ļص���������¼������ʼ������
	void onTouchEnded(Touch* touch, Event* event);//��������ʱ�Ļص���������¼���������������
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