
#ifndef __BOWLINGBALL_h_
#define __BOWLINGBALL_h_
#include <Ogre.h>

class BowlingBall{
private:
	Ogre::Vector3 mPosition; 
	Ogre::Vector3 mVelocity; 
	float mFriction;//stops ball from sliding along the plane
	float mRadius;
	Ogre::SceneNode *mObjectNode; 
	bool mMove;     // If the ball is moving or not
	Ogre::Vector3 accel;//used from the physics missile
	float power;//the speed being given to the ball
	bool spacePressed;//checks if space is held down.
	float devtnTmr; //the timer max. This will change depending on power of ball. Higher power more chance of deviation.
	float tmr;//the timer that counts up every frame
	float deviation;//the number that the ball deviates by;
	int deviDirection;//used for left right. 1/0
	bool allowdevi; //turns on and off deviation
	bool gutterBall;//sets true if the ball enters the gutter 
	bool active;
	Ogre::String ballname; //determins which player owns the ball
	float roll;//used to rotate the ball when it moves
	int maxPower;//the limit to the power
	float mMass;//mass of the ball used in the collisions with the pin
	
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
	int getMaxPower();
	void update();//controls the movement of the ball and controls deviation of movement
	bool getSpacePressed();
	void setSpacePressed(bool);
	Ogre::SceneNode* getNode();
	double getRadius();
	bool getActive();
	void GutterBall();//sets the velocity of the ball to follow the gutter
	Ogre::Vector3 getPosition();
	Ogre::Vector3 getVelocity();
	void setPosition(Ogre::Vector3);
	void setVelocity(Ogre::Vector3);
	void setRadius(float);
	bool getMove();
	void setMove(bool);
	void Reset();//puts the ball back to is start position and puts everything back to initial values.
	bool getGutterB();
	void setGutterB(bool);
	Ogre::String getName();
	void setName(Ogre::String);
	Ogre::Entity *sphere;
		float getMass();
};
#endif