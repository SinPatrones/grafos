#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    Grafo<int> g1(true);

    g1.insertarArista(23,11);
    g1.insertarArista(23,110);
    g1.insertarArista(23,19);

    g1.mostrarListaDeAdyacencia();
    g1.crearArchivoDot();

    return 1;
}
