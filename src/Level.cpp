#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>
#include "bmp.h"
#include <stdint.h>

using namespace std;

struct LevelData{
    char* path;
    int size;
    int height;
    int lenght;
};

int* level;
struct LevelData data;
//TODO pixel mapping
Level::Level(char* path)
{
    data.path = path;
    loadImg();
}
struct LevelData getLevelData()
{
    return data;
}

int* getLevel()
{
    return level;
}

int Level::loadImg(){
    uint8_t* datBuff[2]; // Header buffers
    uint8_t* pixels = NULL; // Pixels
    // The file... We open it with it's constructor
    ifstream file(data.path, ios::binary);
    if(!file.is_open())
    {
        cout << "Failure to open bitmap file." << endl;
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
        cout << "File \"" << data.path << "\" isn't a bitmap file" << endl;
        return 2;
    }
    pixels = new uint8_t[bmpInfo->biSizeImage];
    level = new int[bmpInfo->biSizeImage / 3];
    // Go to where image data starts, then read in image data
    file.seekg(bmpHeader->bfOffBits);
    file.read((char*)pixels, bmpInfo->biSizeImage);
    uint8_t tmpRGB = 0; // Swap buffer
    int pixel = 0;
    for (unsigned long i = 0; i < (data.size = bmpInfo->biSizeImage - 3); i += 3)
    {
        tmpRGB = pixels[i];
        pixels[i] = pixels[i + 2];
        pixels[i + 2] = tmpRGB;
        pixel = 0;
        pixel = (pixel | pixels[i]) << 8;
        pixel = (pixel | pixels[i + 1]) << 8;
        pixel |= pixels[i + 2];
        level[i / 3] = pixel;
    }
    data.height = bmpInfo->biHeight;
    data.lenght = bmpInfo->biWidth;
    return 0;
}
