#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    Grafo<char> g1("g1", true);

    g1.insertarArista('G', 'A');
    g1.insertarArista('G', 'B');
    g1.insertarArista('G', 'C');
    g1.insertarArista('A', 'B');
    g1.insertarArista('A', 'C');
    g1.insertarArista('C', 'D');
    g1.insertarArista('C', 'E');
    g1.insertarArista('C', 'F');
    g1.insertarArista('D', 'F');

    Grafo<char> g2;
    Grafo<char> g3;

    cout << "GENERANDO ARBOL DE EXPANSION MINIMA" << endl;
    g2 = g1.generarArbolMinimoPorProfundida('G');
    g3 = g1.generarArbolMinimoPorAnchura('G');

    cout << "\n--------------------------------\n";
    cout << g1;
    cout << "-------------------------------\n";
    cout << g2;
    cout << "-------------------------------\n";
    cout << g3;
    cout << "-------------------------------\n";
    g1.crearArchivoDot();
    g2.crearArchivoDot();
    g3.crearArchivoDot();

    return 1;
}
