#include "AppDelegate.h"
#include "SceneManager.h"
#include "WelPage.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLViewImpl::create("My Game");
		glview = GLViewImpl::createWithRect("CocosProjectn", Rect(0, 0, 720, 1280));
        director->setOpenGLView(glview);
		glview->setFrameSize(720 / 2, 1280 / 2);//设置桌面窗口大小
    }
	director->getOpenGLView()->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);
	//glview->setDesignResolutionSize(1280, 720, kResolutionExactFit);
	//glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::EXACT_FIT);

    // turn off display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	std::vector<std::string> searchPath;
	searchPath.push_back("rese");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);


    // create a scene. it's an autorelease object
	auto scene = WelPage::scene();
	auto scene1 = PlayLayer::scene();
	//auto scene2 = MenuScene::scene();
    // run
	//SceneManager * sceneManager = new SceneManager();
	//sceneManager->createScene();

    director->runWithScene(scene);
	//director->runWithScene(sceneManager->startScene);


	//初始化 背景音乐  
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_bg.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_mainScene.mp3");
	//初始化 音效  
	SimpleAudioEngine::getInstance()->preloadEffect("music_explode.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music_explodeOne.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("music_gameOver.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music_fail.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("music_win.wav");
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
