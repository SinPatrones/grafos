#ifndef CURSO_H
#define CURSO_H
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Curso{
private:
    string nombreCurso;
    string nombreLargoCurso;
    int semestre;
    // Se agrupan por tipo, y se enumera los grupos
    map<string, vector<string>> tiposDeCurso;
    // Se agrupan por grupos y se enumeran los tipos
    map<string, vector<string>> gruposDeCurso;

public:
    Curso(string nombreCorto){
        this->nombreCurso = nombreCorto;
    }
    Curso(string nombreCorto, string nombreLargo){
        this->nombreCurso = nombreCorto;
        this->nombreLargoCurso = nombreLargo;
    }
    Curso(string nombreCorto, int idSemestre){
        this->nombreCurso = nombreCorto;
        this->semestre = idSemestre;
    }
    Curso(string nombreCorto, string nombreLargo, int idSemestre){
        this->nombreCurso = nombreCorto;
        this->nombreLargoCurso = nombreLargo;
        this->semestre = idSemestre;
    }

    void mostrarValores(){
        cout << endl;
        cout << "NOMBRE CORTO: " << this->nombreCurso << endl;
        cout << "NOMBRE LARGO: " << this->nombreLargoCurso << endl;
        cout << "NUMERO DE SEMESTRE: " << this->semestre << endl;
        cout << "TIPOS CREADOS: " << endl;
        for(auto & tipo: this->tiposDeCurso){
            cout << "\t" << tipo.first << " = ";
            for(auto & grupo: tipo.second){
                cout << grupo << ", ";
            }
            cout << endl;
        }
        cout << "GRUPOS CREADOS: " << endl;
        for(auto & grupo: this->gruposDeCurso){
            cout << "\t" << grupo.first << " = ";
            for(auto & tipo: grupo.second){
                cout << tipo << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool crearTipoCurso(string nombreTipo){
        if (this->tiposDeCurso.find(nombreTipo) == this->tiposDeCurso.end()){
            vector<string> grupo;
            this->tiposDeCurso[nombreTipo] = grupo;
        }
        return true;
    }

    bool crearGrupoCurso(string nombreGrupo){
        if (this->gruposDeCurso.find(nombreGrupo) == this->gruposDeCurso.end()){
            vector<string> grupo;
            this->gruposDeCurso[nombreGrupo] = grupo;
        }
        return true;
    }

    // Encontrar si existe un grupo dentro del tipo de curso
    int encontrarGrupoEnTipo(string tipoCurso, string nombreGrupo){
        if (this->tiposDeCurso.find(tipoCurso) != this->tiposDeCurso.end()){
            vector<string> gruposDelTipo = this->tiposDeCurso[tipoCurso];
            for (size_t idx = 0; idx < gruposDelTipo.size(); idx++){
                if (nombreGrupo == gruposDelTipo[idx])
                    return idx;
            }
        }
        return -1;
    }

    bool crearGrupoTipoCurso(string tipoSeleccionado, string nombreGrupo){
        if (this->encontrarGrupoEnTipo(tipoSeleccionado, nombreGrupo) < 0){
            this->tiposDeCurso[tipoSeleccionado].push_back(nombreGrupo);
        }
        if (this->gruposDeCurso.find(nombreGrupo) == this->gruposDeCurso.end()){
            this->gruposDeCurso[nombreGrupo].push_back(tipoSeleccionado);
        }
        return true;
    }

    int encontrarTipoEnGrupo(string grupoCurso, string nombreTipo){
        if (this->gruposDeCurso.find(grupoCurso) != this->gruposDeCurso.end()){
            vector<string> tiposDelGrupo = this->gruposDeCurso[grupoCurso];
            for (size_t idx = 0; idx < tiposDelGrupo.size(); idx++){
                if (nombreTipo == tiposDelGrupo[idx])
                    return idx;
            }
        }
        return -1;
    }

    bool crearTipoGrupoCurso(string grupoSeleccionado, string nombreTipo){
        if (this->encontrarTipoEnGrupo(grupoSeleccionado, nombreTipo) < 0){
            this->gruposDeCurso[grupoSeleccionado].push_back(nombreTipo);
        }
        if (this->tiposDeCurso.find(nombreTipo) == this->gruposDeCurso.end()){
            this->tiposDeCurso[nombreTipo].push_back(grupoSeleccionado);
        }
        return true;
    }

};


#endif // CURSO_H
