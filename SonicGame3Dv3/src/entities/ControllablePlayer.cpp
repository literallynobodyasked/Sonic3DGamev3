#include <glad/glad.h>

#include "entities.h"
#include "controllableplayer.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "../toolbox/maths.h"
#include "../engineTester/main.h"
#include "../collision/collisionmodel.h"
#include "shieldmagnet.h"
#include "shieldgreen.h"

#include <list>
#include <iostream>
#include <string>

void          ControllablePlayer::setCameraAngles(float,float)        {}
void          ControllablePlayer::setCameraTargetYaw(float)           {}
void          ControllablePlayer::setCameraTargetPitch(float)         {}
void          ControllablePlayer::increaseGroundSpeed(float,float)    {}
float         ControllablePlayer::getSpeed()                          {return 0;}
void          ControllablePlayer::goUp()                              {}
void          ControllablePlayer::setCanMoveTimer(int)                {}
void          ControllablePlayer::setGroundSpeed(float,float)         {}
float         ControllablePlayer::getXVelGround()                     {return 0;}
float         ControllablePlayer::getZVelGround()                     {return 0;}
float         ControllablePlayer::getxVel()                           {return 0;}
void          ControllablePlayer::setxVel(float)                      {}
float         ControllablePlayer::getyVel()                           {return 0;}
void          ControllablePlayer::setyVel(float)                      {}
float         ControllablePlayer::getzVel()                           {return 0;}
void          ControllablePlayer::setzVel(float)                      {}
void          ControllablePlayer::setxVelAir(float)                   {}
float         ControllablePlayer::getXVelAir()                        {return 0;}
void          ControllablePlayer::setzVelAir(float)                   {}
float         ControllablePlayer::getZVelAir()                        {return 0;}
void          ControllablePlayer::setHoverCount(int)                  {}
int           ControllablePlayer::getHoverCount()                     {return 0;}
void          ControllablePlayer::setOnPlane(bool)                    {}
float         ControllablePlayer::getHitboxHorizontal()               {return 0;}
float         ControllablePlayer::getHitboxVertical()                 {return 0;}
void          ControllablePlayer::stopMoving()                        {}
void          ControllablePlayer::setInWater(float)                   {}
void          ControllablePlayer::takeDamage(Vector3f*)               {}
void          ControllablePlayer::rebound(Vector3f*)                  {}
bool          ControllablePlayer::isVulnerable()                      {return false;}
void          ControllablePlayer::die()                               {}
Vector3f      ControllablePlayer::getOverallVel()                     {return Vector3f(0,0,0);}
float         ControllablePlayer::getSpindashSpeed()                  {return 0;}
void          ControllablePlayer::debugAdjustCamera()                 {}
void          ControllablePlayer::boostMe(float)                      {}
void          ControllablePlayer::setDisplacement(float,float,float)  {}
void          ControllablePlayer::setGravity(float)                   {}
bool          ControllablePlayer::isDying()                           {return false;}
void          ControllablePlayer::setOnPlanePrevious(bool)            {}
int           ControllablePlayer::getSpindashTimer()                  {return 0;}
void          ControllablePlayer::setSpindashTimer(int)               {}
bool          ControllablePlayer::isChargingSpindash()                {return false;}
void          ControllablePlayer::setIsBall(bool)                     {}
float         ControllablePlayer::calculateSpindashSpeed(int)         {return 0;}
bool          ControllablePlayer::isOnGround()                        {return false;}
Vector3f*     ControllablePlayer::getCurrNorm()                       {return nullptr;}
Vector3f      ControllablePlayer::getCenterPosition()                 {return Vector3f(0,0,0);}
ShieldMagnet* ControllablePlayer::getShieldMagnet()                   {return nullptr;}
void          ControllablePlayer::setShieldMagnet(ShieldMagnet*)      {}
ShieldGreen*  ControllablePlayer::getShieldGreen()                    {return nullptr;}
void          ControllablePlayer::setShieldGreen(ShieldGreen*)        {}
int           ControllablePlayer::getDiggingTimer()                   {return 0;}
void          ControllablePlayer::increaseCombo()                     {}
void          ControllablePlayer::setInvincibleTimer(int)             {}
void          ControllablePlayer::setSpeedshoesTimer(int)             {}
void		  ControllablePlayer::setOnRocket(bool)					  {}