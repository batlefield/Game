#pragma once

typedef int LONG;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct tagBITMAPFILEHEADER 
{
   WORD    bfType;        // must be 'BM' 
   DWORD   bfSize;        // size of the whole .bmp file
   WORD    bfReserved1;   // must be 0
   WORD    bfReserved2;   // must be 0
   DWORD   bfOffBits;     
} BITMAPFILEHEADER, *PBITMAPFILEHEADER; 

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
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
