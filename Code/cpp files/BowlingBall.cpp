#include "BowlingBall.h"

BowlingBall::BowlingBall(void){
	power = 1;
	spacePressed = false;
	tmr = 0.0f;
	deviation=0;
	devtnTmr = 0;
	deviDirection = 1;
	allowdevi = true;
	gutterBall = false;
	ballname = "1";
	roll = 0;
	maxPower = 15;
	mFriction = 0.0f;
	mMass = 6;
}

BowlingBall::~BowlingBall(void) {

}

Ogre::Vector3 BowlingBall::getPosition() {
	return mPosition;
}

Ogre::Vector3 BowlingBall::getVelocity() {
	return mVelocity;
}

Ogre::SceneNode* BowlingBall::getNode(){
	return mObjectNode;
}

float BowlingBall::getMass(){
	return mMass;
}

bool BowlingBall::getActive(){
	return active;
}

double BowlingBall::getRadius() {
	return mRadius;
}

int BowlingBall::getDeviDirection(){
	return deviDirection;
}

void BowlingBall::setDeviDirection(int f){
	deviDirection = f;
}

bool BowlingBall::getMove() {
	return mMove;
}

bool BowlingBall::getGutterB(){
	return gutterBall;
}

bool BowlingBall::getSpacePressed(){
	return spacePressed;
}

Ogre::String BowlingBall::getName(){
	return ballname;
}

int BowlingBall::getMaxPower(){
	return maxPower;
}

void BowlingBall::setName(Ogre::String s){
	ballname = s;
}

void BowlingBall::setGutterB(bool GB){
	gutterBall = GB;
}

void BowlingBall::setActive(bool b){
	active = b;
}

void BowlingBall::setDevtnTmr(float f){
	devtnTmr = f;
}

void BowlingBall::setSpacePressed(bool b){
	spacePressed = b;
}

void BowlingBall::setPosition(Ogre::Vector3 myPosition) {
	mPosition = myPosition;
	mObjectNode->setPosition(mPosition);
}

void BowlingBall::setVelocity(Ogre::Vector3 myVelocity) {
	mVelocity = myVelocity;
}

void BowlingBall::setMove(bool myMove) {
	mMove = myMove;
}

void BowlingBall::setRadius(float rad){
	mRadius = rad;
}

void BowlingBall::initialise(Ogre::SceneNode* myNode,Ogre::Vector3 myPosition,Ogre::Vector3 myVelocity)
{
	mObjectNode = myNode; // The scene node for the model
	setMove(false); // Or to true if you want the sphere to move now
	mVelocity = myVelocity; // fix velocity
	mPosition = myPosition; // fix position
	mMove = false;
	mRadius = 0;
}

void BowlingBall::setPower(float p){
	power = p;
}

float BowlingBall::getPower(){
	return power;
}

void BowlingBall::update() {

	if(mMove){
		if(allowdevi){
			if(tmr>= devtnTmr){
				if(deviDirection==1){
					deviation+= 0.002;
				}
				else{deviation -= 0.002;}
				tmr=0;
			}
		}
	}

	//increase friction
	mFriction=-(mVelocity.z/250);

	mPosition = mPosition + Ogre::Vector3(mVelocity.x+deviation,mVelocity.y,mVelocity.z); //Next position
	if(mVelocity.z >-1.10){ //checks the speed and rolls if under a certain amount

		mObjectNode->pitch(-((Ogre::Radian)0.09*Ogre::Math::PI/180)*8*power ,Ogre::Node::TS_WORLD);//rolls ball
		mObjectNode->roll((Ogre::Radian)mVelocity.x*Ogre::Math::PI/180 ,Ogre::Node::TS_WORLD);

	}
	else if (!gutterBall){
		mVelocity.z += mFriction;//if ball is over a speed friction slows it down
	}

	mObjectNode->setPosition(mPosition);
	tmr++;





	if(mPosition.z <=-340){//stops ball at end of lane
		deviation = 0;
		allowdevi=false;
	}
	else{GutterBall();}
}

void BowlingBall::GutterBall(){
	if(mPosition.x>= 30){
		mPosition = Ogre::Vector3(30,2,mPosition.z);
		mVelocity.z = power*-1/30;
		if(mVelocity.z>-0.1){
			mVelocity.z = -0.2;
		}
		allowdevi = false;
		gutterBall = true;
	}
	else if(mPosition.x<=-30){
		mPosition = Ogre::Vector3(-30,2,mPosition.z);
		mVelocity.z = power*-1/30;
		if(mVelocity.z>-0.1){
			mVelocity.z = -0.2;
		}
		allowdevi = false;
		gutterBall=true;
	}
}




Ogre::SceneNode* getNode();//returns SceneNode pointer
double getRadius();  // returns m_radius
bool getMove();  // returns m_move


void BowlingBall::Reset(){
	mPosition = Ogre::Vector3(0,3,0);
	deviation = 0;
	allowdevi=true;
	mMove = false;
	gutterBall = false;
	mFriction = 0;
}


