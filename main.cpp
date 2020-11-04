#include <QCoreApplication>
#include "grafo.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main(){
    Grafo<string> g1(true, false);

    insertarCaminoEn(g1, "armando", "juan", "luis", "diego", "sofia", "luis", "carlos", "diego", "armando");

    /*bool hayCiclo = g1.existeCiclo("armado", "juan");
    if (hayCiclo)
        cout << "HAY CICLO ENTRE armado y juan" << endl;
    else
        cout << "NOO HAY CICLO ENTRE 23 y 30" << endl;
*/
    cout << "\n--------------------------------\n";
    cout << g1;
    cout << "-------------------------------\n";
    g1.crearArchivoDot();

    return 1;
}
