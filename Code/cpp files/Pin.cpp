#include "Pin.h"


Pin::Pin(){
}

Pin::Pin(Ogre::SceneManager *mSceneMgr,Ogre::Vector3 pos,int i)
	:mMove(false),mFalling(false),mFriction(0.005),mMass(1.5),counter(0),mSpeed(0.18),inertia(4),mFell(false),mBallAttempt(false),mPinAttempt(false),
	mWobble(false),wobbleDirection(-1),wobbleSpeed(40)
{
	mPosition = pos;
	oriPosition = pos;
	//attatch pin to scene 
	Ogre::String my_string = Ogre::StringConverter::toString(i); 
    pin = mSceneMgr->createEntity("node" + my_string, "Cylinder.002.mesh");
	pin->setMaterialName("Scene.material");
	Ogre::SceneNode *pinNode = mSceneMgr->createSceneNode("pinNode"+ my_string);
	mSceneMgr->getRootSceneNode()->addChild(pinNode);
	pinNode->attachObject(pin);
	pin->setCastShadows(true);
	float pinModelLength = 100;
	float pinLength = 3;
	double pinScale = pinLength/pinModelLength;
		pinNode->scale(pinScale*25, pinScale*25, pinScale*25);
	pinNode-> setPosition(pos);

	mObjectNode = pinNode;
	mRadius =(pinScale*2.5)/2;
	mVelocity = Ogre::Vector3::ZERO;

}

Pin::~Pin(){
	
}

void Pin::removePin(){
	mObjectNode->detachAllObjects();
	mPosition = oriPosition;
	mMove = false;
	mSpeed = 0.15;
	//mObjectNode->pitch((Ogre::Radian)Ogre::Math::PI/2,Ogre::Node::TS_WORLD);
	//mObjectNode->roll(-rad,Ogre::Node::TS_WORLD);
	mObjectNode->setOrientation(Ogre::Quaternion(1,0,0,0));
	mFalling = false;
	mFell = false;
	mStopFallCnt = false;
	mVelocity = Ogre::Vector3::ZERO;
	counter = 0;
}

void Pin::addPin(){
	int numChild = mObjectNode->numAttachedObjects();
	if(numChild == 0)
		mObjectNode->attachObject(pin);
}

Ogre::Vector3 Pin::getPosition(){
	return mPosition;
}

Ogre::SceneNode* Pin::getNode(){
	return mObjectNode;
}

double Pin::getRadius() {
	return mRadius;
}
bool Pin::getMove() {
	return mMove;
}
float Pin::getSpeed(){
	return mSpeed;
}

Ogre::Vector3 Pin::getVelocity(){
	return mVelocity;
}

bool Pin::getFalling() {
	return mFalling;
}

void Pin::setPosition(Ogre::Vector3 myPosition) {
	mPosition = myPosition;
}

void Pin::setVelocity(Ogre::Vector3 myVelocity) {
	mVelocity = myVelocity;
}

float Pin::getMass(){
	return mMass;
}

bool Pin::getFell(){
	return mFell;
}
bool Pin::getFallCnt(){
	return mStopFallCnt;
}

void Pin::setFallCnt(bool b){
	mStopFallCnt = b;
}

bool Pin::getBallAttempt(){
	return mBallAttempt;
}

void Pin::setBallAttempt(bool b){
	 mBallAttempt = b;
}

bool Pin::getPinAttempt(){
	return mPinAttempt;
}

void Pin::setPinAttempt(bool b){
	 mPinAttempt = b;
}

void Pin::setMove(Ogre::Vector3 objectPos,float objectYVel) {
	mMove = true;
	Ogre::Radian rad = Ogre::Math::ATan((objectPos.z - mPosition.z)/((objectPos.x - mPosition.x)));
	


	mVelocity.x = Ogre::Math::Cos(rad);
	mVelocity.z = Ogre::Math::Sin(rad);
	
	if(objectPos.x >= mPosition.x)
		mVelocity *= -1;
	mVelocity *= objectYVel;
	if(!mFalling)
		pinFall(objectPos);
}

void Pin::pinFall(Ogre::Vector3 objectPos){
	mFalling = true;
		mStopFallCnt = true;
	rad = (Ogre::Radian)Ogre::Math::PI/2 - rad;
	mObjectNode->roll(rad,Ogre::Node::TS_WORLD);
}

void Pin::pinFallCheck(Ogre::Vector3 objectPos,Ogre::Vector3 objectVelocity,float objectMass){
	Ogre::Radian objectRadian = Ogre::Math::ATan((objectVelocity.z)/(objectVelocity.x));
	rad = Ogre::Math::ATan((objectPos.z - mPosition.z)/((objectPos.x - mPosition.x)));

	if(objectRadian.valueRadians() < 0)
		objectRadian = Ogre::Math::PI + objectRadian.valueRadians();
	if(rad.valueRadians() < 0)
		rad = Ogre::Math::PI + rad.valueRadians();
	
	if(objectPos.x <= mPosition.x){
		inertiaCheck(rad.valueRadians() - objectRadian.valueRadians(),objectVelocity,objectPos,objectMass);
	}
	else if(objectPos.x >= mPosition.x){
		inertiaCheck( objectRadian.valueRadians() - rad.valueRadians(),objectVelocity,objectPos,objectMass);
	}
}

void Pin::pinWobble(){
       mWobble = true;
       counter -= 20;
}

void Pin::inertiaCheck(float radian,Ogre::Vector3 objectVelocity,Ogre::Vector3 objectPos,float objectMass){
	if(radian <= 0)
		radian = 0.1;

	float colForce = ((objectVelocity.z*-1)/(radian*radian)) * objectMass; 

	if(colForce > inertia){
		setMove(objectPos,(objectVelocity.z*-1));
		mSpeed *= objectMass;
		if(objectMass == 6)
			mBallAttempt = true;
		else
			mPinAttempt = true;
	}

	else if(colForce < inertia){
		if(objectMass == 6){
                     mBallAttempt = true;
                     if(!mPinAttempt)
                           pinWobble();
              }
             
              else if(objectMass == 1.5){
                     mPinAttempt = true;
                     if(!mBallAttempt)
                           pinWobble();
              }
	}
}

void Pin::update() {
	if(mFalling){
		counter++;

		mObjectNode->pitch(-(Ogre::Radian)Ogre::Math::PI/180,Ogre::Node::TS_WORLD);
		if(counter <= 45)

			mPosition.y += 1/45;
		else 
			mPosition.y -= 1/45;

		if(counter >= 90){
			mFalling = false;
			mFell = true;
		
		}
	}

	if(mMove){
		mPosition += mVelocity*mSpeed;

		if(!mFalling)
			mSpeed -= mFriction;
		if(mSpeed <= 0)
			mSpeed = 0;
	}
	if(mWobble){
             
              mObjectNode->pitch((wobbleDirection)*(Ogre::Radian)Ogre::Math::PI/360,Ogre::Node::TS_WORLD);
             
              if(counter % wobbleSpeed == 0 || counter == 0){
                     wobbleDirection *= -1;
              }
 
              if(counter >= 220){
                     mWobble = false;
                     counter = 0;
              }
              counter++;
       }

	mObjectNode->setPosition(mPosition);

	//if(mSpeed ==0 && mFell)
	//	removePin();
}

void Pin::bounds(){
	if(mPosition.x > 30 || mPosition.x < -30 || mPosition.z < -340)
		removePin();
}






