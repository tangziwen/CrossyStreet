#include "World.h"
#include "base_Header.h"
#include "RoadHolder.h"
#include <stdlib.h>
USING_NS_CC;
void World::add(cocos2d::Sprite3D * entity)
{
    m_entityList.push_back(entity);
}

void World::Move(cocos2d::Vec2 p_pos, int direction)
{

}



World::World(cocos2d::Node * render_node,cocos2d::Sprite3D * player, cocos2d::Camera * camera)
{
    this->m_renderNode = render_node;
    for(int i=0;i<MAP_HEIGHT;i++)
        for(int j=0;j<MAP_WIDTH;j++)
        {
            m_map[i][j].result=false;
            m_map[i][j].entity=NULL;
        }
        m_currentStreet.type = WORLD_ROAD;
        m_currentStreet.length = 3;
        m_player = player;
        m_camera = camera;
}



void World::generateNewRow(Vec3 playerPostion,int row,bool need_rebase,int offset)
{
    if(need_rebase)  rebase();
    if(m_currentStreet.length<=0)
    {
       
        if(m_currentStreet.type ==WORLD_STREET)
        {
            m_currentStreet.length = rand()%2+1;
            m_currentStreet.type = WORLD_ROAD;
        }else
        {
            m_currentStreet.length = rand()%2+2;
            m_currentStreet.type = WORLD_STREET;
        }
    }

    for(int i =0;i<MAP_WIDTH ;i++)
    {
        if(m_currentStreet.type == WORLD_ROAD)
        {
            if(rand()%10 >= 7)
            {
                auto tree = Sprite3D::create("model/tree.c3t");
                tree->setPosition3D(Vec3(0,0.75,0));//tree's offset
                tree->setScale(0.001);
                tree->setPosition3D(tree->getPosition3D()+Vec3(i-MAP_WIDTH/2,0,playerPostion.z)+Vec3(0,0,-1*row));
                m_renderNode->addChild(tree);
                m_renderNode->setCameraMask(2);
                m_map[MAP_HEIGHT - row -1 - offset ][i].result = true;
                m_map[MAP_HEIGHT - row -1 - offset][i].entity = tree;
            }
            else
            {
                m_map[MAP_HEIGHT - row -1 - offset][i].result =false;
                m_map[MAP_HEIGHT - row -1 - offset][i].entity = NULL;
            }
        }else
        { // do nothing
            m_map[MAP_HEIGHT - row -1 - offset][i].result = false;
            m_map[MAP_HEIGHT - row -1 - offset][i].entity = NULL;
            //generate some car launcher
        }
    }
    if(m_currentStreet.type == WORLD_STREET)
    {
        CarLauncher * launcher = NULL;
        if(rand()%10>=5)// left side
        {
            launcher = new CarLauncher(Vec3(0-MAP_WIDTH/2,0,playerPostion.z)+Vec3(0,0,-1*row),LEFT_SIDE,m_renderNode,m_player);
            launcher->autoLaunch();
        }else //right side
        {
            launcher = new CarLauncher(Vec3(MAP_WIDTH-MAP_WIDTH/2-1,0,playerPostion.z)+Vec3(0,0,-1*row),RIGHT_SIDE,m_renderNode,m_player);
            launcher->autoLaunch();
        }
    }else
	{
		auto roadHolder = new RoadHolder(Vec3(MAP_WIDTH-MAP_WIDTH/2-1,0,playerPostion.z)+Vec3(0,0,-1*row),m_renderNode,m_player);
        roadHolder->autoLaunch();
	}
    m_currentStreet.length--;
}

void World::rebase()
{
    dump();

    for(int i=MAP_HEIGHT-1;i>0;i--)
        for(int j=0;j<MAP_WIDTH;j++)
        {
            m_map[i][j]= m_map[i-1][j];
        }
}

int World::getWordColum(Vec3 pos)
{
    return pos.x+MAP_WIDTH/2;
}

cocos2d::Vec2 World::getPlayerGridPos(Vec3 player_postion,Vec3 cam_position)
{
    Vec2 result;
    result.x = getWordColum(player_postion);
    result.y = cam_position.z - player_postion.z;
    result.y = MAP_HEIGHT - result.y;
    return result;
}



bool World::isBlock(cocos2d::Vec2 pos)
{
    if(pos.x<0 || pos.x>MAP_WIDTH-1 || pos.y <0 || pos.y >MAP_HEIGHT-1)
    {
        return true;
    }
    else
    {
        CCLOG("test block (%d,%d) :%d",(int)(pos.y+0.5),(int)(pos.x+0.5),m_map[(int)pos.y][(int)pos.x].result);
        return m_map[(int)(pos.y+0.5)][(int)(pos.x+0.5)].result;
    }
}

void World::dump()
{
    for(auto i=removeQueue.begin() ;i!=removeQueue.end();i++)
    {
        auto s = (*i);
        s->removeFromParent();
    }
    removeQueue.clear();
    for(int k=0;k<MAP_WIDTH-1;k++)
    {
        if(m_map[MAP_HEIGHT-1][k].entity)
        {
            removeQueue.push_back(m_map[MAP_HEIGHT-1][k].entity);
        }
    }
}

void World::generateRoadOrStreet()
{
}
