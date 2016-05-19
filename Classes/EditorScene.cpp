#include "EditorScene.h"
#include "GameDefine.h"
#include "SquareSprite.h"

#include "PlayLayer.h"
using namespace std;
using namespace cocos2d::ui;


Scene* EditorScene::createScene(){
	Scene* scene = Scene::create();
	Layer* layer = EditorScene::create();
	scene->addChild(layer);
	return scene;
}
bool EditorScene::init(){
	initBackground();
	initRadioButton();
	setTouchEvent();
	memset(squareType, 0, sizeof(squareType));
	return true;
}
void EditorScene::initBackground()
{
	Sprite * bg = Sprite::create("scene_bg.png");
	bg->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT / 2);
	bg->setScaleX(GAME_SCREEN_WIDTH / bg->getContentSize().width);
	bg->setScaleY(GAME_SCREEN_HEIGHT / bg->getContentSize().height);
	this->addChild(bg);

	for (int i = 0; i < MATRIX_ROW - 1; i++){
		for (int j = 0; j < MATRIX_COL - 1; j++){
			SquareSprite* crab = (SquareSprite*)SquareSprite::createBackrd(XGO + j * SIZE_OF_SQUARE, YGO + i * SIZE_OF_SQUARE);
			//SquareArray[i][j] = crab;
			this->addChild(crab);
		}
	}
}

void EditorScene::initRadioButton(){
	//this->setTouchEnabled(true);


	_radioButtonGroup = RadioButtonGroup::create();
	this->addChild(_radioButtonGroup,1);

	int NUMBER_OF_BUTTONS = 4;

	for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
	{
		RadioButton* radioButton = RadioButton::create("cocosui/radio_button_off.png", "cocosui/radio_button_on.png");
		radioButton->setPosition(ccp(100*(i+1), 100));
		_radioButtonGroup->addRadioButton(radioButton);
		this->addChild(radioButton, 1);
		radioButton->setScale(2.0);
		radioButton->setTag(i);
		radioButton->addEventListener(CC_CALLBACK_2(EditorScene::onChangedRadioButtonSelect, this));
	}

	//_radioButtonGroup->setSelectedButton(0);

	// 添加开始按钮
	auto startItem = MenuItemImage::create(
		"btn_start01.png",
		"btn_start02.png",
		CC_CALLBACK_1(EditorScene::menuStartCallback, this));

	startItem->setPosition(ccp(720/2,1280/4));

	// 添加清除按钮
	auto clearAllItem = MenuItemImage::create(
		"cocosui/clearallnormal.png",
		"cocosui/clearallpressed.png",
		CC_CALLBACK_1(EditorScene::menuClearCallback, this));
	clearAllItem->setPosition(ccp(720/3, 1280/4));
	//增加返回按钮
	cocos2d::MenuItemImage * goBack = cocos2d::MenuItemImage::create("btn_ret.png", "btn_ret.png", this, menu_selector(EditorScene::onGoBack));
	goBack->setPosition(ccp(GAME_SCREEN_WIDTH / 8, GAME_SCREEN_HEIGHT / 12 * 11));
	Menu* menu = Menu::create(startItem, clearAllItem,goBack, NULL);

	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	string picPath[4] = { "playui/crab.png", "playui/wall.png", "playui/home.png", "playui/trap.png" };
	Menu* picMenu = Menu::create();
	for (int i = 0; i < 4; i++){
		auto p1 = MenuItemImage::create(picPath[i], picPath[i]);
		p1->setPosition(ccp(100 * (i + 1), 130));
		picMenu->addChild(p1);
	}
	picMenu->setPosition(Vec2::ZERO);
	this->addChild(picMenu);

	
}
void EditorScene::menuClearCallback(Ref *pSender){
	clearAllSquare();
}
void EditorScene::menuStartCallback(Ref* pSender)
{
	Date::initData(squareType);
	PlayLayer::isDefaultData = 1;
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayLayer::scene()));
}

void EditorScene::onChangedRadioButtonSelect(RadioButton* radioButton, RadioButton::EventType type){
	if (radioButton == nullptr)
	{
		return;
	}

	switch (type){
	case RadioButton::EventType::SELECTED:
			RadioSelectState = radioButton->getTag();
			break;
	case RadioButton::EventType::UNSELECTED:

		break;
	default:
		break;
	}
	CCLOG("selected button`s index = %d", RadioSelectState);


}

