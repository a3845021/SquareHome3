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
	static Scene* scene();//��������Scene
	virtual bool init();//��ʼ��
	virtual void onEnterTransitionDidFinish();//���볡����Ļص�������������Ч���ŵ�����
	bool initBg();//��ʼ������
	void initGameDate();//��ʼ���ؿ���ͼ����
	bool initUI();//��ʼ��UI����
	void preLoadVoid();//Ԥ������Ϸ��Ч
	int getTopLevel();//��ȡ�û��浽����߹ؿ�
	void initLeftRightButton();//��ʼ��ѡ��ؿ���ť
	void leftLevel(Ref* menuItem);//�ؿ�ѡ��ť�Ļص�����
	void rightLevel(Ref* menuItem);//�ؿ�ѡ��ť�Ļص�����

	//�û����������ƶ�����ʱ������ͼ�������ı䷽��λ�ã�������Ч
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();

	bool checkFailorWin();//�����Ϸ�ɹ�����ʧ��
	void squareDisappear();//����ĳ����ɫ����������ɫ����ʱʹ����ʧ
	void setTouchEvent();//�����¼����������
	bool onTouchBegan(Touch* touch, Event* event);//������ʼʱ�Ļص���������¼������ʼ������
	void onTouchEnded(Touch* touch, Event* event);//��������ʱ�Ļص���������¼��������������꣬�ж��û������ƶ�����
												  //���ø�����ͼ���ж���Ϸ�ɹ���ʧ�ܵĺ���
	void onGoBack(Ref* sender);

	void gameFail();//��Ϸʧ��ʱ�ĳ����л�

	CREATE_FUNC(PlayLayer);//����init����
	PlayLayer();
	~PlayLayer();
public:
	static int topLevel;//��ͨ������߹ؿ�
	static int xgo;//x������
	static int ygo;//y������
	static int mark;//��־λ
	static int nowLevel;//��ǰ�ؿ�
	static int sizeOfSquare;//����Ĵ�С
	static int isDefaultData;//�Ƿ����Զ�������ݿ�ʼ��Ϸ
private:
	SquareSprite* SquareArray[MATRIX_ROW][MATRIX_COL];//������ͼ��ľ�����ÿһ��λ���ϵķ���
	int tmpDate[MATRIX_ROW][MATRIX_COL];//�߼��㷽������
	//Date leveldate;//��������ÿһ�صĵ�ͼ����
	int firstX, firstY, endX, endY;//����ʼ����յ�
};

