#include "Shuffleboard.h"


Shuffleboard * Shuffleboard::mInstance = 0;

//-------------------------------------------------------------------------------------
Shuffleboard::Shuffleboard( SceneManager *sceneMan ) :
	mSceneMgr( sceneMan ), mForce(0),gameOn(true),
mMinExtentsOuter( GameConstants::MIN_EXTENTS_OUTER ),
mMaxExtentsOuter( GameConstants::MAX_EXTENTS_OUTER ),
mMinExtentsInner( GameConstants::MIN_EXTENTS_INNER ),
mMaxExtentsInner( GameConstants::MAX_EXTENTS_INNER ),
mBoxOuter( mMinExtentsOuter, mMaxExtentsOuter ),
mBoxInner( mMinExtentsInner, mMaxExtentsInner )
	{



	initialise();
}

//-------------------------------------------------------------------------------------
void Shuffleboard::initialise() {

	// Create the Shuffleboard.
	Entity * ent = mSceneMgr->createEntity("Shuffleboard", "Shuffleboard.mesh");
	SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeShuffleboard");
	node->attachObject( ent );	
	node->setPosition( 0, 0, 0);
	// Create the Arrow.
ent = mSceneMgr->createEntity("Arrow", "arrow.mesh");
mArrow = mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeArrow");
mArrow->attachObject( ent );
mArrow->setPosition( 5, 4, 15 );
mArrow->yaw( Ogre::Degree(90) );

}

void Shuffleboard::setArrowVisible(bool visible) {
mArrow->setVisible( visible );
}


//---------------------------------------------------------------------------------
void Shuffleboard::updateScore() {
std::vector<Puck *> usedPucks = PuckManager::instance()->getUsedPucks();
int score = 0;
if(gameOn){
if ( usedPucks.empty() == false ) {
		sort( usedPucks.begin(), usedPucks.end(), PuckComparer() );
		Puck::PuckType puckType = usedPucks.at(0)->getPuckType();
		std::vector<Puck *>::iterator curr = usedPucks.begin();
		std::vector<Puck *>::iterator end = usedPucks.end();
	for ( ; curr != end && puckType == (*curr)->getPuckType() ; ++curr ) {
		score += getScore( (*curr)->getPosition().z );
		puckType = (*curr)->getPuckType();
		}
	if ( puckType == Puck::YELLOWSTONE ) {
		TextRenderer::getSingleton().setText("YellowScore", "Yellow: "
		+ Ogre::StringConverter::toString( score ) );
		TextRenderer::getSingleton().setText("RedScore", "Red: " +
		Ogre::StringConverter::toString( 0 ) );
		}
	else {
		TextRenderer::getSingleton().setText("RedScore", "Red: " +
		Ogre::StringConverter::toString( score ) );
		TextRenderer::getSingleton().setText("YellowScore", "Yellow: "
		+ Ogre::StringConverter::toString( 0 ) );
		}
	}
}
else
	{
		TextRenderer::getSingleton().setText("GameOver", "Game Over\n Press R to Restart");		
	}
}


void Shuffleboard::launchPuck() {
Puck * puck = PuckManager::instance()->getNextPuck();

if ( puck != 0 ) {
	Ogre::Real centreX = ( GameConstants::MAX_X - GameConstants::MIN_X ) / 2 +
GameConstants::MIN_X;
Ogre::Vector3 launchPos( centreX, GameConstants::LAUNCH_Y,
GameConstants::LAUNCH_Z );
		 puck->activate(launchPos);
		  puck->setDirection(mArrow->getOrientation() * Vector3::UNIT_X, true);
		  mForce+=3;
		puck->applyForce( mForce );
		
		 // Reset the force and the arrow orientation.
mForce = 0;
resetArrowOrientation();
}
else 
{
	gameOn = false;
}
}


//-------------------------------------------------------------------------
int Shuffleboard::getScore(Ogre::Real const & zPos) {
int score = 0;
if(zPos <= GameConstants::SCORING_LINE_3)
{
	score= GameConstants::SCORING_LINE_3_SCORE;
}
else if (zPos <= GameConstants::SCORING_LINE_2)
{
	score = GameConstants::SCORING_LINE_2_SCORE;
}
else if(zPos <= GameConstants::SCORING_LINE_1)
{
	score = GameConstants::SCORING_LINE_1_SCORE;
}
return score;

}



bool Shuffleboard::getInputForce() {
	
bool getInputForce = true;
mForce += ( Ogre::Math::Pow(2.0f, mForce ) *
GameConstants::PUCK_FORCE_MULTIPLIER );
// draw the HUD line with mTotalElapsedTime sizing x -axis.
DebugDrawer::getSingleton().drawQuad( mBoxOuter.getAllCorners(),
Ogre::ColourValue(0, 1.0f, 0) );
if ( mMaxExtentsInner.x + mForce < mMaxExtentsOuter.x ) {
mBoxInner.setExtents( mMinExtentsInner,
Ogre::Vector3(mMaxExtentsInner.x + mForce,
mMaxExtentsInner.y, mMaxExtentsInner.z ) );
}
else {
getInputForce = false;
mForce = GameConstants::MAX_FORCE;
}
DebugDrawer::getSingleton().drawQuad( mBoxInner.getAllCorners(),
Ogre::ColourValue(1.0f, 0, 0) );
DebugDrawer::getSingleton().build();



return getInputForce;

}


void Shuffleboard::resetArrowOrientation() {
Ogre::Vector3 direction = mArrow->getOrientation() * Vector3::UNIT_X;
Ogre::Quaternion quat = direction.getRotationTo( Ogre::Vector3(0, 0, -1) );
mArrow->rotate(quat);
}


void Shuffleboard::rotateArrow(OIS::MouseEvent const & e) {
Ogre::Real xMovement = e.state.X.rel * 0.1f;
// Arrow initially faces in positive X direction.3 | P a g e
Ogre::Vector3 directionFacing = mArrow->getOrientation() * Vector3::UNIT_X;
Ogre::Vector3 straightAhead(0, 0, -1);
Ogre::Degree angle = directionFacing.angleBetween( straightAhead );


if ( angle < Ogre::Degree(GameConstants::MAX_ANGLE) ) {
mArrow->yaw( Ogre::Degree(xMovement * -1) );
}
else if(directionFacing.x < 0 && xMovement > 0 || directionFacing.x > 0 && xMovement < 0){
mArrow->yaw( Ogre::Degree(xMovement * -1 ) );
}
}


//-------------------------------------------------------------------------------------
Shuffleboard * Shuffleboard::instance(SceneManager * sceneMgr ) {
	if (mInstance == 0)  {  
		mInstance = new Shuffleboard( sceneMgr );
	}
    return mInstance;
}