#include "CarAction.h"
USING_NS_CC;
CarAction::CarAction(Player * player)
{
	m_player = player;
}

bool CarAction::isDone()const{
	auto s = getTarget();
	if(s)
	{
		return false;
	}else
	{
		return true;
	}
}


void CarAction::step(float time)
{
	auto s = getTarget();
	if(s)
	{
		auto distance = s->getPosition3D().distance(m_player->getPlayer()->getPosition3D());
		if(distance<0.8)
		{
			s->setColor(Color3B(0,0,255));
			m_player->hurt();
		}
	}
}