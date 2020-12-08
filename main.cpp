#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main(){

    Grafo<int> g1("coloracion", true);

    g1.insertarArista(5, 4);
    g1.insertarArista(5, 6);
    g1.insertarArista(5, 2);
    g1.insertarArista(6, 7);
    g1.insertarArista(6, 1);
    g1.insertarArista(6, 4);
    g1.insertarArista(4, 3);
    g1.insertarArista(3, 1);
    g1.insertarArista(3, 2);
    g1.insertarArista(7, 1);
    g1.insertarArista(2, 1);

    g1.colorearGrafoMMI();

    g1.crearArchivoDot();
    return 1;
}
