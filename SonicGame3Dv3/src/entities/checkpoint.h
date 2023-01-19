#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class TexturedModel;
class Body;

#include <list>
#include "entities.h"
#include <AL/al.h>


class Checkpoint : public Entity
{
private:
	static std::list<TexturedModel*> modelsBase;
	static std::list<TexturedModel*> modelsBall;

	Body* ball1;
	Body* ball2;
	static float colHorizontal;
	static float colVertical;

	bool isHit;

	static ALuint savedBGMIntro;
	static ALuint savedBGMLoop;

public:
	Checkpoint();
	Checkpoint(float x, float y, float z, float rotY);

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif