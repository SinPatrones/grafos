#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main(){

    Grafo<char> g1("migrafo", true,false,false,true);

    g1.insertarArista('e','a',3);
    g1.insertarArista('e','c',6);
    g1.insertarArista('e','f',2);
    g1.insertarArista('a','b',4);
    g1.insertarArista('a','c',15);
    g1.insertarArista('c','d',10);
    g1.insertarArista('c','f',3);
    g1.insertarArista('f','d',6);
    g1.insertarArista('b','d',5);

    g1.crearArchivoDot();

    Grafo<char> g2;
    Grafo<char> g3;
    g2 = g1.generarPrim('e');
    g3 = g1.generarKruskal();

    g2.crearArchivoDot();
    g3.crearArchivoDot();

    return 1;
}
