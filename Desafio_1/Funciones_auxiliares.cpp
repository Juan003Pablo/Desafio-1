#include <QImage>
#include <QString>
#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height){
    /*
 * @brief Carga una imagen BMP desde un archivo y extrae los datos de píxeles en formato RGB.
 *
 * Esta función utiliza la clase QImage de Qt para abrir una imagen en formato BMP, convertirla al
 * formato RGB888 (24 bits: 8 bits por canal), y copiar sus datos de píxeles a un arreglo dinámico
 * de tipo unsigned char. El arreglo contendrá los valores de los canales Rojo, Verde y Azul (R, G, B)
 * de cada píxel de la imagen, sin rellenos (padding).
 *
 * @param input Ruta del archivo de imagen BMP a cargar (tipo QString).
 * @param width Parámetro de salida que contendrá el ancho de la imagen cargada (en píxeles).
 * @param height Parámetro de salida que contendrá la altura de la imagen cargada (en píxeles).
 * @return Puntero a un arreglo dinámico que contiene los datos de los píxeles en formato RGB.
 *         Devuelve nullptr si la imagen no pudo cargarse.
 *
 * @note Es responsabilidad del usuario liberar la memoria asignada al arreglo devuelto usando `delete[]`.
 */

    // Cargar la imagen BMP desde el archivo especificado (usando Qt)
    QImage imagen(input);

    // Verifica si la imagen fue cargada correctamente
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen BMP." << std::endl;
        return nullptr; // Retorna un puntero nulo si la carga falló
    }

    // Convierte la imagen al formato RGB888 (3 canales de 8 bits sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    // Obtiene el ancho y el alto de la imagen cargada
    width = imagen.width();
    height = imagen.height();

    // Calcula el tamaño total de datos (3 bytes por píxel: R, G, B)
    int dataSize = width * height * 3;

    // Reserva memoria dinámica para almacenar los valores RGB de cada píxel
    unsigned char* pixelData = new unsigned char[dataSize];

    // Copia cada línea de píxeles de la imagen Qt a nuestro arreglo lineal
    for (int y = 0; y < height; ++y) {
        const uchar* srcLine = imagen.scanLine(y);              // Línea original de la imagen con posible padding
        unsigned char* dstLine = pixelData + y * width * 3;     // Línea destino en el arreglo lineal sin padding
        memcpy(dstLine, srcLine, width * 3);                    // Copia los píxeles RGB de esa línea (sin padding)
    }

    // Retorna el puntero al arreglo de datos de píxeles cargado en memoria
    return pixelData;
}

// XOR byte a byte
void xorImages(unsigned char* img1, unsigned char* img2, unsigned char* result, int size) {
    for (int i = 0; i < size; ++i) {
        result[i] = img1[i] ^ img2[i];
    }
}

// Guardar archivo .txt con resultados del enmascaramiento
void guardarEnmascaramientoTXT(const char* nombreArchivo, int seed, unsigned char* imagen, unsigned char* mascara, int n_pixels) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    archivo << seed << endl;

    for (int i = 0; i < n_pixels * 3; i += 3) {
        int sumaR = imagen[seed + i] + mascara[i];
        int sumaG = imagen[seed + i + 1] + mascara[i + 1];
        int sumaB = imagen[seed + i + 2] + mascara[i + 2];
        archivo << sumaR << " " << sumaG << " " << sumaB << endl;
    }

    archivo.close();
    cout << "Archivo de enmascaramiento generado: " << nombreArchivo << endl;
}
