#ifndef CURSO_H
#define CURSO_H
#include "horario.h"

class Curso{
private:
    string nombreCurso;
    string nombreLargoCurso;
    int semestre;
    int profesor;
    // Vector para guardar los tipos que tiene el curso
    vector<string> tiposCursos;
    // Vector para guardar los grupos que tiene el curso
    vector<string> gruposCursos;

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



    int buscarAsignacionProfesor(int idProfesor, string tipoCurso, string grupoCurso){
        if (this->profesorAsignado.find(idProfesor) == this->profesorAsignado.end()) return -1;
        for (int idx = 0; idx < this->profesorAsignado[idProfesor].size(); idx++){
            if (this->profesorAsignado[idProfesor][idx].first == tipoCurso && this->profesorAsignado[idProfesor][idx].second == grupoCurso)
                return idx;
        }
        return -1;
    }

    // Usando PAIR para asignar tipo dentro del MAP de PROFESORES_ASIGNADOS
    int asignarProfesorSoloAlTipo(int idProfesor, string tipoCurso){
        this->profesor = -1;
        int posAsignado = this->buscarAsignacionProfesor(idProfesor, tipoCurso, "");
        if (posAsignado < 0){
            pair<string, string> tipoGrupoAsignado(tipoCurso, "");
            this->profesorAsignado[idProfesor].push_back(tipoGrupoAsignado);
            if (this->encontrarTipoCurso(tipoCurso) < 0){
                this->tiposCursos.push_back(tipoCurso);
            }
            return this->profesorAsignado[idProfesor].size() - 1;
        }
        return posAsignado;
    }

    // Usando PAIR para asignar grupo dentro del MAP de PROFESORES_ASIGNADOS
    int asignarProfesorSoloAlGrupo(int idProfesor, string grupoCurso){
        this->profesor = -1;
        int posAsignado = this->buscarAsignacionProfesor(idProfesor, "", grupoCurso);
        if (posAsignado < 0){
            pair<string, string> tipoGrupoAsignado("", grupoCurso);
            this->profesorAsignado[idProfesor].push_back(tipoGrupoAsignado);
            if (this->encontrarGrupoCurso(grupoCurso) < 0){
                this->gruposCursos.push_back(grupoCurso);
            }
            return this->profesorAsignado[idProfesor].size() - 1;
        }
        return posAsignado;
    }

    // Usando PAIR para asignar tipo y grupo dentro del MAP de PROFESORES_ASIGNADOS
    int asignarProfesorAlTipoYgrupo(int idProfesor, string tipoCurso, string grupoCurso){
        this->profesor = -1;
        int posAsignado = this->buscarAsignacionProfesor(idProfesor, tipoCurso, grupoCurso);
        if (posAsignado < 0){
            pair<string, string> tipoGrupoAsignado(tipoCurso, grupoCurso);
            this->profesorAsignado[idProfesor].push_back(tipoGrupoAsignado);
            if (this->encontrarTipoCurso(tipoCurso) < 0){
                this->tiposCursos.push_back(tipoCurso);
            }
            if (this->encontrarGrupoCurso(grupoCurso) < 0){
                this->gruposCursos.push_back(grupoCurso);
            }
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
        cout << "TIPOS CREADOS: ";
        for(auto & tipo: this->tiposCursos){
            cout << tipo << ", ";
        }
        cout << endl;
        cout << "GRUPOS CREADOS: ";
        for(auto & grupo: this->gruposCursos){
            cout << grupo << ", ";
        }
        cout << endl;
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

    int encontrarTipoCurso(string tipoCurso){
        for (int idx = 0; idx < this->tiposCursos.size(); idx++)
            if (this->tiposCursos[idx] == tipoCurso)
                return idx;
        return -1;
    }

    int encontrarGrupoCurso(string grupoCurso){
        for(int idx = 0; idx < this->gruposCursos.size(); idx++)
            if (this->gruposCursos[idx] == grupoCurso)
                return idx;
        return -1;
    }

    friend class Horario;
};


#endif // CURSO_H
