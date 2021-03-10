#include "grafo.h"
#include "horario.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "horario.h"

using namespace std;

enum Horas{
    SinHora,
    PrimeraHora,    // amarillo
    SegundaHora,    // verde
    TerceraHora,    // rojo
    CuartaHora,     // morado
    QuintaHora,     // azul
    SextaHora,      // turquoise3
    SeptimaHora,    // firebrick
    OctavaHora,     // goldenrod3
    NovenaHora,     // aquamarine2
    DecimaHora,      // darkolivegreen3
    DecimoPrimeraHora
};

vector<int> colores = {
    PrimeraHora,
    SegundaHora,
    TerceraHora,
    CuartaHora,
    QuintaHora,
    SextaHora,
    SeptimaHora,
    OctavaHora,
    NovenaHora,
    DecimaHora,
    DecimoPrimeraHora
};

int main(){
    Grafo<string> g1("nuevo", true, false, false, true);

    g1.insertarVertice("Armando");
    g1.insertarVertice("Juan");
    g1.insertarVertice("Stephany");
    g1.insertarVertice("Diego");
    g1.insertarVertice("Andres");

    g1.insertarArista("Armando", "Juan", 6);
    g1.insertarArista("Armando", "Stephany", 5);
    g1.insertarArista("Diego", "Juan", 3);
    g1.insertarArista("Juan", "Andres", 2);

    cout << "PESO Armando: " << g1.encontrarVertice("Armando")->obtenerPeso() << endl;
    cout << "PESO Diego: " << g1.encontrarVertice("Diego")->obtenerPeso() << endl;

    g1.crearArchivoDot();

    return 1;
}
