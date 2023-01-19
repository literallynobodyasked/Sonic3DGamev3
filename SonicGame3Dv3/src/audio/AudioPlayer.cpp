#include <AL/al.h>
#include <vector>
#include <cstring>
#include <fstream>

#include "audioplayer.h"
#include "audiomaster.h"
#include "source.h"
#include "../engineTester/main.h"
#include "../toolbox/vector.h"
#include "../toolbox/split.h"



float AudioPlayer::soundLevelSE = 0.5f;
float AudioPlayer::soundLevelBGM = 0.4f;
std::vector<Source*> AudioPlayer::sources;
std::vector<ALuint> AudioPlayer::buffersSE;
std::vector<ALuint> AudioPlayer::buffersBGM;
ALuint AudioPlayer::bgmIntro;
ALuint AudioPlayer::bgmLoop;


void AudioPlayer::loadSoundEffects()
{
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/BigDestroy.ogg"));           //0
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Dashpad.ogg"));              //1
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Goal.ogg"));                 //2
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/ItemCapsule.ogg"));          //3
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Ring.ogg"));                 //4
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Splash.ogg"));               //5
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Spring.ogg"));               //6
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/UnlockSomething.ogg"));      //7
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Bounce.ogg"));                //8
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Death.ogg"));                 //9
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/GetHit.ogg"));                //10
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/HomingAttack.ogg"));          //11
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Jump.ogg"));                  //12
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Skid.ogg"));                  //13
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/SpindashCharge.ogg"));        //14
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/SpindashRelease.ogg"));       //15
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/StompInit.ogg"));             //16
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/StompLand.ogg"));             //17
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/CantStick.ogg"));             //18
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/DockBreak.ogg"));            //19
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Seagull.ogg"));              //20
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/SpeedRamp.ogg"));            //21
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/SpeedHighway/CranePlatform.ogg"));   //22
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/SpeedHighway/ElevatorPlatform.ogg"));//23
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/ActClear.ogg"));             //24
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/ExitStage.ogg"));            //25
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/CapsuleClick.ogg"));         //26
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Fly.ogg"));                   //27
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/FlyTired.ogg"));              //28
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Climb.ogg"));                 //29
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Dig.ogg"));                   //30
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/DrillDive.ogg"));             //31
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Glide.ogg"));                 //32
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Player/Punch.ogg"));                 //33
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/RadarPing.ogg"));            //34
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/1Up.ogg"));                  //35
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/MenuBleep.ogg"));            //36
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/MenuWoosh.ogg"));            //37
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/MenuAccept.ogg"));           //38
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Snowhead/BabyGoron_Cry1.ogg"));      //39
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Snowhead/BabyGoron_Cry2.ogg"));      //40
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Snowhead/BabyGoron_Cry3.ogg"));      //41
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Snowhead/BabyGoron_Doze.ogg"));      //42
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Dig.ogg"));                  //43
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/RankShow.ogg"));             //44
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/Checkpoint.ogg"));           //45
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/BreakDamage.ogg"));             //46
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/ChaosSpear.ogg"));              //47
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/Damage.ogg"));                  //48
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/Electric.ogg"));                //49
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/MetallicExplode.ogg"));         //50
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/RunFastLoop.ogg"));             //51
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/ChargeShot.ogg"));              //52
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/Boss/LaserLoop.ogg"));               //53
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/RocketAppear.ogg"));         //54
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/RocketTakeOffStart.ogg"));   //55
	AudioPlayer::buffersSE.push_back(AudioMaster::loadOGG("res/Audio/General/RocketTakeOffLoop.ogg"));    //56
}

void AudioPlayer::loadBGM(char* fileName)
{
	AudioPlayer::buffersBGM.push_back(AudioMaster::loadOGG(fileName));
}

void AudioPlayer::deleteSources()
{
	for (Source* src : AudioPlayer::sources)
	{
		src->deleteMe();
		delete src;
		INCR_DEL
	}
	AudioPlayer::sources.clear();
	AudioPlayer::sources.shrink_to_fit();
}

void AudioPlayer::deleteBuffersSE()
{
	for (ALuint buff : AudioPlayer::buffersSE)
	{
		alDeleteBuffers(1, &buff);
	}
	AudioPlayer::buffersSE.clear();
	AudioPlayer::buffersSE.shrink_to_fit();
}

void AudioPlayer::deleteBuffersBGM()
{
	Source* src = AudioPlayer::sources[14];
	src->stop();

	for (ALuint buff : AudioPlayer::buffersBGM)
	{
		alDeleteBuffers(1, &buff);
	}
	AudioPlayer::buffersBGM.clear();
	AudioPlayer::buffersBGM.shrink_to_fit();
	AudioPlayer::bgmIntro = AL_NONE;
	AudioPlayer::bgmLoop  = AL_NONE;
}

void AudioPlayer::createSources()
{
	//First 14 sources are for sound effects
	sources.push_back(new Source(1, 100, 600)); INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	sources.push_back(new Source(1, 100, 600));	INCR_NEW
	//Last source is dedicated to background music
	sources.push_back(new Source(0, 0, 0));     INCR_NEW
}

//with position
Source* AudioPlayer::play(int buffer, Vector3f* pos)
{
	return AudioPlayer::play(buffer, pos, 1.0f, false, 0, 0, 0);
}

//with position and pitch
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch)
{
	return AudioPlayer::play(buffer, pos, pitch, false, 0, 0, 0);
}

//with position and pitch and loop
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch, bool loop)
{
	return AudioPlayer::play(buffer, pos, pitch, loop, 0, 0, 0);
}

