#ifndef CURSO_H
#define CURSO_H
#include "horario.h"

class Curso{
private:
    string nombreCurso;
    string nombreLargoCurso;
    int semestre;
    int profesor;
    // Se agrupan por tipo, y se enumera los grupos
    map<string, vector<string>> tiposDeCurso;
    // Se agrupan por grupos y se enumeran los tipos
    map<string, vector<string>> gruposDeCurso;
    // Se agrupan al profesor que enseña por Tipos de clases
    map<int, vector<string>> profesorHaciaTipos;
    // Se agrupan al profesor que enseña por Grupos de clase
    map<int, vector<string>> profesorHaciaGrupos;

    // Se agrupan el ID del profesor para el GRUPO y TIPO que dicta clases
    map<int, vector<pair<string, string>>> profesorAsignado;

public:
    Curso(string nombreCorto){
        this->nombreCurso = nombreCorto;
        this->nombreLargoCurso = "";
        this->semestre = -1;
        this->profesor = -1;
    }
    Curso(string nombreCorto, string nombreLargo){
        this->nombreCurso = nombreCorto;
        this->nombreLargoCurso = nombreLargo;
        this->semestre = -1;
        this->profesor = -1;
    }
    Curso(string nombreCorto, int idSemestre){
        this->nombreCurso = nombreCorto;
        this->semestre = idSemestre;
        this->nombreLargoCurso = "";
        this->profesor = -1;
    }
    Curso(string nombreCorto, string nombreLargo, int idSemestre){
        this->nombreCurso = nombreCorto;
        this->nombreLargoCurso = nombreLargo;
        this->semestre = idSemestre;
        this->profesor = -1;
    }

    int asignarProfesor(int idProfesor){
        return this->profesor = idProfesor;
    }

    int asignarSemestre(int idSemestre){
        return this->semestre = idSemestre;
    }

    int encontrarDictadoDeProfesorTipo(int idProfesor, string tipoCurso){
        if (this->profesorHaciaTipos.find(idProfesor) == this->profesorHaciaTipos.end()){
            for (int idx = 0; idx < this->profesorHaciaTipos[idProfesor].size(); idx++){
                if (this->profesorHaciaTipos[idProfesor][idx] == tipoCurso)
                    return idx;
            }
        }
        return -1;
    }

    int encontrarDictadoDeProfesorGrupo(int idProfesor, string grupoCurso){
        if (this->profesorHaciaGrupos.find(idProfesor) == this->profesorHaciaGrupos.end()){
            for (int idx = 0; idx < this->profesorHaciaGrupos[idProfesor].size(); idx++){
                if (this->profesorHaciaGrupos[idProfesor][idx] == grupoCurso)
                    return idx;
            }
        }
        return -1;
    }

    int asignarProfesorTipo(int idProfesor, string tipoCurso){
        if (this->tiposDeCurso.find(tipoCurso) != this->tiposDeCurso.end()){
            int posTipo = this->encontrarDictadoDeProfesorTipo(idProfesor, tipoCurso);
            this->profesor = -1;
            if (posTipo < 0){
                this->profesorHaciaTipos[idProfesor].push_back(tipoCurso);
                return this->profesorHaciaTipos.size() - 1;
            }
            return posTipo;
        }
        return -1;
    }

    int asignarProfesorGrupo(int idProfesor, string grupoCurso){
        if (this->gruposDeCurso.find(grupoCurso) != this->gruposDeCurso.end()){
            int posTipo = this->encontrarDictadoDeProfesorGrupo(idProfesor, grupoCurso);
            this->profesor = -1;
            if (posTipo < 0){
                this->profesorHaciaGrupos[idProfesor].push_back(grupoCurso);
                return this->profesorHaciaGrupos.size() - 1;
            }
            return posTipo;
        }
        return -1;
    }

    bool asignarProfesorTipoGrupo(int idProfesor, string tipoCurso, string grupoCurso){
        if (this->tiposDeCurso.find(tipoCurso) == this->tiposDeCurso.end()) return false;
        if (this->gruposDeCurso.find(grupoCurso) == this->gruposDeCurso.end()) return false;
        this->profesor = -1;
        this->asignarProfesorTipo(idProfesor, grupoCurso);
        this->asignarProfesorGrupo(idProfesor, grupoCurso);

        return true;
    }

    int buscarAsignacionProfesor(int idProfesor, string tipoCurso, string grupoCurso){
        if (this->profesorAsignado.find(idProfesor) == this->profesorAsignado.end()) return -1;
        for (int idx = 0; idx < this->profesorAsignado[idProfesor].size(); idx++){
            if (this->profesorAsignado[idProfesor][idx].first == tipoCurso && this->profesorAsignado[idProfesor][idx].second == grupoCurso)
                return idx;
        }
        return -1;
    }

    int asignarProfesorAlTipoYgrupo(int idProfesor, string tipoCurso, string grupoCurso){
        cout << "COMPROBANDO TIPO" << endl;
        if (this->tiposDeCurso.find(tipoCurso) == this->tiposDeCurso.end()) return -1;
        cout << "SI EXISTE TIPO" << endl;
        if (this->gruposDeCurso.find(grupoCurso) == this->gruposDeCurso.end()) return -1;
        cout << "SI EXISTE GRUPO" << endl;
        this->profesor = -1;
        int posAsignado = this->buscarAsignacionProfesor(idProfesor, tipoCurso, grupoCurso);
        if (posAsignado < 0){
            pair<string, string> tipoGrupoAsignado(tipoCurso, grupoCurso);
            this->profesorAsignado[idProfesor].push_back(tipoGrupoAsignado);
            return this->profesorAsignado[idProfesor].size() - 1;
        }
        return posAsignado;
    }

    void mostrarValores(){
        cout << endl;
        cout << "NOMBRE CORTO: " << this->nombreCurso << endl;
        cout << "NOMBRE LARGO: " << this->nombreLargoCurso << endl;
        cout << "ID PROFESOR: " << this->profesor << endl;
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
        cout << "PROFESOR ASIGNADO A: " << endl;
        for (auto & profesor: this->profesorAsignado){
            cout << "\t" << profesor.first << " = ";
            for (auto & asignado: profesor.second){
                cout << "(" << asignado.first << "-" << asignado.second << "), ";
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

    // Función para agregar un grupo al tipo de curso
    bool crearGrupoTipoCurso(string tipoSeleccionado, string nombreGrupo){
        if (this->encontrarGrupoEnTipo(tipoSeleccionado, nombreGrupo) < 0){
            this->tiposDeCurso[tipoSeleccionado].push_back(nombreGrupo);
        }
        if (this->encontrarTipoEnGrupo(nombreGrupo, tipoSeleccionado) < 0){
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

    // Función para crear un tipo de curso a un grupo
    bool crearTipoGrupoCurso(string grupoSeleccionado, string nombreTipo){
        if (this->encontrarTipoEnGrupo(grupoSeleccionado, nombreTipo) < 0){
            this->gruposDeCurso[grupoSeleccionado].push_back(nombreTipo);
        }
        if (this->encontrarGrupoEnTipo(nombreTipo, grupoSeleccionado) < 0){
            this->tiposDeCurso[nombreTipo].push_back(grupoSeleccionado);
        }
        return true;
    }

    friend class Horario;
};


#endif // CURSO_H
