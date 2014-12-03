#include "HelloWorldScene.h"
#include "Player.h"
#include "World.h"
#include "ObjectMatch.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	
    auto camera = Camera::createPerspective(60,visibleSize.width/visibleSize.height,0.01,200);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(1,6,-4));
    camera->setRotation3D(Vec3(-60,0,0));
    Player * player = new Player(this); 
    player->setCam(camera);

	
    auto world =new World(this,player->getPlayer(),camera);
	ObjectMatch::getInstance()->addMatch(player->getPlayer(),player);
    player->setWorld(world);
    this->addChild(camera);
    this->setCameraMask(2);
    

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
    {   
        m_touchBeganPos = touch->getLocation();
        return true; // we did not consume this event, pass thru.
    };

    listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Vec2 touch_end_pos = touch->getLocation();
        Vec2 diff =touch_end_pos-m_touchBeganPos;
        diff.normalize();
        auto a =std::move(Vec2(1,0));//horizontal line
        auto result =Vec2::dot(diff,a);
        if(fabs(result)>0.7)// left or right 
        {
            if(result>0)//right
            {
                player->tryMove(PLAYER_RIGHT);
                CCLOG("right");
            }else //left
            {
                player->tryMove(PLAYER_LEFT);
                CCLOG("left");
            }
        }else{  //up or down 
            if(diff.y>0)
            {
                 player->tryMove(PLAYER_FORWARD);
                 CCLOG("up");
            }else
            {
                player->tryMove(PLAYER_BACKWARD);
                CCLOG("down");
            }
        }
    };
    listener->setSwallowTouches(true);//不向下传递触摸
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::hehe(float dt)
{
    CCLOG("asdads");
}
