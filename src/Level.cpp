#include <fstream>
#include <iostream>
#include "SDL/SDL_opengl.h"
#include "Level.h"
#include "SDL/SDL.h"//Uint8
#include "bmp.h"

using namespace std;

Level::Level()
{

	
}

void Level::loadLevel(char* path)
{
	int Width = 0;
	int Height = 0;
   	int BitCount = 0;
     
    	ifstream bmpFile;
     
    	BITMAPFILEHEADER bmpFileHead;
    	BITMAPINFOHEADER bmpInfoHead;
     
    	bmpFile.open(path, ios::binary | ios::in);
     
	if( !bmpFile.is_open() )
        	cout << "Error loading image file." << endl;
    	else
		cout << "Image file loaded." << endl;
     
    	bmpFile.read( (char*)&bmpFileHead.bfType, 14 );
     
    	if(bmpFileHead.bfType!=0x4d42) // 0x4d42 is BM
    		cout << "Wrong file format." << endl;
     
    	bmpFile.read( (char*)&bmpInfoHead, sizeof(BITMAPINFOHEADER) );
 
    	Width = bmpInfoHead.biWidth;
    	Height = bmpInfoHead.biHeight;
    	BitCount = bmpInfoHead.biBitCount;
     
    	cout << "Width: " << Width << endl;
    	cout << "Height: " << Height << endl;
    	cout << "Bits per pixel: " << BitCount << endl;
}
