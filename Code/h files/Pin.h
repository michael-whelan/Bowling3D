#ifndef __PIN_h_
#define __PIN_h_
#include <Ogre.h>

class Pin{
private:
	Ogre::Vector3 mPosition; 
	Ogre::Vector3 mVelocity; 
	double mRadius;
	Ogre::SceneNode *mObjectNode; // For the Ogre SceneNode link
	bool mMove;     // If the missile can move or not
	Ogre::Entity *pin;

public:
	Pin(void);
	Pin(Ogre::SceneManager*,Ogre::Vector3,int);
	~Pin(void);
	void update();
	Ogre::SceneNode* getNode();
	double getRadius();
	void initialise(Ogre::SceneNode* , Ogre::Vector3);
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getVelocity();
	void setPosition(Ogre::Vector3);
	void setVelocity(Ogre::Vector3);
	bool getMove();
	void setRadius(float);
	void setMove(bool);
	void Reset();
	void removePin();
	void addPin();
};
#endif