#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderEngine.h"
#include "../entities/entities.h"
#include "../shaders/shaders.h"
#include "../toolbox/matrix.h"
#include "../toolbox/vector.h"
#include "../toolbox/maths.h"
#include "../models/models.h"

#include <iostream>
#include <unordered_map>
#include <list>

EntityRenderer::EntityRenderer(ShaderProgram* shader, Matrix4f* projectionMatrix)
{
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
	this->shader = shader;
}

void EntityRenderer::render(std::unordered_map<TexturedModel*, std::list<Entity*>*>* entitiesMap)
{
	//for (auto entry : (*entitiesMap))
	{
		//prepareTexturedModel(entry.first);
		//std::list<Entity*>* entityList = entry.second;

		//for (auto entity : (*entityList))
		{
			//prepareInstance(entity);
			//final render of an entity
			//glDrawElements(GL_TRIANGLES, (entry.first)->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		//unbindTexturedModel();
	}
}

void EntityRenderer::prepareTexturedModel(TexturedModel* model)
{
	RawModel* rawModel = (*model).getRawModel();
	glBindVertexArray((*rawModel).getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = model->getTexture();
	if (texture->getHasTransparency() != 0)
	{
		Master_disableCulling();
	}
	else
	{
		Master_enableCulling();
	}
	shader->loadFakeLighting(texture->getUsesFakeLighting());
	shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, (*(*model).getTexture()).getID());
}

void EntityRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity* entity)
{
	Matrix4f transformationMatrix;
	createTransformationMatrix(&transformationMatrix, entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
	shader->loadTransformationMatrix(&transformationMatrix);
}

void EntityRenderer::renderOLD(Entity* entity, ShaderProgram* shader) //defunct
{
	TexturedModel* texturedModel = entity->getModel();
	RawModel* model = (*texturedModel).getRawModel();
	//glBindVertexArray((*model).getVaoID());
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	//ModelTexture* texture = texturedModel->getTexture();
	//shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
	prepareTexturedModel(texturedModel);

	//Matrix4f transformationMatrix;
	//createTransformationMatrix(&transformationMatrix, entity->getPosition(), entity->getRotX(), entity->getRotY(), entity->getRotZ(), entity->getScale());
	//shader->loadTransformationMatrix(&transformationMatrix);
	prepareInstance(entity);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, (*(*texturedModel).getTexture()).getID());
	glDrawElements(GL_TRIANGLES, (*model).getVertexCount(), GL_UNSIGNED_INT, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	//glBindVertexArray(0);
	unbindTexturedModel();
}
