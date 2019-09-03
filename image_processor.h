#pragma once
#include <vector>
#include <iostream>
using namespace std;

class image_processor
{
public:
    struct pixel {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        int y;
        int cb;
        int cr;
    };
    unsigned int pixelCount;
    image_processor();
    vector<pixel> readFile(ifstream &file);
    void writeFile(vector<pixel> &image, ofstream &file);
    void HighlightSkin(vector<pixel> &image);

private:
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
