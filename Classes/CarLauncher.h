#ifndef CAR_LAUNCHER_H
#define CAR_LAUNCHER_H  
#include "cocos2d.h"
#define LEFT_SIDE 0
#define RIGHT_SIDE 1
#define STREET_SIZE 3
class CarLauncher :public cocos2d::Node
{
public:
    CarLauncher(cocos2d::Vec3 start_pos,int side,cocos2d::Node * render_node,cocos2d::Sprite3D * player);
    void launch(float dt);
    void autoLaunch();
private:
    cocos2d::Sprite3D * m_player;
    cocos2d::Node * m_renderNode;
    cocos2d::Vec3 m_startPos;
    cocos2d::Sprite3D *street[STREET_SIZE];
    int m_side;
	float m_speed;
};
#endif // !CarLauncher