//with everything
Source* AudioPlayer::play(int buffer, Vector3f* pos, float pitch, bool loop, float xVel, float yVel, float zVel)
{
	for (int i = 0; i < 14; i++)
	{
		Source* src = AudioPlayer::sources[i];
		if (!src->isPlaying())
		{
			src->setVolume(soundLevelSE);
			src->setLooping(loop);
			src->setPosition(pos->x, pos->y, pos->z);
			src->setPitch(pitch);
			src->setVelocity(xVel, yVel, zVel);
			src->play(AudioPlayer::buffersSE[buffer]);
			return src;
		}
	}

	//no sources to play music
	return nullptr;
}

Source* AudioPlayer::playBGM(int bufferLoop)
{
	if (bufferLoop >= (int)AudioPlayer::buffersBGM.size() || bufferLoop < 0)
	{
		std::fprintf(stdout, "Error: Index out of bounds on BGM buffers\n");
		return nullptr;
	}

	return AudioPlayer::playBGM(AudioPlayer::buffersBGM[bufferLoop]);
}

Source* AudioPlayer::playBGM(ALuint bufferLoop)
{
	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setLooping(false);

	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE);

	src->setLooping(true);
	src->setVolume(AudioPlayer::soundLevelBGM);

	AudioPlayer::bgmIntro = AL_NONE;
	AudioPlayer::bgmLoop = bufferLoop;

	src->play(AudioPlayer::bgmLoop);

	return src;
}

Source* AudioPlayer::playBGMWithIntro(int bufferIntro, int bufferLoop)
{
	if (bufferIntro >= (int)AudioPlayer::buffersBGM.size() ||
		bufferLoop  >= (int)AudioPlayer::buffersBGM.size() ||
		bufferIntro < 0 ||
		bufferLoop  < 0)
	{
		std::fprintf(stdout, "Error: Index out of bounds on BGM buffers\n");
		return nullptr;
	}

	return AudioPlayer::playBGMWithIntro(AudioPlayer::buffersBGM[bufferIntro], AudioPlayer::buffersBGM[bufferLoop]);
}

Source* AudioPlayer::playBGMWithIntro(ALuint bufferIntro, ALuint bufferLoop)
{
	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setVolume(AudioPlayer::soundLevelBGM);
	src->setLooping(false);

	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE); //Get rid of queued buffers 

	AudioPlayer::bgmIntro = bufferIntro;
	AudioPlayer::bgmLoop  = bufferLoop;

	alSourceQueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmIntro);
	alSourceQueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmLoop);

	alSourcePlay(src->getSourceID());

	return src;
}

//Gets rid of the intro buffer, so that just the loop buffer loops
void AudioPlayer::refreshBGM()
{
	Source* src = AudioPlayer::sources[14];

	if (AudioPlayer::bgmIntro != AL_NONE)
	{
		ALint currentBufferIndex;
		alGetSourcei(src->getSourceID(), AL_BUFFERS_PROCESSED, &currentBufferIndex);
		if (currentBufferIndex == 1)
		{
			alSourceUnqueueBuffers(src->getSourceID(), 1, &AudioPlayer::bgmIntro);
			AudioPlayer::bgmIntro = AL_NONE;
			src->setLooping(true);
		}
	}
}

void AudioPlayer::stopBGM()
{
	Source* src = AudioPlayer::sources[14];
	src->stop();
	src->setLooping(false);

	alSourcei(src->getSourceID(), AL_BUFFER, AL_NONE); Global::checkErrorAL("stopBGM 248"); //Get rid of queued buffers 

	AudioPlayer::bgmIntro = AL_NONE;
	AudioPlayer::bgmLoop  = AL_NONE;
}

Source* AudioPlayer::getSource(int i)
{
	return AudioPlayer::sources[i];
}

ALuint AudioPlayer::getSEBuffer(int i)
{
	return AudioPlayer::buffersSE[i];
}

void AudioPlayer::setBGMVolume(float percent)
{
	Source* src = AudioPlayer::sources[14];
	src->setVolume(percent*soundLevelBGM);
}

void AudioPlayer::loadSettings()
{
	std::ifstream file("Settings/AudioSettings.ini");
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file 'Settings/AudioSettings.ini'\n");
		file.close();
	}
	else
	{
		std::string line;

		while (!file.eof())
		{
			getline(file, line);

			char lineBuf[512]; //Buffer to copy line into
			memset(lineBuf, 0, 512);
			memcpy(lineBuf, line.c_str(), line.size());

			int splitLength = 0;
			char** lineSplit = split(lineBuf, ' ', &splitLength);

			if (splitLength == 2)
			{
				if (strcmp(lineSplit[0], "SFX_Volume") == 0)
				{
					AudioPlayer::soundLevelSE = std::stof(lineSplit[1], nullptr);
					AudioPlayer::soundLevelSE = fmaxf(0.0f, fminf(AudioPlayer::soundLevelSE, 1.0f));
				}
				else if (strcmp(lineSplit[0], "Music_Volume") == 0)
				{
					AudioPlayer::soundLevelBGM = std::stof(lineSplit[1], nullptr);
					AudioPlayer::soundLevelBGM = fmaxf(0.0f, fminf(AudioPlayer::soundLevelBGM, 1.0f));
				}
			}

			free(lineSplit);
		}
		file.close();
	}
}

void AudioPlayer::stopAllSFX()
{
	for (int i = 0; i < 14; i++)
	{
		if (AudioPlayer::sources[i]->isPlaying())
		{
			AudioPlayer::sources[i]->stop();
		}
	}
}