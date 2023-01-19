#include "shadowmapmasterrenderer.h"
#include "shadowshader.h"
#include "shadowbox.h"
#include "shadowframebuffer.h"
#include "shadowmapentityrenderer.h"
#include "../toolbox/matrix.h"
#include "../toolbox/vector.h"
#include "../entities/camera.h"
#include "../entities/light.h"
#include "../entities/entities.h"
#include "../engineTester/main.h"

ShadowMapMasterRenderer::ShadowMapMasterRenderer()
{
	projectionMatrix       = new Matrix4f; INCR_NEW
	lightViewMatrix        = new Matrix4f; INCR_NEW
	projectionViewMatrix   = new Matrix4f; INCR_NEW
	toShadowMapSpaceMatrix = new Matrix4f; INCR_NEW
	createOffset();

	shader = new ShadowShader("res/Shaders/shadows/shadowVertexShader.txt", "res/Shaders/shadows/shadowFragmentShader.txt"); INCR_NEW
	shadowBox = new ShadowBox(lightViewMatrix, Global::gameCamera); INCR_NEW
	shadowFbo = new ShadowFrameBuffer(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE); INCR_NEW
	entityRenderer = new ShadowMapEntityRenderer(shader, projectionViewMatrix); INCR_NEW
}

void ShadowMapMasterRenderer::render(std::unordered_map<TexturedModel*, std::list<Entity*>>* entities, Light* sun)
{
	shadowBox->update();
	Vector3f* sunPosition = sun->getPosition();
	Vector3f lightDirection(-sunPosition->x, -sunPosition->y, -sunPosition->z);
	prepare(&lightDirection, shadowBox);
	entityRenderer->render(entities);
	finish();
}

Matrix4f* ShadowMapMasterRenderer::getToShadowMapSpaceMatrix()
{
	offset->multiply(projectionViewMatrix, toShadowMapSpaceMatrix);

	return toShadowMapSpaceMatrix;
}

void ShadowMapMasterRenderer::cleanUp()
{
	shader->cleanUp();
	shadowFbo->cleanUp();
}

GLuint ShadowMapMasterRenderer::getShadowMap()
{
	return shadowFbo->getShadowMap();
}

Matrix4f* ShadowMapMasterRenderer::getLightSpaceTransform()
{
	return lightViewMatrix;
}

void ShadowMapMasterRenderer::prepare(Vector3f* lightDirection, ShadowBox* box)
{
	updateOrthoProjectionMatrix(box->getWidth(), box->getHeight(), box->getLength());
	Vector3f cent = box->getCenter();
	updateLightViewMatrix(lightDirection, &cent);
	projectionMatrix->multiply(lightViewMatrix, projectionViewMatrix);
	shadowFbo->bindFrameBuffer();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader->start();
}

void ShadowMapMasterRenderer::finish()
{
	shader->stop();
	shadowFbo->unbindFrameBuffer();
}

void ShadowMapMasterRenderer::updateLightViewMatrix(Vector3f* direction, Vector3f* center)
{
	Vector3f dir(direction);
	Vector3f cent(center);

	dir.normalize();
	cent.neg();
	lightViewMatrix->setIdentity();

	Vector2f r(dir.x, dir.z);

	float pitch = acosf(r.length());

	Vector3f axis(1, 0, 0);
	lightViewMatrix->rotate(pitch, &axis);

	float yaw = toDegrees((atanf(dir.x / dir.z)));
	yaw = dir.z > 0 ? yaw - 180 : yaw;

	axis.set(0, 1, 0);
	lightViewMatrix->rotate(-toRadians(yaw), &axis);

	lightViewMatrix->translate(&cent);
}

void ShadowMapMasterRenderer::updateOrthoProjectionMatrix(float width, float height, float length)
{
	projectionMatrix->setIdentity();
	projectionMatrix->m00 = 2.0f / width;
	projectionMatrix->m11 = 2.0f / height;
	projectionMatrix->m22 = -2.0f / length;
	projectionMatrix->m33 = 1;
}

void ShadowMapMasterRenderer::createOffset()
{
	offset = new Matrix4f; INCR_NEW
	Vector3f trans(0.5f, 0.5f, 0.5f);
	offset->translate(&trans);
	offset->scale(&trans);
}
