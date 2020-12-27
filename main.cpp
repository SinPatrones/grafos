#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

int main(){
    string primerSemestre[] = {"ED2", "CC1", "C1V", "ITP2", "CI", "RN"};

    Grafo<string> g1("coloracion", true);

    for (auto & curso: primerSemestre){
        g1.insertarVertice(curso);
    }

    g1.crearGrafoCompleto();

    g1.crearArchivoDot();

    return 1;
}
