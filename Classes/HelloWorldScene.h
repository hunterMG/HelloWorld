#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	int theRandomNumber;
	cocos2d::Size visibleSize;
	cocos2d::TextFieldTTF *tf;
	cocos2d::Label *submitBtn,*messageLable;
	void addListeners();
	void buildUI();
};

#endif // __HELLOWORLD_SCENE_H__
