#include <fstream>
#include <iostream>
#include "SDL/SDL_opengl.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdint.h>
#include "Level.h"
#include <map>
#include <cstring>
#include "bmp.h"

std::map<int, uint8_t> colorToTileMap;
std::map<uint8_t, std::string> tileToImageMap;
std::map<std::string, GLuint> imageToGlIDMap;
std::map<uint8_t, GLuint> tileToGlIDMap; //mainly helper, could live without it

Level::Level()
{
	//TODO: do something about relative path!
	addTile(0x00FF00, 0, "resources/basicTile.png");
}

void Level::addTile(int levelColor, uint8_t tile, std::string path)
{
	colorToTileMap[levelColor] = tile;
	tileToImageMap[tile] = path;
	imageToGlIDMap[path] = loadImage(path);
	tileToGlIDMap[tile] = imageToGlIDMap[path];
}

GLuint Level::loadImage(std::string path)
{
	if(imageToGlIDMap.count(path) == 0)
	{
		return imageToGlIDMap[path];
	}
	GLuint textureID = 0;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(surface == NULL)
	{
		std::cout << "Failed to load image " << path << std::endl;
		std::cout << IMG_GetError() << std::endl;
		return -1;
	}
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4){
		mode = GL_RGBA;
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	std::cout << path << " loaded succesfully!" << std::endl;
	return textureID;
}

int Level::loadLevel(std::string path){
    uint8_t* datBuff[2]; // Header buffers
    uint8_t* pixels = NULL; // Pixels
    // The file... We open it with it's constructor
    std::ifstream file(path.c_str(), std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Failure to open bitmap file." << std::endl;
        return 1;
    }
    datBuff[0] = new uint8_t[sizeof(BITMAPFILEHEADER)];
    datBuff[1] = new uint8_t[sizeof(BITMAPINFOHEADER)];
    file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
    file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));
    BITMAPFILEHEADER* bmpHeader = (BITMAPFILEHEADER*) datBuff[0];
    BITMAPINFOHEADER* bmpInfo = (BITMAPINFOHEADER*) datBuff[1];
    if(bmpHeader->bfType != 0x4D42)
    {
        std::cout << "File \"" << path << "\" isn't a bitmap file" << std::endl;
        return 2;
    }
    pixels = new uint8_t[bmpInfo->biSizeImage];
    // Go to where image data starts, then read in image data
    file.seekg(bmpHeader->bfOffBits);
    file.read((char*)pixels, bmpInfo->biSizeImage);
    uint8_t tmpRGB = 0; // Swap buffer
    for (unsigned long i = 0; i < (bmpInfo->biSizeImage - 3); i += 3)
    {
        tmpRGB = pixels[i];
        pixels[i] = pixels[i + 2];
        pixels[i + 2] = tmpRGB;
    }
    return 0;
}
