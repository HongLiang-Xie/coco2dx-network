#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"NetManager.h"
#include"GameUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    /**  you can create scene with following comment code instead of using csb file.
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

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
	auto loginNode = CSLoader::createNode("login.csb");
	auto  m_node = dynamic_cast<Node*>(rootNode->getChildByTag(6));
	loginNode->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_node->addChild(loginNode);
	auto login = dynamic_cast<ui::Button*>(loginNode->getChildByTag(11));
	login->addClickEventListener(CC_CALLBACK_1(HelloWorld::ClickLogin, this));
    addChild(rootNode);
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(
		"Login", CC_CALLBACK_1(HelloWorld::Login, this));



    return true;


}

void HelloWorld::Login(cocos2d::EventCustom * data)
{
	
	
	MsgPacket* _MP = (MsgPacket*)(data->getUserData());
	if (_MP == NULL || this == NULL)return;
	pb::login msg;
	msg.ParseFromArray(_MP->data, _MP->datalen);
	switch (msg.returntype())
	{
	case 1:
		dynamic_cast<ui::Text*> (this->getChildByTag(0)->getChildByTag(13))->setString("success");
		Director::getInstance()->replaceScene(GameUI::createScene());
		break;
	case 3:
		dynamic_cast<ui::Text*> (this->getChildByTag(0)->getChildByTag(13))->setString("failed");
		Director::getInstance()->replaceScene(GameUI::createScene());
		break;
	default:
		break;
	}


}

void HelloWorld::ClickLogin(Ref * _psender)
{


		pb::login login;
		login.set_type(1);
		login.set_returntype(0);
		login.set_userid(dynamic_cast<ui::TextField*> (this->getChildByTag(0)->getChildByTag(6)->getChildByTag(7)->getChildByTag(9))->getString());
		login.set_password(dynamic_cast<ui::TextField*> (this->getChildByTag(0)->getChildByTag(6)->getChildByTag(7)->getChildByTag(10))->getString());
		MsgPacket*_MP = NetManager::GetInterface()->Packages(1, dynamic_cast<google::protobuf::Message*>(&login));
		NetManager::GetInterface()->wb.send((unsigned char*)_MP, _MP ->datalen+8);


}
	
	
