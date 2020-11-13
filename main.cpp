#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main(){

    Grafo<int> g1("migrafo", true,false,false,true);

    g1.insertarArista(59,100,9);
    g1.insertarArista(20,100,12);
    g1.insertarArista(59,10,10);
    g1.insertarArista(59,20,50);
    g1.insertarArista(59,50,5);
    g1.insertarArista(30,50,30);
    g1.insertarArista(80,50,19);
    g1.insertarArista(80,20,40);
    g1.insertarArista(10,80,10);
    g1.insertarArista(10,30,5);

    auto g2 = g1.generarKruskal();

    g2.crearArchivoDot();

    g1.crearArchivoDot();

    return 1;
}
