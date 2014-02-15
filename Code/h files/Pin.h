#ifndef __PIN_h_
#define __PIN_h_
#include <Ogre.h>


class Pin{
private:
	Ogre::Vector3 mPosition; 
	Ogre::Vector3 mVelocity;
	Ogre::Vector3 oriPosition; 
	double mRadius;
	Ogre::SceneNode *mObjectNode; // For the Ogre SceneNode link
	bool mMove,mFalling,mFell,mBallAttempt,mPinAttempt,mStopFallCnt;     // If the missile can move or not
	Ogre::Entity *pin;
	float mMass,mFriction,mSpeed;//attributes of the pin
	Ogre::Quaternion mOrientation;
	int counter;
	Ogre::Radian rad;
	float inertia;//initial inertia of the pin/ Higher = harder to move = harder to strike
	int wobbleDirection,wobbleSpeed;
	bool mWobble;
	

public:
	Pin(void);
	Pin(Ogre::SceneManager*,Ogre::Vector3,int);
	~Pin(void);
	void update();//controls all the movement of the pin
	Ogre::SceneNode* getNode();
	double getRadius();
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getVelocity();
	void setPosition(Ogre::Vector3);
	void setVelocity(Ogre::Vector3);
	bool getMove();
	bool getFalling();
	void setMove(Ogre::Vector3,float);
	void Reset();//resets the pin to its initial position and values
	void removePin();//removes the pin from the board. Contolled by pin manager
	void addPin();
	void bounds();
	void pinFall(Ogre::Vector3);//causes the pin to fall in a given direction
	void pinFallCheck(Ogre::Vector3,Ogre::Vector3,float);//determines if the pin should fall and if so what direction it should move in
	void inertiaCheck(float,Ogre::Vector3,Ogre::Vector3,float);//allows the pin to move onto the next phase either wobble or fal depending on how far above inertia the hit was.
	float getMass();
	bool getFell();
	bool getFallCnt();//a bool to make sure pins are only counted once
	void setFallCnt(bool);
	float getSpeed();
	bool getBallAttempt();//checks if a ball tried to knock this pin
	void setBallAttempt(bool);
	bool getPinAttempt();//checks if a pin tried to knock this pin
	void setPinAttempt(bool);
	void pinWobble();//controls the wobble counter
	
};

#endif