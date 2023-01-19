#include "metafile.h"
#include "../toolbox/split.h"
#include "textmeshcreator.h"

#include <iostream>
#include <string>
#include <cstring>

#include "../engineTester/main.h"


extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

MetaFile::MetaFile(std::string filename)
{
	this->aspectRatio = (double)SCR_WIDTH / (double)SCR_HEIGHT;
	openFile(filename);
	loadPaddingData();
	loadLineSizes();
	int imageWidth = getValueOfVariable("scaleW");
	loadCharacterData(imageWidth);
	close();
}

double MetaFile::getSpaceWidth()
{
	return spaceWidth;
}

Character MetaFile::getCharacter(int ascii)
{
	return metaData[ascii];
}

bool MetaFile::processNextLine()
{
	std::string line;

	if (reader->eof())
	{
		return false;
	}
	values.clear();

	getline((*reader), line);

	char lineBuf[1024];
	memset(lineBuf, 0, 1024);
	memcpy(lineBuf, line.c_str(), line.size());

	int splitLength1 = 0;
	char** lineSplit1 = split(lineBuf, SPLITTER, &splitLength1);

	for (int i = 0; i < splitLength1; i++)
	{
		char* part = lineSplit1[i];

		int splitLength2 = 0;
		char** lineSplit2 = split(part, '=', &splitLength2);

		if (splitLength2 == 2)
		{
			std::string vp0 = lineSplit2[0];
			std::string vp1 = lineSplit2[1];
			//std::fprintf(stdout, "'%s' '%s'\n", vp0.c_str(), vp1.c_str());
			values[vp0] = vp1;
		}
		free(lineSplit2);
	}
	free(lineSplit1);

	return true;
}

int MetaFile::getValueOfVariable(std::string variable)
{
	return std::stoi(values[variable]);
}

std::vector<int> MetaFile::getValuesOfVariable(std::string variable)
{
	std::string line = values[variable];

	char lineBuf[1024];
	memset(lineBuf, 0, 1024);
	memcpy(lineBuf, line.c_str(), line.size());

	int splitLength = 0;
	char** numbers = split(lineBuf, NUMBER_SEPARATOR, &splitLength);

	std::vector<int> actualValues;

	for (int i = 0; i < splitLength; i++)
	{
		std::string val = numbers[i];
		actualValues.push_back(std::stoi(val));
	}
	free(numbers);

	return actualValues;
}

void MetaFile::close()
{
	reader->close();
	delete reader;
	INCR_DEL
	reader = nullptr;
}

void MetaFile::openFile(std::string filename)
{
	reader = new std::ifstream(filename);
	INCR_NEW
	if (!reader->is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", (filename).c_str());
		reader->close();
		delete reader;
		INCR_DEL
		reader = nullptr;
	}
}

void MetaFile::loadPaddingData()
{
	processNextLine();
	this->padding = getValuesOfVariable("padding");
	this->paddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
	this->paddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
}

void MetaFile::loadLineSizes()
{
	processNextLine();
	int lineHeightPixels = getValueOfVariable("lineHeight") - paddingHeight;
	verticalPerPixelSize = TextMeshCreator::LINE_HEIGHT / (double)lineHeightPixels;
	horizontalPerPixelSize = verticalPerPixelSize / aspectRatio;
}

void MetaFile::loadCharacterData(int imageWidth)
{
	processNextLine();
	processNextLine();
	while (processNextLine())
	{
		Character* c = loadCharacter(imageWidth);
		if (c != nullptr)
		{
			metaData[c->getId()] = (*c); //Put a copy of the character into the hash map
			delete c;
			INCR_DEL
		}
	}
}

Character* MetaFile::loadCharacter(int imageSize)
{
	int id = getValueOfVariable("id");
	if (id == TextMeshCreator::SPACE_ASCII)
	{
		this->spaceWidth = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
		return nullptr;
	}
	double xTex = ((double)getValueOfVariable("x") + (padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
	double yTex = ((double)getValueOfVariable("y") + (padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
	int width = getValueOfVariable("width") - (paddingWidth - (2 * DESIRED_PADDING));
	int height = getValueOfVariable("height") - ((paddingHeight)-(2 * DESIRED_PADDING));
	double quadWidth = width * horizontalPerPixelSize;
	double quadHeight = height * verticalPerPixelSize;
	double xTexSize = (double)width / imageSize;
	double yTexSize = (double)height / imageSize;
	double xOff = (getValueOfVariable("xoffset") + padding[PAD_LEFT] - DESIRED_PADDING) * horizontalPerPixelSize;
	double yOff = (getValueOfVariable("yoffset") + (padding[PAD_TOP] - DESIRED_PADDING)) * verticalPerPixelSize;
	double xAdvance = (getValueOfVariable("xadvance") - paddingWidth) * horizontalPerPixelSize;
	//std::fprintf(stdout, "%d %f %f %f %f %f %f %f %f %f\n", id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	INCR_NEW
	return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
}