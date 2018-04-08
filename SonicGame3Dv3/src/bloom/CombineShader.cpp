#include "combineshader.h"
#include "../renderEngine/renderEngine.h"

#include <glad/glad.h>

CombineShader::CombineShader(char* vFile, char* fFile)
{
	vertexShaderID = Loader_loadShader(vFile, GL_VERTEX_SHADER);
	fragmentShaderID = Loader_loadShader(fFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	getAllUniformLocations();
}

void CombineShader::start()
{
	glUseProgram(programID);
}

void CombineShader::stop()
{
	glUseProgram(0);
}

void CombineShader::cleanUp()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void CombineShader::connectTextureUnits()
{
	loadInt(location_colourTexture, 0);
	loadInt(location_highlightTexture, 1);
}

void CombineShader::bindAttributes()
{
	bindAttribute(0, "position");
}

void CombineShader::bindAttribute(int attribute, char* variableName)
{
	glBindAttribLocation(programID, attribute, variableName);
}

void CombineShader::getAllUniformLocations()
{
	location_colourTexture = getUniformLocation("colourTexture");
	location_highlightTexture = getUniformLocation("highlightTexture");
}

int CombineShader::getUniformLocation(char* uniformName)
{
	return glGetUniformLocation(programID, uniformName);
}

void CombineShader::loadInt(int location, int value)
{
	glUniform1i(location, value);
}
