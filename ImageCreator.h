#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Pixel.h"
#include "AsciiCharacters.h"
using namespace std;
namespace image
{
    const int imageWidth = 4096;
    const int imageHeight = 2160;
    static Pixel imageData[imageWidth][imageHeight];

    class ImageCreator
    {
    public:
        struct BmpHeader {
        public:
            uint32_t sizeOfBitmapFile = 54 + (imageWidth * imageHeight *3);
            uint32_t reservedBytes = 0;
            uint32_t pixelDataOffset = 54;
        };

        struct BmpInfoHeader {
        public:
            uint32_t sizeOfThisHeader = 40;
            int32_t width = imageWidth; // in pixels
            int32_t height = imageHeight; // in pixels
            uint16_t numberOfColorPlanes = 1; // must be 1
            uint16_t colorDepth = 24;
            uint32_t compressionMethod = 0;
            uint32_t rawBitmapDataSize = 0; // generally ignored
            int32_t horizontalResolution = 3780; // in pixel per meter
            int32_t verticalResolution = 3780; // in pixel per meter
            uint32_t colorTableEntries = 0;
            uint32_t importantColors = 0;
        };

        //ititialize imageData with default pixels
        static void fillImage(uint8_t red, uint8_t green, uint8_t blue) {
            for (int i = 0; i < BmpInfoHeader().width; i++) {
                for (int ii = 0; ii < BmpInfoHeader().height; ii++) {
                    addPixel(ii, i, red, green, blue);
                }
            }
        }
        static void fillImage(Pixel pixel) {
            for (int i = 0; i < BmpInfoHeader().width; i++) {
                for (int ii = 0; ii < BmpInfoHeader().height; ii++) {
                    addPixel(ii, i, pixel);
                }
            }
        }
        //adds pixel to point on image
        static void addPixel(int x, int y, Pixel pixel) {
            imageData[y][x] = pixel;
        }
        static void addPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
            imageData[y][x] = Pixel(red,green,blue);
        }

        //overlays a pixel with set opacity: [0,100]
        static void addPixel(int x, int y, Pixel pixel, uint8_t opacity) {
            int blue = ((imageData[y][x].blue * (1 - (opacity / 100.0))) + pixel.blue);
            int green = ((imageData[y][x].green * (1 - (opacity / 100.0))) + pixel.green);
            int red = ((imageData[y][x].red * (1 - (opacity / 100.0))) + pixel.red);
            //cout << "(rgb) | (" << red << "," << green << "," << blue << ")\n";

            if (blue > 255) {
                blue = 255;
            }
            if (green > 255) {
                green = 255;
            }
            if (red > 255) {
                red = 255;
            }

            imageData[y][x].blue = blue;
            imageData[y][x].green = green;
            imageData[y][x].red = red;
        }

        //draws a image using ascii art
        static void drawImage(int x, int y,int width, int height,string inputString, Pixel pixel,int hScale,int vScale) {
            string scaledString = "";
            width *= hScale;
            height *= vScale;
            x -= width/2;
            y -= height/2;
            for (int i = 0; i < height/vScale; i++) { //every line
                for (int ii = 0; ii < vScale; ii++) { //every time it should repeat that line
                    for (int iii = 0; iii < width/hScale; iii++) { //every character in that line
                        for (int iv = 0; iv < hScale; iv++) { //every time it should repeat that character
                            scaledString += inputString[iii + (i * height/vScale)];
                        }
                    }
                }
            }
            for (int y1 = height; y1 > 0; y1--) {
                for (int x1 = 0; x1 < width; x1++) {
                    if (scaledString[((height-y1)*width)+x1] == '#') {
                        addPixel(y1+y, x1+x, pixel);
                    }
                }
            }
        }

        //draws a line between 2 points, size changes thickness of line
        static void drawLine(int x1, double y1, int x2, double y2, int size, Pixel pixel) {
            double slopePerPixel = (y2 - y1) / (x2 - x1);
            for (int x = x1; x < x2; x++) {
                double y = (x - x1) * slopePerPixel;
                drawCircle((int)x,(int)(y+y1), size, pixel);
                double nextY = (x - x1 + 1) * slopePerPixel;
                if (slopePerPixel > 0) { //increasing values
                    if (nextY > y + 1) {
                        for (int i = 1; i + y < nextY; i++) {
                            drawCircle((int)x, (int)(y + y1 + i), size, pixel);
                        }
                    }
                }
                else { //decreasing values
                    if (nextY < y - 1) {
                        for (int i = -1; i + y > nextY; i--) {
                            drawCircle((int)x+1, (int)(y + y1 + i), size, pixel);
                        }
                    }
                }
            }
        }

