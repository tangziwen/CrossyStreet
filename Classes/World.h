#ifndef  WORLD_H
#define WORLD_H 
#include "cocos2d.h"
#include <vector>
#include "base_Header.h"
#include "CarLauncher.h"
#define WORLD_UNDEF -1
#define WORLD_STREET 0
#define WORLD_ROAD 1

struct StreetOrRoad{
    int length;
    int type;
    std::vector<CarLauncher*> m_laucherList;
};

struct tile{
    bool result;
    cocos2d::Sprite3D * entity;
};

class World{
public:
    World(cocos2d::Node * render_node,cocos2d::Sprite3D * player, cocos2d::Camera * camera);
    void generateNewRow(cocos2d::Vec3 playerPostion,int row,bool need_rebase =true,int offset = 2);
    void add(cocos2d::Sprite3D * entity);
    void Move(cocos2d::Vec2 p_pos, int direction);
    int getWordColum(cocos2d::Vec3 pos);
    cocos2d::Vec2 getPlayerGridPos(cocos2d::Vec3 player_postion,cocos2d::Vec3 cam_position);
     bool isBlock(cocos2d::Vec2 pos);
     void dump();
    void generateRoadOrStreet();
private:
    cocos2d::Sprite3D * m_player;
    cocos2d::Camera * m_camera;
    StreetOrRoad m_currentStreet;
    std::vector<cocos2d::Sprite3D *> removeQueue;
    std::vector<cocos2d::Sprite3D *> m_entityList;
    cocos2d::Node * m_renderNode;
    tile m_map[MAP_HEIGHT][MAP_WIDTH];
    void rebase();
    int m_currentGenerateType;
};

#endif // ! WORLD_H
