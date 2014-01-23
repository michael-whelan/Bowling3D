
#ifndef __BOWLINGBALL_h_
#define __BOWLINGBALL_h_
#include <Ogre.h>

class BowlingBall{
private:
	Ogre::Vector3 mPosition; 
	Ogre::Vector3 mVelocity; 
	float mRadius;
	Ogre::SceneNode *mObjectNode; // For the Ogre SceneNode link
	bool mMove;     // If the ball can move or not
	Ogre::Vector3 accel;//used from the physics missile
	float power;//the speed being given to the ball
	bool spacePressed;//checks if space is held down.
	float devtnTmr; //the timer max. This will change depending on power of ball. Higher power more chance of deviation.
	float tmr;//the timer that counts up every frame
	float deviation;//the number that the ball deviates by;
	int deviDirection;//used for left right. 1/0
	bool allowdevi; //turns on and off deviation
	bool gutterBall;
	bool active;
	Ogre::String ballname; 
	
public:
	BowlingBall(void);
	~BowlingBall(void);

	void initialise(Ogre::SceneNode* , Ogre::Vector3, Ogre::Vector3);
	void setPower(float);
	float getPower();
	int getDeviDirection();
	void setDeviDirection(int);
	void setDevtnTmr(float);
	void setActive(bool);
	void update();
	bool getSpacePressed();
	void setSpacePressed(bool);
	Ogre::SceneNode* getNode();
	double getRadius();
	bool getActive();
	void GutterBall();
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getVelocity();
	void setPosition(Ogre::Vector3);
	void setVelocity(Ogre::Vector3);
	void setRadius(float);
	bool getMove();
	void setMove(bool);
	void Reset();
	bool getGutterB();
	void setGutterB(bool);
	Ogre::String getName();
	void setName(Ogre::String);
	Ogre::Entity *sphere;
};
#endif