#include <fstream>
#include <iostream>
#include "SDL/SDL_opengl.h"
#include "Level.h"
#include "SDL/SDL.h"//Uint8

#define BYTE  unsigned char
#define DWORD  unsigned int
#define LONG  int
#define UINT  unsigned int
#define WORD  unsigned short int

#pragma pack(2)
typedef struct tagBITMAPFILEHEADER 
{
   WORD    bfType;        // must be 'BM' 
   DWORD   bfSize;        // size of the whole .bmp file
   WORD    bfReserved1;   // must be 0
   WORD    bfReserved2;   // must be 0
   DWORD   bfOffBits;     
} BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER
{
   DWORD  biSize;            // size of the structure
   LONG   biWidth;           // image width
   LONG   biHeight;          // image height
   WORD   biPlanes;          // bitplanes
   WORD   biBitCount;        // resolution 
   DWORD  biCompression;     // compression
   DWORD  biSizeImage;       // size of the image
   LONG   biXPelsPerMeter;   // pixels per meter X
   LONG   biYPelsPerMeter;   // pixels per meter Y
   DWORD  biClrUsed;         // colors used
   DWORD  biClrImportant;    // important colors
} BITMAPINFOHEADER;
#pragma pack()

Level::Level()
{

	
}

void Level::loadLevel(char* path)
{
	Uint8* datBuff[2] = {NULL, NULL}; //header buffers
	Uint8* pixels = NULL; //pixels

	BITMAPFILEHEADER* bmpHeader = NULL; //header
	BITMAPINFOHEADER* bmpInfo = NULL; //info
	std::ifstream file(path, std::ios::binary);
	if(!file)
	{
		std::cout << "Failed to open bitmap: " << path << std::endl;
		return;	
	}

	datBuff[0] = new Uint8[sizeof(BITMAPFILEHEADER)];
	datBuff[1] = new Uint8[sizeof(BITMAPINFOHEADER)];

	file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
	file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));
	bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
	bmpInfo = (BITMAPINFOHEADER*)datBuff[1];
	
	if(bmpHeader->bfType != 0x4D42)
	{
		std::cout << "File isn't bitmap: " << path << std::endl;
		return;	
	}
	pixels = new Uint8[bmpInfo->biSizeImage];

	file.seekg(bmpHeader->bfOffBits);
	file.read((char*)pixels, bmpInfo->biSizeImage);

	//BGR to RGB	
	Uint8 tmpRGB = 0;
	for(unsigned long i = 0; i< bmpInfo->biSizeImage; i += 3)
	{
		tmpRGB = pixels[i];
		pixels[i] = pixels[i + 2];
		pixels[i + 2] = tmpRGB;
	}

	GLuint w = bmpInfo->biWidth;
	GLuint h = bmpInfo->biHeight;

	std::cout << "Level loaded!" << std::endl;
}
