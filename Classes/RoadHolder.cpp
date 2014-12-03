#include "RoadHolder.h"
#include "base_Header.h"
USING_NS_CC;
#define STREET_MODEL_LENGHT_SCALE 0.3
#define STREET_MODEL_WIDTH_SCALE 0.027
#define STRRET_OFFSET 0.6

RoadHolder::RoadHolder(cocos2d::Vec3 start_pos,cocos2d::Node * renderNode,cocos2d::Sprite3D * player)
{
    Node::init();

    renderNode->addChild(this);

	road[0] = Sprite3D::create("model/road.c3b");
	road[0]->setPosition3D(Vec3(0,0,start_pos.z - STRRET_OFFSET));
	road[0]->setScale(0.1);
	road[0]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	road[0]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	road[0]->setRotation3D(Vec3(0,0,-90));
	renderNode->addChild(road[0]);

	road[1] = Sprite3D::create("model/road.c3b");
	road[1]->setPosition3D(Vec3(MAP_WIDTH-0.2,0,start_pos.z - STRRET_OFFSET));
	road[1]->setScale(0.1);
	road[1]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	road[1]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	road[1]->setRotation3D(Vec3(0,0,-90));
	renderNode->addChild(road[1]);

	road[2] = Sprite3D::create("model/road.c3b");
	road[2]->setPosition3D(Vec3(-MAP_WIDTH+0.2,0,start_pos.z - STRRET_OFFSET));
	road[2]->setScale(0.1);
	road[2]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	road[2]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	road[2]->setRotation3D(Vec3(0,0,-90));
	renderNode->addChild(road[2]);

	renderNode->setCameraMask(2);

    m_player = player;
    m_startPos = start_pos;
}

void RoadHolder::autoLaunch()
{
    this->schedule(schedule_selector(RoadHolder::launch),0);
}

void RoadHolder::launch(float dt)
{
    if((m_startPos - m_player->getPosition3D()).z > 5)
    {
        this->removeFromParent();
        for(int i = 0; i<ROAD_SIZE;i++)
        {
            road[i]->removeFromParent();
        }
    }
}
