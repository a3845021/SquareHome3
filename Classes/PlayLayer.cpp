#include "PlayLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "EditorScene.h"
#include<string>



int PlayLayer::topLevel = 0;
int PlayLayer::nowLevel = 0;
int PlayLayer::xgo = 0;
int PlayLayer::ygo = 400;
int PlayLayer::mark = 0;
int PlayLayer::sizeOfSquare = 45;
int PlayLayer::isDefaultData = 0;//0:默认数据  1：地图编辑模块传过来的数据
Scene* PlayLayer::scene(){
	Scene* scene = Scene::create();
	Layer* layer = PlayLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PlayLayer::init(){
	this->preLoadVoid();
	this->initBg();
	this->initGameDate();
	this->initUI();
	this->setTouchEvent();
	this->initLeftRightButton();
	mark++;
	return true;
}

bool PlayLayer::initBg(){
	//LayerColor* ccc = LayerColor::create(ccc4(240, 240, 240, 240), 1280, 1280);
	//LayerColor* ccc = LayerColor::create("");
	Sprite * bg = Sprite::create("scene_bg.png");
	bg->setPosition(GAME_SCREEN_WIDTH / 2, GAME_SCREEN_HEIGHT/2);
	bg->setScaleX(GAME_SCREEN_WIDTH / bg->getContentSize().width);
	bg->setScaleY(GAME_SCREEN_HEIGHT / bg->getContentSize().height);

	this->addChild(bg);
	return true;
}
void PlayLayer::initGameDate(){
	if (!isDefaultData){
		this->topLevel = getTopLevel();
		if (mark == 0){
			this->nowLevel = topLevel;
		}
		Date::createBy(nowLevel);
	}
	for (int i = 0; i <13; i++){
		for (int j = 0; j < 17; j++){
			if (Date::square[i][j] == 1)
				tmpDate[i][j] = 1;
			else tmpDate[i][j] = 0;
		}
	}
}
bool PlayLayer::initUI(){
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 16; j++){
			if (Date::square[i][j] == 1){
				SquareSprite* crab = (SquareSprite*)SquareSprite::createBackrd(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
				//SquareArray[i][j] = crab;
				this->addChild(crab, 1);
			}
			else if (Date::square[i][j] == 2){
				SquareSprite* crab = (SquareSprite*)SquareSprite::createWall(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
				//SquareArray[i][j] = crab;
				this->addChild(crab, 1);
			}
			else if (Date::square[i][j] == 3){
				SquareSprite* crab = (SquareSprite*)SquareSprite::createHome(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
				//SquareArray[i][j] = crab;
				this->addChild(crab, 1);
			}
			else if (Date::square[i][j] == 4){
				SquareSprite* crab = (SquareSprite*)SquareSprite::createTrap(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
				//SquareArray[i][j] = crab;
				this->addChild(crab, 1);
			}
			else if (Date::square[i][j] == 0){
				SquareSprite* crab = (SquareSprite*)SquareSprite::createBackrd(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
				//SquareArray[i][j] = crab;
				this->addChild(crab, 1);
			}
		}
	}
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 16; j++){
			SquareSprite* crab = (SquareSprite*)SquareSprite::createCrab(xgo + j * sizeOfSquare, ygo + i * sizeOfSquare);
			SquareArray[i][j] = crab;
			if (Date::square[i][j] == 1){
				this->addChild(SquareArray[i][j], 2);
			}
		}
	}
	return true;
}
void PlayLayer::setTouchEvent(){
	auto listener1 = EventListenerTouchOneByOne::create();
	// 是否开启触摸
	listener1->setSwallowTouches(true);
	// 触摸回调
	listener1->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	//listener1->onTouchMoved = CC_CALLBACK_2(PlayLayer::onTouchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(PlayLayer::onTouchEnded, this);
	//将触摸监听添加到eventDispacher中去
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}
bool PlayLayer::onTouchBegan(Touch* touch, Event* event){
	//获取触摸的X轴和Y轴
	Point touchPoint = touch->getLocation(); //获取OpenGL坐标（即cocos2d-x坐标，原点在左下角）
	touch->getLocationInView();
	firstX = touchPoint.x;
	firstY = touchPoint.y;
	return true;
}



//事件监听回调：触摸结束
void PlayLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	//获取X轴和Y轴的移动范围
	Point touchPoint = touch->getLocation(); //获取OpenGL坐标（即cocos2d-x坐标，原点在左下角）
	endX = firstX - touchPoint.x;
	endY = firstY - touchPoint.y;

	//判断X轴和Y轴的移动距离，如果X轴的绝对值大，则向左右滑动，如果Y轴的绝对值大，则向上下滑动
	if (abs(endX) > abs(endY)){
		//手势向左右
		//判断向左还是向右
		if (endX > 10){
			//向左
			doLeft();
		}
		else if (endX< 10){
			//向右
			if (doRight()){
			}
		}
	}
	else{
		//手势向上下
		//判断手势向上还是向下
		if (endY > 10){
			//向下
			doDown();
		}
		else if (endY < -10){
			//向上
			doUp();
		}
	}
	checkFailorWin();
}
bool PlayLayer::doUp(){
	bool isMove = false;
	//Hide* hide = Hide::create();
	//Show* show = Show::create();
	for (int i = 10; i >= 0; i--){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1 && Date::square[i + 1][j] != 2 && i != 11 && tmpDate[i + 1][j] != 1){
				Point pp = SquareArray[i][j]->getPosition();
				SquareArray[i][j]->setPosition(ccp(pp.x, pp.y + sizeOfSquare));
				tmpDate[i][j] = 0;
				tmpDate[i + 1][j] = 1;
				Sprite* tmp = SquareArray[i][j];
				SquareArray[i][j] = SquareArray[i + 1][j];
				SquareArray[i + 1][j] = (SquareSprite*)tmp;
				isMove = true;
				// checkFailorWin();
			}
		}
	}
	if (isMove){
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/move.wav", false);
	}
	return true;
}
bool PlayLayer::doDown(){
	bool isMove = false;
	for (int i = 1; i <12; i++){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1 && Date::square[i - 1][j] != 2 && i != 0 && tmpDate[i - 1][j] != 1){
				Point pp = SquareArray[i][j]->getPosition();
				SquareArray[i][j]->setPosition(ccp(pp.x, pp.y - sizeOfSquare));
				tmpDate[i][j] = 0;
				tmpDate[i - 1][j] = 1;
				Sprite* tmp = SquareArray[i][j];
				SquareArray[i][j] = SquareArray[i - 1][j];
				SquareArray[i - 1][j] = (SquareSprite*)tmp;
				isMove = true;
				//checkFailorWin();
			}
		}
	}
	if (isMove){
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/move.wav", false);
	}
	return true;
}
bool PlayLayer::doLeft(){
	bool isMove = false;
	for (int i = 0; i <12; i++){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1 && Date::square[i][j - 1] != 2 && j != 0 && tmpDate[i][j - 1] != 1){
				Point pp = SquareArray[i][j]->getPosition();
				SquareArray[i][j]->setPosition(ccp(pp.x - sizeOfSquare, pp.y));
				tmpDate[i][j] = 0;
				tmpDate[i][j - 1] = 1;
				Sprite* tmp = SquareArray[i][j];
				SquareArray[i][j] = SquareArray[i][j - 1];
				SquareArray[i][j - 1] = (SquareSprite*)tmp;
				isMove = true;
				//checkFailorWin();
			}
		}
	}
	if (isMove){
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/move.wav", false);
	}
	return true;
}
bool PlayLayer::doRight(){
	bool isMove = false;
	for (int i = 0; i <12; i++){
		for (int j = 15; j >= 0; j--){
			if (tmpDate[i][j] == 1 && Date::square[i][j + 1] != 2 && j != 15 && tmpDate[i][j + 1] != 1){
				Point pp = SquareArray[i][j]->getPosition();
				SquareArray[i][j]->setPosition(ccp(pp.x + sizeOfSquare, pp.y));
				tmpDate[i][j] = 0;
				tmpDate[i][j + 1] = 1;
				Sprite* tmp = SquareArray[i][j];
				SquareArray[i][j] = SquareArray[i][j + 1];
				SquareArray[i][j + 1] = (SquareSprite*)tmp;
				isMove = true;
				//checkFailorWin();
			}
		}
	}
	if (isMove){
		SimpleAudioEngine::sharedEngine()->playEffect("sounds/move.wav", false);
	}
	return true;
}
bool PlayLayer::checkFailorWin(){
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1 && Date::square[i][j] == 4){
				this->squareDisappear();
				SimpleAudioEngine::sharedEngine()->playEffect("sounds/filded.wav", false);
				//Director::getInstance()->replaceScene(TransitionFade::create(0.7f, PlayLayer::scene()));//失败
				this->gameFail();
			}
		}
	}
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1){
				if (Date::square[i][j] != 3){
					return true;//继续游戏
				}
			}
		}
	}
	mark++;
	nowLevel++;
	if (nowLevel>8) nowLevel = 8;
	if (nowLevel > topLevel){
		topLevel = nowLevel;
		UserDefault::getInstance()->setIntegerForKey("topLevel", topLevel);//存档
	}
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/succeed.mp3", false);//播放成功音效   是否循环
	Director::getInstance()->replaceScene(TransitionFade::create(0.7f, PlayLayer::scene()));//成功，进入下一关
	return false;
}

