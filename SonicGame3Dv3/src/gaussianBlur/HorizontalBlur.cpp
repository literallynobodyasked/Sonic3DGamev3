#include <glad/glad.h>

#include "horizontalblur.h"
#include "horizontalblurshader.h"
#include "../postProcessing/imagerenderer.h"
#include "../engineTester/main.h"

HorizontalBlur::HorizontalBlur(int targetFboWidth, int targetFboHeight)
{
	shader = new HorizontalBlurShader("res/Shaders/gaussianBlur/horizontalBlurVertex.txt", "res/Shaders/gaussianBlur/blurFragment.txt"); Global::countNew++;
	shader->start();
	shader->loadTargetWidth((float)targetFboWidth);
	shader->stop();
	renderer = new ImageRenderer(targetFboWidth, targetFboHeight); Global::countNew++;
}

void HorizontalBlur::render(GLuint texture)
{
	shader->start();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	renderer->renderQuad();
	shader->stop();
}

int HorizontalBlur::getOutputTexture()
{
	return renderer->getOutputTexture();
}

void HorizontalBlur::cleanUp()
{
	renderer->cleanUp();
	shader->cleanUp();
	delete shader; Global::countDelete++;
	delete renderer; Global::countDelete++;
}
