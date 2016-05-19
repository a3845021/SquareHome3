#pragma once
#include "cocos2d.h"
#include "SquareSprite.h"
#include "GameDate.h"
#include "MainScene.h"
#include "GameOverScene.h"
using namespace CocosDenshion;
USING_NS_CC;


class PlayLayer :
	public cocos2d::Layer
{
public:
	static Scene* scene();//构造生成Scene
	virtual bool init();//初始化
	virtual void onEnterTransitionDidFinish();//进入场景后的回调函数，进行音效播放等设置
	bool initBg();//初始化背景
	void initGameDate();//初始化关卡地图数据
	bool initUI();//初始化UI界面
	void preLoadVoid();//预加载游戏音效
	int getTopLevel();//读取用户玩到的最高关卡
	void initLeftRightButton();//初始化选择关卡按钮
	void leftLevel(Ref* menuItem);//关卡选择按钮的回调函数
	void rightLevel(Ref* menuItem);//关卡选择按钮的回调函数

	//用户上下左右移动方块时更新视图。包括改变方块位置，播放音效
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();

	bool checkFailorWin();//检查游戏成功或者失败
	void squareDisappear();//设置某个绿色方块碰到红色方块时使其消失
	void setTouchEvent();//触摸事件的相关设置
	bool onTouchBegan(Touch* touch, Event* event);//触摸开始时的回调函数，记录触摸开始点坐标
	void onTouchEnded(Touch* touch, Event* event);//触摸结束时的回调函数，记录触摸结束点的坐标，判断用户手势移动方向，
												  //调用更新视图和判断游戏成功或失败的函数
	void onGoBack(Ref* sender);

	void gameFail();//游戏失败时的场景切换

	CREATE_FUNC(PlayLayer);//调用init函数
	PlayLayer();
	~PlayLayer();
public:
	static int topLevel;//已通过的最高关卡
	static int xgo;//x轴缩进
	static int ygo;//y轴缩进
	static int mark;//标志位
	static int nowLevel;//当前关卡
	static int sizeOfSquare;//方块的大小
	static int isDefaultData;//是否以自定义的数据开始游戏
private:
	SquareSprite* SquareArray[MATRIX_ROW][MATRIX_COL];//保存视图层的矩阵中每一个位置上的方块
	int tmpDate[MATRIX_ROW][MATRIX_COL];//逻辑层方块种类
	//Date leveldate;//负责生成每一关的地图数据
	int firstX, firstY, endX, endY;//触摸始点和终点
};

