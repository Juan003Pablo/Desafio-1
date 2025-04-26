#include "Header.h"
#include <iostream>
using namespace std;

int FuncionXOR() {
    int wID = 0, hID = 0;
    int wIM = 0, hIM = 0;
    int wM = 0, hM = 0;

    // Cargar imagen final (ID) e imagen de distorsión (IM)
    unsigned char* imgID = loadPixels("I_D.bmp", wID, hID);
    unsigned char* imgIM = loadPixels("I_M.bmp", wIM, hIM);

    if (!imgID || !imgIM || wID != wIM || hID != hIM) {
        cout << "Error al cargar imágenes o tamaños incompatibles." << endl;
        return -1;
    }

    // Aplicar XOR entre ID e IM
    int size = wID * hID * 3;
    unsigned char* resultado = new unsigned char[size];
    xorImages(imgID, imgIM, resultado, size);

    // Cargar máscara M
    unsigned char* mask = loadPixels("M.bmp", wM, hM);
    if (!mask) {
        delete[] imgID;
        delete[] imgIM;
        delete[] resultado;
        return -1;
    }

    int n_pixels = wM * hM;
    int seed = 100; // Puedes cambiar esto o hacerlo aleatorio

    // Guardar archivo de enmascaramiento como .txt
    guardarEnmascaramientoTXT("generado.txt", seed, resultado, mask, n_pixels);

    // Liberar memoria
    delete[] imgID;
    delete[] imgIM;
    delete[] resultado;
    delete[] mask;

    return 0;
}
