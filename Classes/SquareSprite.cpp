#include "cocos2d.h"
#include"SquareSprite.h"

USING_NS_CC;

double SquareSprite::scaleOfSquare = 0.85;

Sprite* SquareSprite::createCrab(int x, int y){
	Sprite* Crab = Sprite::create("playui/crab.png");
	Crab->setScale(scaleOfSquare);
	Crab->setPosition(x, y);
	Crab->setAnchorPoint(ccp(0, 0));
	return Crab;
}
Sprite* SquareSprite::createHome(int x, int y){
	Sprite* Crab = Sprite::create("playui/home.png");
	Crab->setScale(scaleOfSquare);
	Crab->setPosition(x, y);
	Crab->setAnchorPoint(ccp(0, 0));
	return Crab;
}
Sprite* SquareSprite::createTrap(int x, int y){
	Sprite* Crab = Sprite::create("playui/trap.png");
	Crab->setScale(scaleOfSquare);
	Crab->setPosition(x, y);
	Crab->setAnchorPoint(ccp(0, 0));
	return Crab;
}
Sprite* SquareSprite::createWall(int x, int y){
	//Sprite* Crab = Sprite::create("PlayUI/wall.png", CCRectMake(0, 0, 23, 23));
	Sprite* Crab = Sprite::create("playui/wall.png");
	Crab->setScale(scaleOfSquare);
	Crab->setPosition(x, y);
	Crab->setAnchorPoint(ccp(0, 0));
	return Crab;
}
Sprite* SquareSprite::createBackrd(int x, int y){
	//Sprite* Crab = Sprite::create("PlayUI/wall.png", CCRectMake(0, 0, 23, 23));
	Sprite* Crab = Sprite::create("playui/backrd.png");
	Crab->setScale(scaleOfSquare);
	Crab->setPosition(x, y);
	Crab->setAnchorPoint(ccp(0, 0));
	return Crab;
}
//SquareSprite* SquareSprite::createHome(int x, int y);
//SquareSprite* SquareSprite::createTrap(int x, int y);
//SquareSprite* SquareSprite::createWall(int x, int y);


SquareSprite::SquareSprite(){

}
SquareSprite::~SquareSprite(){

}
