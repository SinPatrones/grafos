#include <QCoreApplication>
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

    Curso c1("ED2");
    c1.crearTipoCurso("LA");
    c1.crearTipoCurso("TE");

    c1.crearGrupoTipoCurso("TE", "a");
    c1.crearGrupoTipoCurso("TE", "b");
    c1.crearTipoGrupoCurso("c", "TE");
    c1.crearGrupoTipoCurso("LA", "a");
    c1.crearGrupoTipoCurso("PR", "a");

    c1.asignarProfesor(34);

    c1.mostrarValores();
/*
    Horario h1;
    h1.crearSemestre("SegundoSemestre");
    h1.crearSemestre("CuartoSemestre");
    h1.crearSemestre("SextoSemestre");
    h1.crearSemestre("OctavoSemestre");
    h1.crearSemestre("DecimoSemestre");

    h1.crearProfesor("Luis");
    h1.crearProfesor("Pepe");
    h1.crearProfesor("Jacinto");
    h1.crearProfesor("Floripondio");
    h1.crearProfesor("Gregorio");

    for(string & curso: segundoSemestre){
        h1.crearCurso(curso, "SegundoSemestre");
    }
    for(string & curso: cuartoSemestre){
        h1.crearCurso(curso, "CuartoSemestre");
    }
    for(string & curso: sextoSemestre){
        h1.crearCurso(curso, "SextoSemestre");
    }
    for(string & curso: octavoSemestre){
        h1.crearCurso(curso, "OctavoSemestre");
    }
    for(string & curso: decimoSemestre){
        h1.crearCurso(curso, "DecimoSemestre");
    }

    cout << endl;
    cout << h1.extraerGrupoCurso("ED2:a") << endl;
    cout << h1.extraerGrupoCurso("ED2-TE") << endl;
    cout << h1.extraerTipoCurso("ED2:c-LA") << endl;
    cout << h1.extraerTipoCurso("ED2:c") << endl;
    cout << h1.extraerTipoCurso("ED2-LA") << endl;
    cout << h1.extrarNombreCurso("ED2:b") << endl;
    cout << endl << endl;

    h1.crearGrupoEnCurso("ED2");
    h1.crearGrupoEnCurso("ED2");
    h1.crearGrupoEnCurso("ITP2");
    h1.crearGrupoEnCurso("ITP2");
    h1.crearGrupoEnCurso("RN");
    h1.crearGrupoEnCurso("RN");
    h1.crearGrupoEnCurso("RN");


    h1.mostrarCursos();
*/
/*

    Grafo<string> g1("coloracion", true);

    for (auto & curso: primerSemestre){
        for (auto & curso2: primerSemestre){
            if (curso != curso2){
                    g1.insertarArista(curso, curso2);
            }
        }
    }

    for (auto & curso: cuartoSemestre){
        for (auto & curso2: cuartoSemestre){
            if (curso != curso2){
                g1.insertarArista(curso, curso2);
            }
        }
    }


    for (auto & curso: sextoSemestre){
        for (auto & curso2: sextoSemestre){
            if (curso != curso2){
                g1.insertarArista(curso, curso2);
            }
        }
    }

    for (auto & curso: octavoSemestre){
        for (auto & curso2: octavoSemestre){
            if (curso != curso2){
                g1.insertarArista(curso, curso2);
            }
        }
    }

    for (auto & curso: decimoSemestre){
        for (auto & curso2: decimoSemestre){
            if (curso != curso2){
                g1.insertarArista(curso, curso2);
            }
        }
    }

    // string primerSemestre[] = {"ED2", "CC1", "C1V", "ITP2", "CI", "RN"};
    // string cuartoSemestre[] = {"AED", "TC", "BD2", "ALN", "EP", "ECA"};
    // string sextoSemestre[] = {"PC", "IS2", "EDA", "SO", "TI2", "MAC"};
    // string octavoSemestre[] = {"IHC", "PFCI", "CPD", "SC", "FEBTI", "RH", "FC(e)", "TIS(e)"};
    // string decimoSemestre[] = {"CC", "PFC2", "TI3", "IoT", "R(e)", "TEC(e)"};

    g1.insertarArista("ED2","CC1");
    g1.insertarArista("CC1","CPD");
    g1.insertarArista("R(e)","SC");
    g1.insertarArista("ED2","TC");
    g1.insertarArista("PC","RH");
    g1.insertarArista("PFC2","IHC");
    g1.insertarArista("MAC","ECA");

    g1.mostrarListaDeAdyacencia();

    g1.colorearHorario(colores);

    g1.crearArchivoDot();
*/

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
