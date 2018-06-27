#include "particleresources.h"
#include "particletexture.h"
#include "../renderEngine/renderEngine.h"
#include "../engineTester/main.h"

ParticleTexture* ParticleResources::textureDust = nullptr;
ParticleTexture* ParticleResources::textureSnowDrop = nullptr;
ParticleTexture* ParticleResources::textureDustCloud = nullptr;
ParticleTexture* ParticleResources::textureSnowball = nullptr;
ParticleTexture* ParticleResources::textureStar = nullptr;
ParticleTexture* ParticleResources::textureSparkleYellow = nullptr;
ParticleTexture* ParticleResources::textureSparkleGreen = nullptr;
ParticleTexture* ParticleResources::textureSparkleRed = nullptr;
ParticleTexture* ParticleResources::textureSparkleBlue = nullptr;
ParticleTexture* ParticleResources::textureSparkleLightBlue = nullptr;
ParticleTexture* ParticleResources::textureSparkleWhite = nullptr;
ParticleTexture* ParticleResources::textureWaterDrop = nullptr;
ParticleTexture* ParticleResources::textureLightBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlueTrail = nullptr;
ParticleTexture* ParticleResources::textureBlackTrail = nullptr;
ParticleTexture* ParticleResources::textureGrayTrail = nullptr;
ParticleTexture* ParticleResources::texturePinkTrail = nullptr;
ParticleTexture* ParticleResources::textureDarkGreenTrail = nullptr;
ParticleTexture* ParticleResources::textureOrangeTrail = nullptr;
ParticleTexture* ParticleResources::textureRedTrail = nullptr;
ParticleTexture* ParticleResources::textureSplash = nullptr;
ParticleTexture* ParticleResources::textureBubble = nullptr;
ParticleTexture* ParticleResources::textureExplosion1 = nullptr;
ParticleTexture* ParticleResources::textureExplosion2 = nullptr;
ParticleTexture* ParticleResources::textureBlackFade = nullptr;
ParticleTexture* ParticleResources::textureBlackFadeOut = nullptr;
ParticleTexture* ParticleResources::textureTear1 = nullptr;
ParticleTexture* ParticleResources::textureTear2 = nullptr;
ParticleTexture* ParticleResources::textureWhiteFadeOutAndIn = nullptr;
ParticleTexture* ParticleResources::textureBlackFadeOutAndIn = nullptr;
ParticleTexture* ParticleResources::textureInWater = nullptr;
ParticleTexture* ParticleResources::textureBlueLine = nullptr;

void ParticleResources::loadParticles()
{
	textureSnowDrop          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SnowDropAtlas.png"), 2, 1.0f, 0);
	textureDustCloud         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/DustCloud.png"), 1, 0.2f, 0);
	textureSnowball          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Snowball.png"), 1, 0.75f, 0);
	textureStar              = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Star.png"), 1, 1.0f, 0);
	textureSparkleYellow     = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleYellow.png"), 1, 1.0f, 1);
	textureSparkleGreen      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleGreen.png"), 1, 1.0f, 1);
	textureSparkleRed        = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleRed.png"), 1, 1.0f, 1);
	textureSparkleBlue       = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleBlue.png"), 1, 1.0f, 1);
	textureSparkleLightBlue  = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleLightBlue.png"), 1, 1.0f, 1);
	textureSparkleWhite      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SparkleWhite.png"), 1, 1.0f, 1);
	textureWaterDrop         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/WaterDrop.png"), 1, 1, 0);
	textureLightBlueTrail    = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailLightBlue.png"), 1, 0.1f, 1);
	textureBlueTrail         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailBlue.png"), 1, 0.1f, 1);
	textureBlackTrail        = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailBlack.png"), 1, 0.1f, 1);
	textureGrayTrail         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailGray.png"), 1, 0.1f, 1);
	texturePinkTrail         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailPink.png"), 1, 0.1f, 1);
	textureDarkGreenTrail    = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailDarkGreen.png"), 1, 0.1f, 1);
	textureOrangeTrail       = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailOrange.png"), 1, 0.3f, 1);
	textureRedTrail          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/SpTrailRed.png"), 1, 0.3f, 1);
	textureDust              = new ParticleTexture(Loader_loadTexture("res/Models/Particle/DustAtlas.png"), 4, 0.2f, 0);
	textureSplash            = new ParticleTexture(Loader_loadTextureNoInterpolation("res/Models/Particle/SplashAtlas.png"), 4, 0.6f, 0);
	textureBubble            = new ParticleTexture(Loader_loadTextureNoInterpolation("res/Models/Particle/BubbleInverseAtlas.png"), 4, 0.6f, 0);
	textureExplosion1        = new ParticleTexture(Loader_loadTextureNoInterpolation("res/Models/Particle/Explosion1Atlas.png"), 4, 0.8f, 0);
	textureExplosion2        = new ParticleTexture(Loader_loadTextureNoInterpolation("res/Models/Particle/Explosion2Atlas.png"), 4, 0.8f, 0);
	textureBlackFade         = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BlackFadeAtlas.png"), 2, 1.0f, 0);
	textureBlackFadeOut      = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BlackFadeOutAtlas.png"), 2, 1.0f, 0);
	textureTear1             = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Tear1.png"), 1, 1.0f, 0);
	textureTear2             = new ParticleTexture(Loader_loadTexture("res/Models/Particle/Tear2.png"), 1, 1.0f, 0);
	textureWhiteFadeOutAndIn = new ParticleTexture(Loader_loadTexture("res/Models/Particle/WhiteFadeOutAndInAtlas.png"), 2, 1.0f, 0);
	textureBlackFadeOutAndIn = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BlackFadeOutAndInAtlas.png"), 2, 1.0f, 0);
	textureInWater           = new ParticleTexture(Loader_loadTexture("res/Models/Particle/InWater.png"), 1, 0.1f, 1);
	textureBlueLine          = new ParticleTexture(Loader_loadTexture("res/Models/Particle/BlueLine.png"), 1, 1.0f, 1);
	Global::countNew += 32;
}