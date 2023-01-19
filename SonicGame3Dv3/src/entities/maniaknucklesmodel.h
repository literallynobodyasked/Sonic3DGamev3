#ifndef MANIAKNUCKLESMODEL_H
#define MANIAKNUCKLESMODEL_H

class TexturedModel;

#include <list>
#include "entities.h"


class ManiaKnucklesModel : public Entity
{
private:
	static std::list<TexturedModel*>* models;

	static std::list<TexturedModel*> modelDash0;
	static std::list<TexturedModel*> modelDash1;
	static std::list<TexturedModel*> modelDash2;
	static std::list<TexturedModel*> modelDash3;
	static std::list<TexturedModel*> modelDash4;
	static std::list<TexturedModel*> modelDash5;
	static std::list<TexturedModel*> modelDash6;
	static std::list<TexturedModel*> modelDash7;
	static std::list<TexturedModel*> modelDash8;
	static std::list<TexturedModel*> modelDash9;
	static std::list<TexturedModel*> modelDash10;
	static std::list<TexturedModel*> modelDash11;
	static std::list<TexturedModel*> modelJump;
	static std::list<TexturedModel*> modelJog0;
	static std::list<TexturedModel*> modelJog1;
	static std::list<TexturedModel*> modelJog2;
	static std::list<TexturedModel*> modelJog3;
	static std::list<TexturedModel*> modelJog4;
	static std::list<TexturedModel*> modelJog5;
	static std::list<TexturedModel*> modelJog6;
	static std::list<TexturedModel*> modelJog7;
	static std::list<TexturedModel*> modelJog8;
	static std::list<TexturedModel*> modelJog9;
	static std::list<TexturedModel*> modelJog10;
	static std::list<TexturedModel*> modelJog11;
	static std::list<TexturedModel*> modelJog12;
	static std::list<TexturedModel*> modelJog13;
	static std::list<TexturedModel*> modelJog14;
	static std::list<TexturedModel*> modelJog15;
	static std::list<TexturedModel*> modelJog16;
	static std::list<TexturedModel*> modelJog17;

public:
	ManiaKnucklesModel();

	void step();

	void animate(int animIndex, float time);

	void setOrientation(float x, float y, float z, float xRot, float yRot, float zRot, float spinRot);

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();
};
#endif