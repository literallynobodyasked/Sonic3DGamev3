#include "pausescreen.h"
#include "../engineTester/main.h"

#include <cmath>
#include <algorithm>

#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../renderEngine/renderEngine.h"
#include "../toolbox/input.h"
#include "../entities/playersonic.h"
#include "../toolbox/levelloader.h"
#include "../fontMeshCreator/guitext.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"
#include "../particles/particletexture.h"
#include "../entities/camera.h"
#include "../particles/particlemaster.h"
#include "../guis/guitextureresources.h"
#include "../guis/guimanager.h"

int PauseScreen::menuSelection = 0;
int PauseScreen::menuSelectionMAX = 3;
int PauseScreen::menuDisplayID = 0;

int PauseScreen::moveYPrevious = 0;
bool PauseScreen::selectInputPrevious = false;
bool PauseScreen::backInputPrevious = false;

FontType* PauseScreen::font = nullptr;

GUIText* PauseScreen::textCursor  = nullptr;
GUIText* PauseScreen::textResume  = nullptr;
GUIText* PauseScreen::textCamera  = nullptr;
GUIText* PauseScreen::textRestart = nullptr;
GUIText* PauseScreen::textQuit    = nullptr;

bool PauseScreen::isPaused = false;
bool PauseScreen::shouldPause = false;
bool PauseScreen::pausedSounds[14];

extern InputStruct Inputs;

extern unsigned int SCR_HEIGHT;
extern unsigned int SCR_WIDTH;

void PauseScreen::init()
{

	font = new FontType(Loader::loadTexture("res/Fonts/vipnagorgialla.png"), "res/Fonts/vipnagorgialla.fnt"); INCR_NEW
	textCursor = new GUIText(">", 2.5f, font, 0.5f - ((float) SCR_HEIGHT / (float) SCR_WIDTH * 0.05f), 0.25f, 1.0f, false, false, false); INCR_NEW
	isPaused = false;
}

void PauseScreen::step()
{
	if (shouldPause == true)
	{
		shouldPause = false;
		if (Global::gameState == STATE_PAUSED)
		{
			unpause(true);
		}
		else if (Global::gameState == STATE_RUNNING)
		{
			if (Global::finishStageTimer == -1)
			{
				pause();
			}
		}
	}

	if (Inputs.INPUT_START && !Inputs.INPUT_PREVIOUS_START)
	{
		shouldPause = true;
	}

	if (Global::gameState == STATE_PAUSED)
	{
		int moveY = Inputs.MENU_Y;

		if (moveYPrevious != moveY)
		{
			menuSelection += moveY;
			menuSelection = std::max(0, std::min(menuSelectionMAX, menuSelection));
		}

		if (Inputs.INPUT_JUMP && !Inputs.INPUT_PREVIOUS_JUMP)
		{
			switch (menuDisplayID)
			{
			case ROOT:
				switch (menuSelection)
				{
				case 0:
					//unpause();
					shouldPause = true;
					break;

				case 1:
				{
					if (Global::gameLives > 0)
					{
						Global::shouldLoadLevel = true;
						Vector3f vel(0,0,0);
						new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &vel, 0, 60, 0.0f,  10.0f, 0, 1.0f, 0, true);
						unpause(false);
						Global::gameState = STATE_CUTSCENE;
					}
					break;
				}

				case 2:
				{
					//switch cam, reload text
					if (textCamera != nullptr)
					{
						textCamera->deleteMe(); delete textCamera; INCR_DEL textCamera = nullptr;
						if (Global::isAutoCam)
						{
							textCamera    = new GUIText("Free Cam",  2.5f, font, 0.5f, 0.55f, 1.0f, false, false, true); INCR_NEW
							Global::isAutoCam = false;
						}
						else
						{
							textCamera    = new GUIText("Auto Cam",  2.5f, font, 0.5f, 0.55f, 1.0f, false, false, true); INCR_NEW
							Global::isAutoCam = true;
						}
					}
					break;
				}

				case 3:
				{
					Vector3f vel(0,0,0);
					new Particle(ParticleResources::textureBlackFade, Global::gameCamera->getFadePosition1(), &vel, 0, 60, 0.0f,  10.0f, 0, 1.0f, 0, true);
					unpause(false);
					LevelLoader::loadTitle();
					break;
				}

				default:
					break;
				}
				break;

			default:
				break;
			}
		}

		if (Inputs.INPUT_ACTION && !Inputs.INPUT_PREVIOUS_ACTION)
		{
			shouldPause = true;
			//unpause();
		}

		switch (menuDisplayID)
		{
		case ROOT:
			switch (menuSelection)
			{
				case 0: textCursor->getPosition()->y = 0.35f; break;
				case 1: textCursor->getPosition()->y = 0.45f; break;
				case 2: textCursor->getPosition()->y = 0.55f; break;
				case 3: textCursor->getPosition()->y = 0.65f; break;
				default: break;
			}
			break;

		default:
			break;
		}

		moveYPrevious = moveY;
	}
}

