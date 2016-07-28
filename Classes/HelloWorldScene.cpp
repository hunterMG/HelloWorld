#include "HelloWorldScene.h"

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
    
    visibleSize = Director::getInstance()->getVisibleSize();
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

	// add "HelloWorld" splash screen"
	auto bg = Sprite::create("bg.png");

	// position the sprite on the center of the screen
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//sprite->setAnchorPoint(Vec2(1.0, 1.0));
	/*add the sprite as a child to this layer*/
	this->addChild(bg, 0);

	srand(time(NULL));
	theRandomNumber = rand() % 100;
	log("theRandomNumber is %d", theRandomNumber);
	
	buildUI();
	addListeners();

/*
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("My Hello World哈哈", "fonts/Marker Felt.ttf", 24);
	//为了在init()函数外访问lable，给它加上Tag值   auto lable = this->getChildByTag(123);
	label->setTag(123);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

	label->setAnchorPoint(Vec2(0.5, 0.5));
    // add the label as a child to this layer
    this->addChild(label, 1);

	auto tree1 = Sprite::create("tree.png", Rect(1, 15, 236, 217));
	tree1->setPosition(Vec2(100, 120));
	tree1->setAnchorPoint(Vec2(0.0, 0.0));
	this->addChild(tree1, 0);

	Texture2D * cache = Director::getInstance()->getTextureCache()->addImage("tree.png");
	auto tree2 = Sprite::create();
	tree2->setTexture(cache);
	tree2->setTextureRect(Rect(1, 15, 236, 217));
	tree2->setPosition(Vec2(100, 120));
	this->addChild(tree2, 0);
    //创建node1
	auto node1 = Sprite::create("node1.png");
	node1->setPosition(Vec2(100, 100));
	node1->setAnchorPoint(Vec2(1.0, 1.0));
	
	//创建node2
	auto node2 = Sprite::create("node2.png");
	node2->setPosition(Vec2(100, 100));
	node2->setAnchorPoint(Vec2(1.0, 1.0));

	this->addChild(node2, 0);
	this->addChild(node1, 0);

	Vec2 point1 = node1->convertToNodeSpace(node2->getPosition());
	Vec2 point2 = node1->convertToNodeSpaceAR(node2->getPosition());

	log("Node2 NodeSpace = (%f).", point1.x+ point1.y);
	log("Node2 NodeSpaceAR = (%f).", point2.x+ point2.y);
*/
    return true;
}

void HelloWorld::buildUI()
{
	auto lable1 = Label::create();
	lable1->setString("please input a number between 0~100:");
	addChild(lable1);
	lable1->setPosition(visibleSize.width / 2, visibleSize.height -
		lable1->getContentSize().height / 2 - 20);

	tf = TextFieldTTF::textFieldWithPlaceHolder("Input number here:", "Courier", 16);
	tf->setPosition(visibleSize.width / 2, lable1->getPositionY() - 50);
	addChild(tf);

	submitBtn = Label::create();
	submitBtn->setPosition(visibleSize.width / 2, tf->getPositionY() - 50);
	submitBtn->setString("submit");
	addChild(submitBtn);

	messageLable = Label::create();
	messageLable->setPosition(visibleSize.width / 2, submitBtn->getPositionY() - 50);
	addChild(messageLable);

}
void HelloWorld::addListeners(){
	auto director = Director::getInstance();
	auto handler = [this](Touch *t, Event *e) {
		auto target = e->getCurrentTarget();
		auto point = t->getLocation();
		if (target->getBoundingBox().containsPoint(point)) {
			if (target==tf)
			{
				tf->attachWithIME();
			}
			else if (target ==submitBtn)
			{
				tf->detachWithIME();
				log("submit");
				int inputValue = __String::create(tf->getString())->intValue();
				if (inputValue > theRandomNumber) {
					messageLable->setString("input is bigger!");
				}
				else if (inputValue < theRandomNumber) {
					messageLable->setString("input is smaller!");
				}
				else {
					messageLable->setString("right!!!");
				}

			}
		}
		else
		{
			tf->detachWithIME();
		}
		return false;
	};

	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = handler;
	director->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(listen, tf);
	
	auto submitListener = EventListenerTouchOneByOne::create();
	submitListener->onTouchBegan = handler;
	director->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(submitListener, submitBtn);

}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
