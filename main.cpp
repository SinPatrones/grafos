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
    string segundoSemestre[] = {"ED2", "CC1", "C1V", "ITP2", "CI", "RN"};
    string cuartoSemestre[] = {"AED", "TC", "BD2", "ALN", "EP", "ECA"};
    string sextoSemestre[] = {"PC", "IS2", "EDA", "SO", "TI2", "MAC"};
    string octavoSemestre[] = {"IHC", "PFCI", "CPD", "SC", "FEBTI", "RH", "FC(e)", "TIS(e)"};
    string decimoSemestre[] = {"CC", "PFC2", "TI3", "IoT", "R(e)", "TEC(e)"};

    Horario h1(colores);

    cout << "SE AGREGO CANTIDAD DE SALOES" << endl;

    h1.crearCurso("ED2", "Estructuras Discretas 2");
    h1.crearCurso("CC1");
    h1.crearCurso("C1V");
    h1.crearCurso("ITP2");
    h1.crearCurso("RN");
    h1.crearCurso("CI");

    h1.crearCurso("AED");
    h1.crearCurso("TC");
    h1.crearCurso("BD2");
    h1.crearCurso("ALN");

    cout << endl << "SE CREARON LOS CURSOS" << endl;

    h1.asignarHorasAlCurso("ED2", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});
    h1.asignarHorasAlCurso("CC1", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});
    h1.asignarHorasAlCurso("C1V", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});
    h1.asignarHorasAlCurso("ITP2", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});
    h1.asignarHorasAlCurso("RN", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});
    h1.asignarHorasAlCurso("CI", {PrimeraHora, SegundaHora, TerceraHora, CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora});

    h1.asignarHorasAlCurso("AExD", {CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora, NovenaHora, DecimaHora, DecimoPrimeraHora});
    h1.asignarHorasAlCurso("TC", {CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora, NovenaHora, DecimaHora, DecimoPrimeraHora});
    h1.asignarHorasAlCurso("BD2", {CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora, NovenaHora, DecimaHora, DecimoPrimeraHora});
    h1.asignarHorasAlCurso("ALN", {CuartaHora, QuintaHora, SextaHora, SeptimaHora, OctavaHora, NovenaHora, DecimaHora, DecimoPrimeraHora});

    cout << "SE ASIGNARONS HORAS DISPONIBLES PARA LOS CURSOS" << endl;

    h1.asignarSemestreAlCurso("ED2", "PrimerSemestre");
    h1.asignarSemestreAlCurso("C1V", "PrimerSemestre");
    h1.asignarSemestreAlCurso("CC1", "PrimerSemestre");
    h1.asignarSemestreAlCurso("ITP2", "PrimerSemestre");
    h1.asignarSemestreAlCurso("RN", "PrimerSemestre");
    h1.asignarSemestreAlCurso("CI", "PrimerSemestre");

    h1.asignarSemestreAlCurso("AED", "SegundoSemestre");
    h1.asignarSemestreAlCurso("TC", "SegundoSemestre");
    h1.asignarSemestreAlCurso("BD2", "SegundoSemestre");
    h1.asignarSemestreAlCurso("ALN", "SegundoSemestre");

    cout << "SE ASIGNO SEMESTRE A LOS CURSOS" << endl;

    h1.asignarProfesorAtipoYgrupo("ED2", "TE", "a", "Carlos");
    h1.asignarProfesorAtipoYgrupo("ED2", "TE", "b", "Luis");
    h1.asignarProfesorAtipoYgrupo("ED2", "LA", "a", "Carlos");
    h1.asignarProfesorAtipoYgrupo("ED2", "LA", "b", "Luis");
    h1.asignarProfesorAtipoYgrupo("C1V", "TE", "a", "Diego");
    h1.asignarProfesorAtipoYgrupo("C1V", "TE", "b", "Diego");
    h1.asignarProfesorAtipoYgrupo("C1V", "LA", "a", "Diego");
    h1.asignarProfesorAtipoYgrupo("C1V", "LA", "b", "Diego");
    h1.asignarProfesorAtipoYgrupo("CI", "", "a", "Maria");

    h1.asignarProfesorAtipoYgrupo("CC1", "TE", "", "Pedro");

    cout << "SE ASGINARON PROFESORES A LOS GRUPOS" << endl;

    h1.asignarProfesorAlCurso("ITP2", "Luis");
    h1.asignarProfesorAlCurso("AED", "Luis");
    h1.asignarProfesorAlCurso("TC", "Luis");

    cout << "SE ASIGNO PROFESOR AL CURSO" << endl;

    cout << "#### MOSTRANDO INFO ####" << endl;
    h1.mostrarInfoHorario();

    cout << endl << endl << "--------- SE CARGARAN LOS DATOS ------------" << endl << endl;
    h1.cargarDatos(2);

    return 1;
}
