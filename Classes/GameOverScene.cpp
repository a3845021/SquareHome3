
#include "GameOverScene.h"
#include "PlayLayer.h"
#include "MainScene.h"

using namespace CocosDenshion;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{
	if( !Layer::init() ){
		return false;
	}

	TTFConfig config("yuehei.otf",48);

	// ��ӱ���ͼƬ
    auto sprite = Sprite::create("scene_end.png");
	sprite->setScale(720.0 / sprite->getContentSize().width);
	sprite->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));
    this->addChild(sprite);

	// ����
	auto labelScore = Label::createWithTTF(config, "  0  ");
	labelScore -> setPosition(Point( GAME_SCREEN_WIDTH/2 , GAME_SCREEN_HEIGHT/1.4));
	labelScore -> setTag(13);
	this->addChild(labelScore);

	// ������¿�ʼ��ť
	auto restartItem = MenuItemImage::create(
                                           "btn_restart01.png",
                                           "btn_restart02.png",
										   CC_CALLBACK_1(GameOver::menuRestartCallback, this));
    
	restartItem->setPosition(Vec2(GAME_SCREEN_WIDTH/4,GAME_SCREEN_HEIGHT/8));

	// ��ӷ������˵���ť
	auto backItem = MenuItemImage::create(
                                           "btn_back01.png",
                                           "btn_back02.png",
										   CC_CALLBACK_1(GameOver::menuBackCallback, this));
    
	backItem->setPosition(Vec2(GAME_SCREEN_WIDTH/1.4,GAME_SCREEN_HEIGHT/8));
    
	auto menu = Menu::create(restartItem,backItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this -> addChild( menu );

	return true;
}

void GameOver::menuRestartCallback(Ref *pSender)
{
	//auto scene = GameScene::createScene();
	//CCTransitionScene* reScene = CCTransitionMoveInL::create(1.0f, scene);
	//CCDirector::sharedDirector()->replaceScene(reScene);
	Director::getInstance()->replaceScene(PlayLayer::scene());
}

void GameOver::menuBackCallback( Ref *pSender )
{
	auto scene = MainScene::createScene();
	CCTransitionScene* reScene = CCTransitionSplitRows::create(1.0f, scene);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameOver::setScore( int sc )
{
	auto labelScore = (Label *)this -> getChildByTag(13);
	labelScore -> setString( StringUtils::format(" %d ",sc));
	if( userDefault->getIntegerForKey("Int") < sc ){
		// �¼�¼
		auto newRecord = Sprite::create("sprite_newRecord.png");
		newRecord -> setPosition(Point( GAME_SCREEN_WIDTH/3.05 , GAME_SCREEN_HEIGHT/1.22));
		newRecord->setScale(10.0f);// start size
		newRecord->runAction(ScaleTo::create(1.2f, 1.0));

		this->addChild(newRecord);
		
		// ��Ч
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
			SimpleAudioEngine::getInstance()->playEffect("music_win.wav",false);  
		}

		userDefault->setIntegerForKey("Int",sc);
	}
	else
	{
		// ����
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {                      
			SimpleAudioEngine::getInstance()->playEffect("music_fail.mp3",false);  
		}
	}

}
void GameOver::setResult(bool result){
	log("GameOver::setResult called");
	if (result == 1){//�ɹ�
		auto labelScore = (Label *)this->getChildByTag(13);
		labelScore->setString("SUCCESS!");
		labelScore->setSystemFontSize(40);
	}
	else{//ʧ��
		auto labelScore = (Label *)this->getChildByTag(13);
		labelScore->setString("FAIL!");
		labelScore->setSystemFontSize(80);

	}
}