        //draws a triangle between 2 points, size changes thickness of line, axisY is baseline to draw to
        static void drawTriangle(int x1, double y1, int x2, double y2, int baseLine, int size, Pixel pixel,uint8_t opacity) {
            double slopePerPixel = (y2 - y1) / (x2 - x1);
            for (int x = x1; x < x2; x++) {
                double y = (x - x1) * slopePerPixel;
                drawCircle((int)x, (int)(y + y1), size, pixel);
                for (int ii = baseLine; ii <= (int)(y + y1); ii++) { //shades to baseline
                    addPixel((int)ii, (int)x, pixel, opacity);
                }
                double nextY = (x - x1 + 1) * slopePerPixel;
                if (slopePerPixel > 0) { //increasing values
                    if (nextY > y + 1) {
                        for (int i = 1; i + y < nextY; i++) {
                            drawCircle((int)x, (int)(y + y1 + i), size, pixel);
                        }
                    }
                }
                else { //decreasing values
                    if (nextY < y - 1) { 
                        for (int i = -1; i + y > nextY; i--) {
                            drawCircle((int)x + 1, (int)(y + y1 + i), size, pixel);
                        }
                    }
                }
            }
        }
            
        //draws circle based on size
        static void drawCircle(int x, int y, int size, Pixel pixel) {
            string circle = "";
            if (size == 0) {
                circle = "#";
            }
            else if (size == 1) {
                circle  = "_#_";
                circle += "###";
                circle += "_#_";
            }
            else if (size == 2) {
                circle  = "_###_";
                circle += "#####";
                circle += "#####";
                circle += "#####";
                circle += "_###_";
            }
            else if (size == 3) {
                circle  = "__###__";
                circle += "_#####_";
                circle += "#######";
                circle += "#######";
                circle += "#######";
                circle += "_#####_";
                circle += "__###__";
            }
            else {
                circle = "#";
                size = 0;
            }
            //y -= (size*2) +1;
            drawImage(x, y, (2 * size) + 1, (2 * size) + 1, circle, pixel, 1, 1);
        }

        //draws input text
        static void addText(int x, int y, string text,int size,int style) {
            int i = 0;
            for (int ii = 0; ii < text.length(); ii++) {
                if (text[ii] < 91 && text[ii] > 64) { //90 is 'Z' , 122 is 'z'
                    text[ii] += 32;  //converts uppercase to lowercase
                }
            }
            Pixel fontColour = Pixel();
            fontColour.red = 0;
            fontColour.green = 0;
            fontColour.blue = 0;
            if (style == 1) { //prints first character onwards
                for (char character : text) {
                    bool isValidChar;
                    string characterData = ascii::Char(character,&isValidChar);
                    
                    if (!isValidChar) {
                        Pixel errorColour = Pixel();
                        errorColour.red = 255;
                        errorColour.green = 0;
                        errorColour.blue = 0;
                        drawImage(x, y, 5, 5, characterData, errorColour, size * 1, size * 2);
                    }
                    else {
                        drawImage(x, y, 5, 5, characterData, fontColour, size * 1, size * 2);
                    }
                    x += 7 * size;
                    i++;
                }
            } else if (style == 2) { //prints backwards
                for (int ii = text.length()-1; ii >= 0; ii--) {
                    char character = text[ii];
                    bool isValidChar;
                    string characterData = ascii::Char(character, &isValidChar);
                    if (!isValidChar) {
                        Pixel errorColour = Pixel();
                        errorColour.red = 255;
                        errorColour.green = 0;
                        errorColour.blue = 0;
                        drawImage(x, y, 5, 5, characterData, errorColour, size * 1, size * 2);
                    }
                    else {
                        drawImage(x, y, 5, 5, characterData, fontColour, size * 1, size * 2);
                    }
                    x -= 7 * size;
                }
            }
        }

        //compiles image data into a .bmp file
        static void finishImage(string fileName) {
            //create image files
            ofstream imageFile;
            imageFile.open(fileName + ".bmp", ios::binary);
            char bitmapSignatureBytes[2] = { 'B', 'M' };
            BmpHeader bmpHeader = BmpHeader();
            BmpInfoHeader bmpInfoHeader = BmpInfoHeader();
            imageFile.write((char*)bitmapSignatureBytes, 2);
            imageFile.write((char*)&bmpHeader, 12);
            imageFile.write((char*)&bmpInfoHeader, 40);

            size_t numberOfPixels = bmpInfoHeader.width * bmpInfoHeader.height;
            //converts image data 2d array to 1d vector
            vector<Pixel> pixelArray;
            for (int i = 0; i < bmpInfoHeader.height; i++) {
                for (int ii = 0; ii < bmpInfoHeader.width; ii++) {
                    pixelArray.push_back(imageData[ii][i]);
                }
            }
            //writes 1d vector to file
            for (int i = 0; i < pixelArray.size(); i++) {
                Pixel pixel = pixelArray.at(i);
                imageFile.write((char*)&pixel, 3);
            }
            imageFile.close();
        }
    };

}
