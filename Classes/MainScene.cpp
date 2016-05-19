
#include "MainScene.h"
#include "PlayLayer.h"
#include "EditorScene.h" 

using namespace CocosDenshion;

Scene* MainScene::createScene( )
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene -> addChild( layer );
	return scene;
}

bool MainScene::init( )
{
	if( !Layer::init() ){
		return false;
	}

	// 添加背景图片
    auto sprite = Sprite::create("scene_sta.png");
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
	sprite->setScaleX(GAME_SCREEN_WIDTH / sprite->getContentSize().width);
	sprite->setScaleY(GAME_SCREEN_HEIGHT / sprite->getContentSize().height);
    this->addChild(sprite);

	// 添加开始按钮
	auto startItem = MenuItemImage::create(
                                           "btn_start01.png",
                                           "btn_start02.png",
										   CC_CALLBACK_1(MainScene::menuStartCallback, this));
    
	startItem->setPosition(Vec2(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/6));

	// 添加设置按钮
	auto setItem = MenuItemImage::create(
											"btn_setting01.png",
											"btn_setting02.png",
											CC_CALLBACK_1(MainScene::menuSetCallback,this));
	setItem->setPosition(Vec2( setItem->getContentSize().width , GAME_SCREEN_HEIGHT/6 ));

	// 添加退出按钮
	auto exitItem = MenuItemImage::create(
											"btn_exit01.png",
											"btn_exit02.png",
											CC_CALLBACK_1(MainScene::menuExitCallback,this));
	exitItem->setPosition(Vec2( GAME_SCREEN_WIDTH-exitItem->getContentSize().width ,GAME_SCREEN_HEIGHT/6 ));

	//编辑模式按钮
	auto editorMode = MenuItemImage::create("editor_mode_normal.png", "editor_mode_pressed.png", CC_CALLBACK_1(MainScene::menuEditorModeCallback, this));
	editorMode->setPosition(Vec2(GAME_SCREEN_WIDTH * 6 / 7, GAME_SCREEN_HEIGHT * 7 / 8));

	auto menu = Menu::create(startItem, setItem, exitItem, editorMode, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	//this->addChild(editorMode);
	return true;
}

void MainScene::menuStartCallback( Ref* pSender )
{
	//auto scene = GameScene::createScene();
	//CCDirector::sharedDirector()->replaceScene(scene);
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PlayLayer::scene()));
}

void MainScene::menuSetCallback(Ref *pSender)
{
	auto scene = Developer::createScene();
	CCTransitionScene* reScene = CCTransitionPageTurn::create(1.0f, scene, false);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void MainScene::menuExitCallback(Ref *pSender)
{
	Director::getInstance()->end();
}

void MainScene::menuEditorModeCallback(Ref *pSender){
	CCLOG("跳转到编辑模式界面");
	/*auto scene = EditorScene::createScene();
	CCTransitionScene* reScene = CCTransitionScene::create(0, scene);
	Director::getInstance()->replaceScene(reScene);*/

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, EditorScene::createScene()));
}
void MainScene::onEnter()
{
	Layer::onEnter();
}

void MainScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();  
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {                      
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_mainScene.mp3", true);  
    } 
}

void MainScene::onExit()
{
	Layer::onExit();
}

void MainScene::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}

void MainScene::cleanup()
{
	Layer::cleanup();
	//SimpleAudioEngine::getInstance()->stopBackgroundMusic("music_mainScene.mp3");
}