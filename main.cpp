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
    PrimeraHora,
    SegundaHora,
    TerceraHora,
    CuartaHora,
    QuintaHora,
    SextaHora,
    SeptimaHora,
    OctavaHora,
    NovenaHora,
    DecimaHora
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
    DecimaHora
};

int main(){

    string segundoSemestre[] = {"ED2", "CC1", "C1V", "ITP2", "CI", "RN"};
    string cuartoSemestre[] = {"AED", "TC", "BD2", "ALN", "EP", "ECA"};
    string sextoSemestre[] = {"PC", "IS2", "EDA", "SO", "TI2", "MAC"};
    string octavoSemestre[] = {"IHC", "PFCI", "CPD", "SC", "FEBTI", "RH", "FC(e)", "TIS(e)"};
    string decimoSemestre[] = {"CC", "PFC2", "TI3", "IoT", "R(e)", "TEC(e)"};

    Horario h1(colores);

    h1.crearCurso("ED2");
    h1.crearCurso("CC1");
    h1.crearCurso("C1V");
    h1.crearCurso("ITP2");
    h1.crearCurso("RN");
    h1.crearCurso("CI");

    h1.crearCurso("AED");
    h1.crearCurso("TC");
    h1.crearCurso("BD2");
    h1.crearCurso("ALN");

    //h1.crearSoloGrupoAlCurso("C1V", "a");
    //h1.crearSoloGrupoAlCurso("C1V", "b");

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

    h1.asignarProfesorAlCurso("ITP2", "Luis");
    h1.asignarProfesorAlCurso("AED", "Luis");
    h1.asignarProfesorAlCurso("TC", "Luis");


    h1.mostrarInfoHorario();
    h1.cargarDatos();


/*
    Grafo<string> g1("coloracion", true);

    g1.insertarArista("EDII-a-T", "CCII");
    g1.insertarArista("EDII-a-T", "C1V-a-T");
    g1.insertarArista("EDII-a-T", "C1V-a-L");
    g1.insertarArista("EDII-a-T", "CI");
    g1.insertarArista("EDII-a-T", "RN");
    g1.insertarArista("EDII-a-T", "EDII-a-L");
    //----------------
    g1.insertarArista("EDII-a-L", "CCII");
    g1.insertarArista("EDII-a-L", "C1V-a-T");
    g1.insertarArista("EDII-a-L", "C1V-a-L");
    g1.insertarArista("EDII-a-L", "CI");
    g1.insertarArista("EDII-a-L", "RN");
    g1.insertarArista("EDII-a-L", "EDII-a-T");
    //----------------
    g1.insertarArista("CCII","C1V-a-T");
    g1.insertarArista("CCII","C1V-a-L");
    g1.insertarArista("CCII","CI");
    g1.insertarArista("CCII","RN");
    g1.insertarArista("CCII","C1V-b-L");
    g1.insertarArista("CCII","C1V-b-T");
    g1.insertarArista("CCII","EDII-a-L");
    g1.insertarArista("CCII","EDII-a-T");
    //-----------------
    g1.insertarArista("CI","C1V-a-L");
    g1.insertarArista("CI","C1V-a-T");
    g1.insertarArista("CI","CCII");
    g1.insertarArista("CI","EDII-a-T");
    g1.insertarArista("CI","EDII-a-L");
    g1.insertarArista("CI","C1V-b-T");
    g1.insertarArista("CI","C1V-b-L");
    g1.insertarArista("CI","RN");
    //------------------
    g1.insertarArista("RN","CI");
    g1.insertarArista("RN","C1V-a-L");
    g1.insertarArista("RN","C1V-a-T");
    g1.insertarArista("RN","CCII");
    g1.insertarArista("RN","EDII-a-T");
    g1.insertarArista("RN","EDII-a-L");
    g1.insertarArista("RN","C1V-b-T");
    g1.insertarArista("RN","C1V-b-L");
    //-------------------
    g1.insertarArista("C1V-a-T","C1V-a-L");
    g1.insertarArista("EDII-a-T","EDII-a-L");
    g1.insertarArista("C1V-b-T","C1V-b-L");

    g1.colorearHorario(colores);

    g1.crearArchivoDot();
*/
    return 1;
}
