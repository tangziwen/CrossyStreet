#include "Player.h"
#include "CCMoveBy3D.h"
#include "CCJumpBy3D.h"
#include "RoadHolder.h"
USING_NS_CC;
Player::Player(Node * render_node)
{
    auto ambient_light = AmbientLight::create(Color3B(100,100,100));
    render_node->addChild(ambient_light);
    auto point_light  = PointLight::create(Vec3(0,10,0),Color3B(255,255,0),4);
    m_player = Sprite3D::create("model/Steve.c3b");
    m_player->addChild(point_light);
    m_player->setPosition3D(Vec3(0,0,-5));
    m_player->setScale(0.1);
    m_player->setRotation3D(Vec3(0,90,0));
    render_node->addChild(m_player);
    render_node->setCameraMask(2);
    m_direction = PLAYER_FORWARD;
	m_isAlive = true;
    m_renderNode = render_node;
}

cocos2d::Sprite3D * Player::getPlayer()
{
    return this->m_player;
}

void Player::tryMove(int direction)
{
	if(!m_isAlive) return;
    if(m_direction == direction)
    {
        move(direction);
        //move(direction);
    }else
    {
        //turn to;
        m_direction = direction;
        turn(m_direction);
        move(direction);
    }
}

void Player::turn(int direction)
{
    switch (direction)
    {
    case PLAYER_RIGHT:
        m_player->setRotation3D(Vec3(0,0,0));
        break;
    case PLAYER_LEFT:
        m_player->setRotation3D(Vec3(0,180,0));
        break;
    case PLAYER_FORWARD:
        m_player->setRotation3D(Vec3(0,90,0));
        break;
    case PLAYER_BACKWARD:
        m_player->setRotation3D(Vec3(0,-90,0));
        break;
    default:
        break;
    }
}

void Player::move(int direction)
{
    Vec2 pos =m_world->getPlayerGridPos(m_player->getPosition3D(),m_cam->getPosition3D());
    CCLOG("player grid postion %g %g",pos.x,pos.y);
    switch (direction)
    {
    case PLAYER_RIGHT:
        {
            if(m_world->isBlock(pos+Vec2(1,0)))
            {
                return ;
            }
            auto jump = JumpBy3D::create(0.2,Vec3(1,0,0),1,1);
            m_player->runAction(jump);
           // m_player->setPosition3D(m_player->getPosition3D()+Vec3(1,0,0));
           
            {
                auto move = MoveBy3D::create(0.3,Vec3(1,0,0));
                m_cam->runAction(move);
            }
        }
        break;
    case PLAYER_LEFT:
        {
            if(m_world->isBlock(pos+Vec2(-1,0)))
            {
                return ;
            }
            auto jump = JumpBy3D::create(0.2,Vec3(-1,0,0),1,1);
            m_player->runAction(jump);
        //m_player->setPosition3D(m_player->getPosition3D()+Vec3(-1,0,0));
        {
            auto move = MoveBy3D::create(0.3,Vec3(-1,0,0));
            m_cam->runAction(move);
        }
        }
        
        break;
    case PLAYER_FORWARD:
        {
            if(m_world->isBlock(pos+Vec2(0,-1)))
            {
                return ;
            }
            auto jump = JumpBy3D::create(0.2,Vec3(0,0,-1),1,1);
            m_player->runAction(jump);
            //m_player->setPosition3D(m_player->getPosition3D()+Vec3(0,0,-1));
            if(m_player->getPosition3D().z < m_cam->getPosition3D().z-3)
            {
                m_score++;
                auto move = MoveBy3D::create(0.3,Vec3(0,0,-1));
                m_cam->runAction(move);
                m_world->generateNewRow(m_player->getPosition3D(),7);
            }
        }

        break;
    case PLAYER_BACKWARD:
        {
            if(m_world->isBlock(pos+Vec2(0,1)))
            {
                return ;
            }
            if(m_player->getPosition3D().z+1 < m_cam->getPosition3D().z)
            {
                auto jump = JumpBy3D::create(0.2,Vec3(0,0,1),1,1);
                m_player->runAction(jump);
            }
        }
        break;
    default:
        break;
    }
}
void Player::setCam(cocos2d::Camera *cam)
{
    m_cam = cam;
}

void Player::setWorld(World * wolrd)
{

    m_world = wolrd;
    auto roadHolder = new RoadHolder(Vec3(MAP_WIDTH-MAP_WIDTH/2-1,0,this->getPlayer()->getPositionZ())+Vec3(0,0,1),m_renderNode,this->getPlayer());
    roadHolder->autoLaunch();
    for(int i =0 ;i<= 9;i++)
    {
        m_world->generateNewRow(m_player->getPosition3D(),i,false,0);
    }
}

void Player::hurt()
{
	if(m_isAlive)
	{
		//auto scaleTo = ScaleTo::create(1,1,0.5,1);
		//m_player->runAction(scaleTo);
	
		//test code
		auto x = m_player->getScaleX();
		auto y = m_player->getScaleY();
		auto z =m_player->getScaleZ();
		m_player->setScaleX(x);
		m_player->setScaleY(y*0.1);
		m_player->setScaleZ(z);
		m_player->removeAllChildren();
		m_isAlive = false;
	}
}

int Player::score()
{
    return m_score;
}

void Player::setScore(int new_score)
{
    m_score = new_score;
}


