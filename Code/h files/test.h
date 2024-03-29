/*
-----------------------------------------------------------------------------
Filename:    test.h
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC10 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/
#ifndef __test_h_
#define __test_h_

#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif
#include "OgreVector3.h"
#include "OgreVector3.h"



class test : public BaseApplication
{
public:
    test(void);
    virtual ~test(void);
		Ogre::Vector3 mVelocity;

protected:
	 void createGamePanel();//creates the different GUI objects
    virtual void createScene(void);//creates all initial objects needed including GUI
	virtual void createBall(void);//creates the ball 
	virtual void createPin(void);//creates the pin
	virtual void createArrow(void);//creates the arrow
};

#endif // #ifndef __test_h_
