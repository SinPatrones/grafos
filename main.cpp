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

    g1.insertarArista("Armando", "Juan", 6);
    g1.insertarArista("Armando", "Stephany", 5);
    g1.insertarArista("Diego", "Juan", 3);
    g1.insertarArista("Juan", "Andres", 4);
    g1.insertarArista("Juan", "Stephany", 2);
    g1.insertarArista("Pepe", "Andres", 4);
    g1.insertarArista("Diego", "Pepe", 1);
    g1.insertarArista("Juan", "Lucia", 6);
    g1.insertarArista("Stephany", "Pepe", 6);


    g1.ordenadoDeVertices();
    g1.crearArchivoDot();

    return 1;
}
