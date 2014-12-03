#include "CarLauncher.h"
#include "CCMoveBy3D.h"
#include "base_Header.h"
#include "CarAction.h"
#include "ObjectMatch.h"
#define STREET_MODEL_LENGHT_SCALE 0.3
#define STREET_MODEL_WIDTH_SCALE 0.027
#define STRRET_OFFSET 0.6
USING_NS_CC;

CarLauncher::CarLauncher(cocos2d::Vec3 start_pos,int side,Node *render_node,cocos2d::Sprite3D *player)
{

    Node::init();
    m_startPos = start_pos;
    m_side = side;
    m_renderNode = render_node;
    m_renderNode->addChild(this);
    m_player = player;
	
	street[0] = Sprite3D::create("model/street.c3b");
	street[0]->setPosition3D(Vec3(0,0,start_pos.z - STRRET_OFFSET));
	street[0]->setScale(0.1);
	street[0]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	street[0]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	street[0]->setRotation3D(Vec3(0,0,-90));
	render_node->addChild(street[0]);

	street[1] = Sprite3D::create("model/street.c3b");
	street[1]->setPosition3D(Vec3(MAP_WIDTH-0.2,0,start_pos.z - STRRET_OFFSET));
	street[1]->setScale(0.1);
	street[1]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	street[1]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	street[1]->setRotation3D(Vec3(0,0,-90));
	render_node->addChild(street[1]);

	street[2] = Sprite3D::create("model/street.c3b");
	street[2]->setPosition3D(Vec3(-MAP_WIDTH+0.2,0,start_pos.z - STRRET_OFFSET));
	street[2]->setScale(0.1);
	street[2]->setScaleZ(STREET_MODEL_WIDTH_SCALE);
	street[2]->setScaleY(STREET_MODEL_LENGHT_SCALE);
	street[2]->setRotation3D(Vec3(0,0,-90));
	render_node->addChild(street[2]);
	render_node->setCameraMask(2);
	m_speed = rand()%30 *1.0 /10;
}

void CarLauncher::launch(float dt)
{
    if((m_startPos - m_player->getPosition3D()).z > 5)
    {
        this->removeFromParent();
        for(int i = 0; i<STREET_SIZE;i++)
        {
            street[i]->removeFromParent();
        }
    }

    auto car = Sprite3D::create("model/Cow.c3b");
    car->setPosition3D(m_startPos);
    car->setScale(0.5);
    m_renderNode->addChild(car);
    
    m_renderNode->setCameraMask(2);
    Vec3 dst;
    if(m_side == LEFT_SIDE )
    {
        dst = Vec3(MAP_WIDTH,0,0);
        car->setRotation3D(Vec3(0,90,0));
    }else
    {
        dst = Vec3(-MAP_WIDTH,0,0);
        car->setRotation3D(Vec3(0,-90,0));
    }
    auto move = MoveBy3D::create(4 + m_speed,dst);
    auto seq = Sequence::create(move,   CallFunc::create([=]()
    {
      car->removeFromParent();
    }),NULL);
	void * result =  ObjectMatch::getInstance()->finSecond(m_player);
	CarAction * action = new CarAction((Player * )result);
    car->runAction(seq);
	car->runAction(action);

}

void CarLauncher::autoLaunch()
{
   this->schedule(schedule_selector(CarLauncher::launch),1.0f + m_speed/2);
}


