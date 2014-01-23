/*
-----------------------------------------------------------------------------
Filename:    Practical1.cpp
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

#include "test.h"
//-------------------------------------------------------------------------------------
test::test(void)
{
}
//-------------------------------------------------------------------------------------
test::~test(void)
{
}

//-------------------------------------------------------------------------------------
void test::createScene(void)
{
	// Create the ground with grass on it
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
	plane.d = 0;//Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("floor",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,80,400,10,10,true,1,1,1,Ogre::Vector3::UNIT_Z);
	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
	pPlaneEnt->setMaterialName("Examples/BowlingAlley");
	pPlaneEnt->setCastShadows(false);
	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);
	floorNode->setPosition(0,0,-150);

	// Set ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	// Create a light
	Ogre::Light* l = mSceneMgr->createLight("MainLight");
	l->setPosition(20,80,50);
	mSceneMgr->setSkyDome(true,"Examples/CloudySky",5,8);
	createBall();
	
	createArrow();

	collisionManager = new CollisionManager();
	pinManager = new PinManager();
	pinManager->PlacePins(mSceneMgr);
}

void test::createBall(void){

	mBallObject = new BowlingBall();
	mBallObject->sphere = mSceneMgr->createEntity(mBallObject->getName(), "sphere.mesh");
	// Choose a material texture for the cube
	

	Ogre::SceneNode *sphereNode = mSceneMgr->createSceneNode("sphereNode");
	mSceneMgr->getRootSceneNode()->addChild(sphereNode);
	sphereNode->attachObject(mBallObject->sphere);
	mBallObject->sphere->setCastShadows(true);
	float sphereModelLength = 100;
	float sphereLength = 3;

	// Change size of graphics cube to that of cubeLength
	double sphereScale = sphereLength/sphereModelLength;

	sphereNode->scale(sphereScale, sphereScale, sphereScale);

	// Position the cube to sit exactly on the ground
	sphereNode-> setPosition(Ogre::Vector3(0, sphereLength,0));

	
	// Now initialise all of it�s properties to match the //graphics model of the sphere as in ballNode
	mBallObject->initialise(sphereNode,sphereNode->getPosition(),Ogre::Vector3(1,0,0));
	double sphereRadius = sphereScale/2;  // To store actual radius used here
	mBallObject->setRadius(sphereRadius);
}

void test::createPin(void){
	Ogre::Entity *pin = mSceneMgr->createEntity("pin", "column.mesh");

	//pin->setMaterialName("PinMat");

	Ogre::SceneNode *pinNode = mSceneMgr->createSceneNode("pinNode");
	mSceneMgr->getRootSceneNode()->addChild(pinNode);
	pinNode->attachObject(pin);
	pin->setCastShadows(true);
	float pinModelLength = 100;
	float pinLength = 3;


	double pinScale = pinLength/pinModelLength;


	pinNode->scale(pinScale*2.5, pinScale/1.4, pinScale*2.5);

	pinNode-> setPosition(Ogre::Vector3(0, pinLength,-280));

}

void test::createArrow(void){

	Ogre::Entity *arrow = mSceneMgr->createEntity("arrow", "Column.mesh");

	arrow->setMaterialName("Examples/Hilite/Yellow");

	Ogre::SceneNode *arrowNode = mSceneMgr->createSceneNode("arrowNode");
	mSceneMgr->getRootSceneNode()->addChild(arrowNode);
	arrowNode->attachObject(arrow);
	arrow->setCastShadows(true);
	float arrowModelLength = 100;
	double arrowModelRadius = 2.7; // the exact radius of the mesh for // tfhe arrowinder model
	double arrowModelHeight = 6.2; // the exact length of the mesh for // arrowinder model
	float arrowLength = 3;
	double arrowRadius = 0.3;  // The new radius for graphics arrowinder

	double arrowScale = arrowLength/arrowModelLength;


	arrowNode->scale((arrowRadius/arrowModelRadius)/4, (arrowLength/arrowModelHeight)/10, (arrowRadius/arrowModelRadius)/4);

	arrowNode-> setPosition(mBallObject->getPosition().x,10.0f,mBallObject->getPosition().z);
	arrowNode->pitch(Ogre::Degree(90));
	mArrowObject = new Arrow(arrowNode,arrowNode->getPosition(),(float)arrowRadius,(float)arrowLength,(float)4);
	mArrowObject->initialize();
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		test app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
