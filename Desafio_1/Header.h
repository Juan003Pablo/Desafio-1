#ifndef HEADER_H
#define HEADER_H

#include <QImage>
#include <QString>
using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height);
void xorImages(unsigned char* img1, unsigned char* img2, unsigned char* result, int size);
void guardarEnmascaramientoTXT(const char* nombreArchivo, int seed, unsigned char* imagen, unsigned char* mascara, int n_pixels);


#endif // HEADER_H
