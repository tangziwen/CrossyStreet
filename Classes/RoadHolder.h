#ifndef ROAD_HOLDER_H 
#define ROAD_HOLDER_H  
#include "cocos2d.h"
#define ROAD_SIZE 3
class RoadHolder :public cocos2d::Node {
public:
	RoadHolder(cocos2d::Vec3,cocos2d::Node * renderNode,cocos2d::Sprite3D * player);
    void autoLaunch();
    void launch(float dt);
private:
    cocos2d::Vec3 m_startPos;
    cocos2d::Sprite3D * road[ROAD_SIZE];
    cocos2d::Sprite3D * m_player;
};

#endif // !ROAD_HOLDER_H
