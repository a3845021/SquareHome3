/*
* SquareSprite.h
*
*  Created on: 2014Äê12ÔÂ14ÈÕ
*      Author: mark_chen
*/


#ifndef SQUARESPRITE_H_
#define SQUARESPRITE_H_
#include "cocos2d.h"
class SquareSprite : public cocos2d::Sprite{
public:
	static Sprite* createCrab(int x, int y);
	static Sprite* createHome(int x, int y);
	static Sprite* createTrap(int x, int y);
	static Sprite* createWall(int x, int y);
	static Sprite* createBackrd(int x, int y);
	static double scaleOfSquare;
	SquareSprite();
	virtual ~SquareSprite();
};

#endif /* SQUARESPRITE_H_ */
