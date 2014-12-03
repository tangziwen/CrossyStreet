#ifndef CAR_ACTION_H
#define CAR_ACTION_H
#include "cocos2d.h"
#include "Player.h"
class CarAction: public cocos2d::Action
{

public:
	CarAction(Player * player);
	virtual bool isDone() const;
	virtual void step(float time);
private:
	Player * m_player;
};
#endif