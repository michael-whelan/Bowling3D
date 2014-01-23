#include "Pin.h"


Pin::Pin(){
}

Pin::Pin(Ogre::SceneManager *mSceneMgr,Ogre::Vector3 pos,int i){
	mPosition = pos;

	//attatch pin to scene 
	Ogre::String my_string = Ogre::StringConverter::toString(i); 
    pin = mSceneMgr->createEntity("node" + my_string, "column.mesh");
	pin->setMaterialName("Examples/RustySteel");
	Ogre::SceneNode *pinNode = mSceneMgr->createSceneNode("pinNode"+ my_string);
	mSceneMgr->getRootSceneNode()->addChild(pinNode);
	pinNode->attachObject(pin);
	pin->setCastShadows(true);
	float pinModelLength = 100;
	float pinLength = 3;
	double pinScale = pinLength/pinModelLength;
	pinNode->scale(pinScale*2.5, pinScale/1.4, pinScale*2.5);
	pinNode-> setPosition(pos);

	mObjectNode = pinNode;
	mRadius =(pinScale*2.5)/2;
}

Pin::~Pin(){
	
}

void Pin::removePin(){
	mObjectNode->detachAllObjects();
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

void Pin::setPosition(Ogre::Vector3 myPosition) {
	mPosition = myPosition;
}

void Pin::setVelocity(Ogre::Vector3 myVelocity) {
	mVelocity = myVelocity;
}

void Pin::setMove(bool myMove) {
	mMove = myMove;
}


void Pin::setRadius(float rad){
	mRadius = rad;

}

void Pin::initialise(Ogre::SceneNode* myNode,Ogre::Vector3 myPosition)
{
	
}

void Pin::update() {
	
}