void PauseScreen::unpause(bool shouldResumeSFX)
{
	if (!isPaused)
	{
		return;
	}

	Global::gameState = STATE_RUNNING;

	if (textCursor != nullptr)
	{
		textCursor->setVisibility(false);
	}
	if (textResume != nullptr)
	{
		textResume->deleteMe(); delete textResume; INCR_DEL textResume = nullptr;
	}
	if (textRestart != nullptr)
	{
		textRestart->deleteMe(); delete textRestart; INCR_DEL textRestart = nullptr;
	}
	if (textCamera != nullptr)
	{
		textCamera->deleteMe(); delete textCamera; INCR_DEL textCamera = nullptr;
	}
	if (textQuit != nullptr)
	{
		textQuit->deleteMe(); delete textQuit; INCR_DEL textQuit = nullptr;
	}

	//Resume all sound effects that were paused
	if (shouldResumeSFX)
	{
		for (int i = 0; i < 14; i++)
		{
			if (PauseScreen::pausedSounds[i])
			{
				AudioPlayer::getSource(i)->continuePlaying();
			}
		}
	}
	else
	{
		AudioPlayer::stopAllSFX();
	}

	isPaused = false;
}

void PauseScreen::pause()
{
	if (isPaused)
	{
		return;
	}

	if (Global::gamePlayer != nullptr && Global::gamePlayer->isDying() == true)
	{
		return;
	}

	const float size = 2.5f;

	Global::gameState = STATE_PAUSED;
	menuSelection = 0;
	menuDisplayID = 0;
	menuSelectionMAX = 3;
	textCursor->setVisibility(true);
	if (textResume == nullptr)
	{
		textResume = new GUIText("Resume",    size, font, 0.5f, 0.35f, 1.0f, false, false, true); INCR_NEW
	}
	if (textRestart == nullptr)
	{
		textRestart = new GUIText("Restart",   size, font, 0.5f, 0.45f, 1.0f, false, false, true); INCR_NEW
	}
	if (textCamera == nullptr)
	{
		if (Global::isAutoCam)
		{
			textCamera = new GUIText("Auto Cam",  size, font, 0.5f, 0.55f, 1.0f, false, false, true); INCR_NEW
		}
		else
		{
			textCamera = new GUIText("Free Cam",  size, font, 0.5f, 0.55f, 1.0f, false, false, true); INCR_NEW
		}
	}
	if (textQuit == nullptr)
	{
		textQuit = new GUIText("Quit",      size, font, 0.5f, 0.65f, 1.0f, false, false, true); INCR_NEW
	}

	//Pause all sound effects
	for (int i = 0; i < 14; i++)
	{
		if (AudioPlayer::getSource(i)->isPlaying())
		{
			PauseScreen::pausedSounds[i] = true;
			AudioPlayer::getSource(i)->pause();
		}
		else
		{
			PauseScreen::pausedSounds[i] = false;
		}
	}

	isPaused = true;
}