void PlayLayer::gameFail(){
	//auto scene = GameOver::createScene();
	//scene->setRes
	//scene->setSuccessFlag(false);
	//Director::sharedDirector()->replaceScene(scene);

	auto scene = Scene::create();
	auto layer = GameOver::create();
	//layer->setScore(1000);
	layer->setResult(0);
	scene->addChild(layer);

	CCTransitionScene* reScene = CCTransitionFadeUp::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}
//检测碰撞方块并使其消失
void PlayLayer::squareDisappear(){
	for (int i = 0; i < 12; i++){
		for (int j = 0; j < 16; j++){
			if (tmpDate[i][j] == 1 && Date::square[i][j] == 4){
				SquareArray[i][j]->setPosition(-100, -100);
			}
		}
	}
}
void PlayLayer::preLoadVoid(){
	SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/succeed.mp3");//预加载声音文件
	SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/filded.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/move.wav");
}

int PlayLayer::getTopLevel(){
	if (UserDefault::getInstance()->getBoolForKey("first_time", true)){
		UserDefault::getInstance()->setIntegerForKey("topLevel", 0);
		UserDefault::getInstance()->setBoolForKey("first_time", false);
	}
	//UserDefault::getInstance()->setIntegerForKey("topLevel", 0);
	int lev = UserDefault::getInstance()->getIntegerForKey("topLevel");
	return lev;
}
void PlayLayer::initLeftRightButton(){
	//返回按钮
	cocos2d::MenuItemImage * goBack = cocos2d::MenuItemImage::create("btn_ret.png", "btn_ret.png", this, menu_selector(PlayLayer::onGoBack));
	goBack->setPosition(ccp(GAME_SCREEN_WIDTH/8,GAME_SCREEN_HEIGHT/12*11));
	//goBack->setScale(1.0f);
	//auto menu = Menu::create(goBack, NULL);
	//this->addChild(menu,1);
	//menu->setPosition(Vec2::ZERO);

	

	cocos2d::MenuItemImage *left = cocos2d::MenuItemImage::create("playui/choselevel.png", "playui/choselevel_pressed.png", this, menu_selector(PlayLayer::leftLevel));
	left->setPosition(ccp(50, 300));
	left->setVisible(false);
	//auto left_menu = Menu::create(left, NULL);
	//left_menu->setPosition(Vec2::ZERO);
	//this->addChild(left_menu, 1);

	cocos2d::MenuItemImage *right = cocos2d::MenuItemImage::create("playui/choselevel_right.png", "playui/choselevel_pressed_right.png", this, menu_selector(PlayLayer::rightLevel));
	right->setPosition(ccp(720 - 50, 300));
	right->setVisible(false);
	auto right_menu = Menu::create(right, left, goBack, NULL);
	right_menu->setPosition(Vec2::ZERO);
	this->addChild(right_menu, 1);

	if (isDefaultData){
		return;
	}

	if (nowLevel != 0){ 
		left->setVisible(true);
	}
	if (nowLevel%8 < getTopLevel()){
		right->setVisible(true);
	}
	std::string levelMark = "7 - ";
	char buf[10];
	sprintf(buf, "%d", nowLevel%8);
	std::string b = buf;
	levelMark += b;
	LabelTTF* levelLabel = LabelTTF::create(levelMark, "Microsoft YaHei", 50);
	levelLabel->setColor(ccc3(255, 0, 0));
	levelLabel->setPosition(720/2, 1180);
	this->addChild(levelLabel);

	
}
void PlayLayer::onGoBack(Ref* sender)
{
	Scene* mainScene = MainScene::createScene();
	Scene* editorScene = EditorScene::createScene();
	if (isDefaultData){
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, editorScene));
	}
	else{
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainScene));
	}
}
void PlayLayer::leftLevel(Object* menuItem){
		nowLevel--;
		if (nowLevel<0) nowLevel = 0;
		Director::getInstance()->replaceScene(TransitionFade::create(0.0f, PlayLayer::scene()));
}
void PlayLayer::rightLevel(Object* menuItem){
	nowLevel++;
	//if (nowLevel<0) nowLevel = 0;
	Director::getInstance()->replaceScene(TransitionFade::create(0.0f, PlayLayer::scene()));
}


void PlayLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("music_bg.mp3", true);
	}
}
PlayLayer::PlayLayer()
{
}



PlayLayer::~PlayLayer()
{
}
