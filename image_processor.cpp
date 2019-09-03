#include "image_processor.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;



image_processor::image_processor()
{

}

vector<image_processor::pixel> image_processor::readFile(ifstream &file) {
    vector<pixel> image;
    if (file.is_open()) {
        //reading header
        file.read(&idLength, sizeof(idLength));
        file.read(&colorMapType, sizeof(colorMapType));
        file.read(&dataTypeCode, sizeof(dataTypeCode));
        file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
        file.read((char*)&colorMapLength, sizeof(colorMapLength));
        file.read(&colorMapDepth, sizeof(colorMapDepth));
        file.read((char*)&xOrigin, sizeof(xOrigin));
        file.read((char*)&yOrigin, sizeof(yOrigin));
        file.read((char*)&width, sizeof(width));
        file.read((char*)&height, sizeof(height));
        file.read(&bitsPerPixel, sizeof(bitsPerPixel));
        file.read(&imageDescriptor, sizeof(imageDescriptor));

        //reading actual image data
        pixelCount = (width*height);
        char *data = new char[pixelCount*3];
        file.read(data, sizeof(data[0])*pixelCount*3);
        for (unsigned int i = 0; i < pixelCount*3; i+=3) {
            pixel pix;
            pix.blue = data[i];
            pix.green = data[i+1];
            pix.red = data[i+2];
            pix.y = .257*pix.red + 0.504*pix.green + 0.098*pix.red + 16;
            pix.cb = -0.148*pix.red - 0.291*pix.green + 0.439*pix.blue + 128;
            pix.cr = 0.439*pix.red - 0.368*pix.green - 0.071*pix.blue + 128;
            image.push_back(pix);
        }
        delete[] data;
    }
    return image;
}

void image_processor::HighlightSkin(vector<pixel> &image)
{
    pixel centerPixel = image[image.size()/2];
    for (uint i = 0; i < pixelCount; i++)
    {
        if  (image[i].cb - centerPixel.cb <= 15 && image[i].cb -centerPixel.cb >= -15 &&
             image[i].cr - centerPixel.cr <= 10 && image[i].cr - centerPixel.cr >= -10)
        {
            image[i].blue = 0;
            image[i].green = 0;
            image[i].red = 0;
        }
        else
        {
            image[i].blue = 255;
            image[i].green = 255;
            image[i].red = 255;
        }
    }
}

void image_processor::writeFile(vector<pixel> &image, ofstream &file) {
    file.write(&idLength, sizeof(idLength));
    file.write(&colorMapType, sizeof(colorMapType));
    file.write(&dataTypeCode, sizeof(dataTypeCode));
    file.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));
    file.write((char*)&colorMapLength, sizeof(colorMapLength));
    file.write(&colorMapDepth, sizeof(colorMapDepth));
    file.write((char*)&xOrigin, sizeof(xOrigin));
    file.write((char*)&yOrigin, sizeof(xOrigin));
    file.write((char*)&width, sizeof(width));
    file.write((char*)&height, sizeof(height));
    file.write(&bitsPerPixel, sizeof(bitsPerPixel));
    file.write(&imageDescriptor, sizeof(imageDescriptor));

    for (unsigned int i = 0; i < pixelCount; i++) {
        file.write((char*)&image[i].blue, 1);
        file.write((char*)&image[i].green, 1);
        file.write((char*)&image[i].red, 1);
    }
file.close();
}
