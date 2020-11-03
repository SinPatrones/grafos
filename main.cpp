#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    Grafo<int> g1(true, false, false, true);

    g1.crearGrafoCompleto(4);

    g1.mostrarNodos();
    cout << "--------------------------------\n";
    g1.mostrarListaDeAdyacencia();
    cout << "-------------------------------\n";
    g1.crearArchivoDot();


    return 1;
}