void EditorScene::setTouchEvent(){
	EventListenerTouchOneByOne* listener11 = EventListenerTouchOneByOne::create();
	// 是否开启触摸
	listener11->setSwallowTouches(true);
	// 触摸回调
	listener11->onTouchBegan = CC_CALLBACK_2(EditorScene::onTouchBegan, this);
	listener11->onTouchMoved = CC_CALLBACK_2(EditorScene::onTouchMove, this);
	listener11->onTouchEnded = CC_CALLBACK_2(EditorScene::onTouchEnded, this);
	//将触摸监听添加到eventDispacher中去
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener11, this);
}

bool EditorScene::onTouchBegan(Touch* touch, Event* event){
	return true;
}

int EditorScene::xx = -1;
int EditorScene::yy = -1;

void EditorScene::onTouchMove(Touch * touch, Event*event){
	Point touchPoint = touch->getLocation();
	//if (RadioSelectState != -1){
	CCLOG("touch point is x: %f,y:%f", touchPoint.x, touchPoint.y);
	//}
	int x = (touchPoint.x - XGO) / SIZE_OF_SQUARE;
	int y = (touchPoint.y - YGO) / SIZE_OF_SQUARE;

	if (xx == x&&yy == y){
		return;
	}
	xx = x;
	yy = y;
	if (x > MATRIX_COL || y > MATRIX_ROW - 2 || x < 0 || y < 0){
		return;
	}
	switch (RadioSelectState){

	case 0:
	{
			  int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1 + 4;
			  if (squareType[y][x] == 1){
				  if (nullptr == this->getChildByTag(tag)) return;
				  this->getChildByTag(tag)->setVisible(false);
				  squareType[y][x] = 0;
				  break;
			  }
			  if (squareType[y][x] != 0){
				  break;
			  }

			  squareType[y][x] = 1;
			  SquareSprite* sprite0;
			  if (nullptr == this->getChildByTag(tag)){
				  sprite0 = (SquareSprite*)SquareSprite::createCrab(XGO + x * SIZE_OF_SQUARE,
					  YGO + y * SIZE_OF_SQUARE);
				  sprite0->setTag(tag);
				  this->addChild(sprite0);
			  }
			  else{
				  this->getChildByTag(tag)->setVisible(true);
			  }

			  break;
	}
	case 1:{

			   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
			   if (squareType[y][x] == 2){
				   if (nullptr == this->getChildByTag(tag)) return;
				   this->getChildByTag(tag)->setVisible(false);
				   squareType[y][x] = 0;
				   break;
			   }
			   if (squareType[y][x] != 0){
				   break;
			   }

			   squareType[y][x] = 2;
			   SquareSprite* sprite0;
			   if (nullptr == this->getChildByTag(tag)){
				   sprite0 = (SquareSprite*)SquareSprite::createWall(XGO + x * SIZE_OF_SQUARE,
					   YGO + y * SIZE_OF_SQUARE);
				   sprite0->setTag(tag);
				   this->addChild(sprite0);
			   }
			   else{
				   this->getChildByTag(tag)->setVisible(true);
			   }
			   break;
	}

	case 2:{
			   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
			   if (squareType[y][x] == 3){
				   if (nullptr == this->getChildByTag(tag)) return;
				   this->getChildByTag(tag)->setVisible(false);
				   squareType[y][x] = 0;
				   break;
			   }
			   if (squareType[y][x] != 0){
				   break;
			   }

			   squareType[y][x] = 3;
			   SquareSprite* sprite0;
			   if (nullptr == this->getChildByTag(tag)){
				   sprite0 = (SquareSprite*)SquareSprite::createHome(XGO + x * SIZE_OF_SQUARE,
					   YGO + y * SIZE_OF_SQUARE);
				   sprite0->setTag(tag);
				   this->addChild(sprite0);
			   }
			   else{
				   this->getChildByTag(tag)->setVisible(true);
			   }
			   break;
	}

	case 3:{
			   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
			   if (squareType[y][x] == 4){
				   if (nullptr == this->getChildByTag(tag)) return;
				   this->getChildByTag(tag)->setVisible(false);
				   squareType[y][x] = 0;
				   break;
			   }
			   if (squareType[y][x] != 0){
				   break;
			   }

			   squareType[y][x] = 4;
			   SquareSprite* sprite0;
			   if (nullptr == this->getChildByTag(tag)){
				   sprite0 = (SquareSprite*)SquareSprite::createTrap(XGO + x * SIZE_OF_SQUARE,
					   YGO + y * SIZE_OF_SQUARE);
				   sprite0->setTag(tag);
				   this->addChild(sprite0);
			   }
			   else{
				   this->getChildByTag(tag)->setVisible(true);
			   }
			   break;
	}

	default:
		break;
	}
}
//事件监听回调：触摸结束
void EditorScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point touchPoint = touch->getLocation();
	//if (RadioSelectState != -1){
		CCLOG("touch point is x: %f,y:%f", touchPoint.x, touchPoint.y);
	//}
		int x = (touchPoint.x - XGO) / SIZE_OF_SQUARE;
		int y = (touchPoint.y - YGO) / SIZE_OF_SQUARE;
		if (x == xx&&y == yy){
			xx = -1, yy = -1;
			return;
		}
		if (x > MATRIX_COL || y > MATRIX_ROW-2 || x < 0 || y < 0){
			return;
		}
		switch (RadioSelectState){
			 
		case 0:
		{
		    int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
			if (squareType[y][x] == 1){
				this->getChildByTag(tag)->setVisible(false);
				squareType[y][x] = 0;
				break;
			}
			if (squareType[y][x] != 0){
				break;
			}
			
			squareType[y][x] = 1;
			SquareSprite* sprite0;
			if (nullptr == this->getChildByTag(tag)){
				sprite0 = (SquareSprite*)SquareSprite::createCrab(XGO + x * SIZE_OF_SQUARE,
					YGO + y * SIZE_OF_SQUARE);
				sprite0->setTag(tag);
				this->addChild(sprite0);
			}
			else{
				this->getChildByTag(tag)->setVisible(true);
			}
			
			break;
		}
		case 1:{

				   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
				   if (squareType[y][x] == 2){
					   this->getChildByTag(tag)->setVisible(false);
					   squareType[y][x] = 0;
					   break;
				   }
				   if (squareType[y][x] != 0){
					   break;
				   }

				   squareType[y][x] = 2;
				   SquareSprite* sprite0;
				   if (nullptr == this->getChildByTag(tag)){
					   sprite0 = (SquareSprite*)SquareSprite::createWall(XGO + x * SIZE_OF_SQUARE,
						   YGO + y * SIZE_OF_SQUARE);
					   sprite0->setTag(tag);
					   this->addChild(sprite0);
				   }
				   else{
					   this->getChildByTag(tag)->setVisible(true);
				   }
			break;
		}

		case 2:{
				   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
				   if (squareType[y][x] == 3){
					   this->getChildByTag(tag)->setVisible(false);
					   squareType[y][x] = 0;
					   break;
				   }
				   if (squareType[y][x] != 0){
					   break;
				   }

				   squareType[y][x] = 3;
				   SquareSprite* sprite0;
				   if (nullptr == this->getChildByTag(tag)){
					   sprite0 = (SquareSprite*)SquareSprite::createHome(XGO + x * SIZE_OF_SQUARE,
						   YGO + y * SIZE_OF_SQUARE);
					   sprite0->setTag(tag);
					   this->addChild(sprite0);
				   }
				   else{
					   this->getChildByTag(tag)->setVisible(true);
				   }
			break;
		}

		case 3:{
				   int tag = RadioSelectState * 12 * 16 + y * 16 + x + 1+4;
				   if (squareType[y][x] == 4){
					   this->getChildByTag(tag)->setVisible(false);
					   squareType[y][x] = 0;
					   break;
				   }
				   if (squareType[y][x] != 0){
					   break;
				   }

				   squareType[y][x] = 4;
				   SquareSprite* sprite0;
				   if (nullptr == this->getChildByTag(tag)){
					   sprite0 = (SquareSprite*)SquareSprite::createTrap(XGO + x * SIZE_OF_SQUARE,
						   YGO + y * SIZE_OF_SQUARE);
					   sprite0->setTag(tag);
					   this->addChild(sprite0);
				   }
				   else{
					   this->getChildByTag(tag)->setVisible(true);
				   }
			break;
		}

		default:
			break;
		}

}

void EditorScene::clearAllSquare(){
	for (int i = 4; i < 800; i++){
		if (nullptr != this->getChildByTag(i)){
			this->getChildByTag(i)->setVisible(false);
			this->removeChildByTag(i);
		}
	}
	memset(squareType, 0, sizeof(squareType));
}

void EditorScene::onGoBack(Ref* sender){
	PlayLayer::isDefaultData = 0;
	Scene* mainScene = MainScene::createScene();
	Scene* editorScene = EditorScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainScene));
}
EditorScene::EditorScene()
{
}


EditorScene::~EditorScene()
{
}


