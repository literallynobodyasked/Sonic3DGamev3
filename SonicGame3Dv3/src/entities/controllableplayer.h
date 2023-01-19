#ifndef CONTROLLABLEPLAYER_H
#define CONTROLLABLEPLAYER_H

#include "entities.h"
#include "../toolbox/vector.h"

class ShieldMagnet;
class ShieldGreen;

class ControllablePlayer : public Entity
{
	//Functions that every player must be able to handle in some way
public:

	virtual void setCameraAngles(float newYaw, float newPitch);

	virtual void setCameraTargetYaw(float yaw);

	virtual void setCameraTargetPitch(float pitch);

	virtual void increaseGroundSpeed(float dx, float dz);

	virtual float getSpeed();

	virtual void goUp();

	virtual void setCanMoveTimer(int newMoveTimer);

	virtual void setGroundSpeed(float newXspd, float newZspd);

	virtual float getXVelGround();

	virtual float getZVelGround();

	virtual float getxVel();

	virtual void setxVel(float xVel);

	virtual float getyVel();

	virtual void setyVel(float yVel);

	virtual float getzVel();

	virtual void setzVel(float zVel);

	virtual void setxVelAir(float xVelAir);

	virtual float getXVelAir();

	virtual void setzVelAir(float zVelAir);

	virtual float getZVelAir();

	virtual void setHoverCount(int newCount);

	virtual int getHoverCount();

	virtual void setOnPlane(bool on);

	virtual float getHitboxHorizontal();

	virtual float getHitboxVertical();

	virtual void stopMoving();

	virtual void setInWater(float height);

	virtual void takeDamage(Vector3f* damageSource);

	virtual void rebound(Vector3f* source);

	virtual bool isVulnerable();

	virtual void die();

	virtual Vector3f getOverallVel();

	virtual float getSpindashSpeed();

	virtual void debugAdjustCamera();

	virtual void boostMe(float amount);

	virtual void setDisplacement(float x, float y, float z);

	virtual void setGravity(float newGrav);

	virtual bool isDying();

	virtual void setOnPlanePrevious(bool on);

	virtual int getSpindashTimer();

	virtual void setSpindashTimer(int newTimer);

	virtual bool isChargingSpindash();

	virtual void setIsBall(bool newisBall);

	//returns the speed player goes after releasing a spindash
	virtual float calculateSpindashSpeed(int spindashCharge);

	virtual bool isOnGround();

	//Returns the normal of the triangle that the player has collided with
	virtual Vector3f* getCurrNorm();

	//Returns the center position of where the player is being drawn.
	virtual Vector3f getCenterPosition();

	virtual ShieldMagnet* getShieldMagnet();

	virtual void setShieldMagnet(ShieldMagnet* newMagnet);

	virtual ShieldGreen* getShieldGreen();

	virtual void setShieldGreen(ShieldGreen* newGreen);

	virtual int getDiggingTimer();

	virtual void increaseCombo();

	virtual void setInvincibleTimer(int newTimer);

	virtual void setSpeedshoesTimer(int newTimer);

	virtual void setOnRocket(bool onRocket);
};
#endif