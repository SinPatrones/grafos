#ifndef HORARIO_H
#define HORARIO_H
#include "grafo.h"
#include "curso.h"

class Horario{
private:
    vector<string> grupos; // Lista para guardar los grupos que se hayan creado en todo el horario (ejm: a, b, c)
    vector<string> tiposDeCursos;   // Lista de los TIPOS de cursos que se hayan creado en el horario (ejm: LAboratorio, TEoria, PRacticas)
    vector<string> semestres;
    vector<string> profesores;

    // Lista de cursos ordenados a manera de colección
    // en el cual la CLAVE es el nombre corto del curso
    // y el VALOR es el puntero(dirección) del curso creado en memoria
    map<string, Curso *> cursos;

    unsigned int cantidadCursos;

    Grafo<string> grafo;

public:
    Horario(){
        this->cantidadCursos = 0;
    }

    bool crearCurso(string nombreCorto){
        this->cursos[nombreCorto] = new Curso(nombreCorto);
        this->cantidadCursos++;
        return true;
    }

    bool crearCurso(string nombreCorto, string nombreLargo){
        this->cursos[nombreCorto] = new Curso(nombreCorto, nombreLargo);
        this->cantidadCursos++;
        return true;
    }

    bool crearCurso(string nombreCorto, int idSemestre){
        this->cursos[nombreCorto] = new Curso(nombreCorto, idSemestre);
        this->cantidadCursos++;
        return true;
    }

    bool crearCurso(string nombreCorto, string nombreLargo, int idSemestre){
        this->cursos[nombreCorto] = new Curso(nombreCorto, nombreLargo, idSemestre);
        this->cantidadCursos++;
        return true;
    }

    void mostrarInfoHorario(){
        cout << "-------- SEMESTRES ---------" << endl;
        for (auto & semestre: this->semestres){
            cout << semestre << ", ";
        }
        cout << endl << endl;
        cout << "----- TIPOS DE CURSOS ------" << endl;
        for (auto & tipos: this->tiposDeCursos){
            cout << tipos << ", ";
        }
        cout << endl << endl;
        cout << "---------- GRUPOS ----------" << endl;
        for (auto & grupo: this->grupos){
            cout << grupo << ", ";
        }
        cout << endl << endl;
        cout << "-------- PROFESORES --------" << endl;
        for (auto & profesor: this->profesores){
            cout << profesor << ", ";
        }
        cout << endl << endl;
        cout << "---------- CURSOS ----------" << endl;
        for(auto & curso: this->cursos){
            curso.second->mostrarValores();
        }
    }

    int encontrarSemestre(string nombreSemestre){
        for (int idx = 0; idx < this->semestres.size(); idx++){
            if (this->semestres[idx] == nombreSemestre)
                return idx;
        }
        return -1;
    }

    int encontrarProfesor(string nombreProfesor){
        for (int idx = 0; idx < this->profesores.size(); idx++){
            if (this->profesores[idx] == nombreProfesor)
                return idx;
        }
        return -1;
    }

    int encontrarGrupo(string nombreGrupo){
        for (int idx = 0; idx < this->grupos.size(); idx++){
            if (this->grupos[idx] == nombreGrupo)
                return idx;
        }
        return -1;
    }

    int encontrarTipo(string nombreTipo){
        for (int idx = 0; idx < this->tiposDeCursos.size(); idx++){
            if (this->tiposDeCursos[idx] == nombreTipo)
                return idx;
        }
        return -1;
    }

    int crearProfesor(string nombreProfesor){
        int idProfesor = this->encontrarProfesor(nombreProfesor);
        if (idProfesor < 0){
            this->profesores.push_back(nombreProfesor);
            return this->profesores.size() - 1;
        }
        return idProfesor;
    }

    int crearSemestre(string nombreSemestre){
        int idSemestre = this->encontrarSemestre(nombreSemestre);
        if (idSemestre < 0){
            this->semestres.push_back(nombreSemestre);
            return this->semestres.size() - 1;
        }
        return idSemestre;
    }

    int crearGrupo(string nombreGrupo){
        int idGrupo = this->encontrarGrupo(nombreGrupo);
        if (idGrupo < 0){
            this->grupos.push_back(nombreGrupo);
            return this->grupos.size() - 1;
        }
        return idGrupo;
    }

    int crearTipoCurso(string nombreCortoTipo){
        int idTipoCurso = this->encontrarTipo(nombreCortoTipo);
        if (idTipoCurso < 0){
            this->tiposDeCursos.push_back(nombreCortoTipo);
            return this->tiposDeCursos.size() - 1;
        }
        return idTipoCurso;
    }

    // Asignar profesor por nombre
    bool asignarProfesorAlCurso(string nombreCortoCurso, string nombreProfesor){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end())
            return false;
        this->cursos[nombreCortoCurso]->asignarProfesor(this->crearProfesor(nombreProfesor));
        return true;
    }

    // Asignar Semestre por nombre
    bool asignarSemestreAlCurso(string nombreCortoCurso, string nombreSemestre){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end())
            return false;
        this->cursos[nombreCortoCurso]->asignarSemestre(this->crearSemestre(nombreSemestre));
        return true;
    }

    // Asignar profesor por ID
    bool asignarProfesorAlCurso(string nombreCortoCurso, int idProfesor){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->cursos[nombreCortoCurso]->asignarProfesor(idProfesor);
        return true;
    }

    // Asignar semestre por ID
    bool asignarSemestreAlCurso(string nombreCortoCurso, int idSemestre){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->cursos[nombreCortoCurso]->asignarSemestre(idSemestre);
        return true;
    }

    bool crearSoloGrupoAlCurso(string nombreCortoCurso, string nombreCortoGrupo){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->crearGrupo(nombreCortoCurso);
        this->cursos[nombreCortoCurso]->crearGrupoCurso(nombreCortoGrupo);
        return true;
    }

    bool crearSoloTipoAlCurso(string nombreCortoCurso, string nombreCortoTipo){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->crearTipoCurso(nombreCortoTipo);
        this->cursos[nombreCortoCurso]->crearTipoCurso(nombreCortoTipo);
        return true;
    }

    bool crearGrupoAlTipo(string nombreCortoCurso, string tipo, string grupo){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->cursos[nombreCortoCurso]->crearGrupoTipoCurso(tipo, grupo);
        this->crearGrupo(grupo);
        return true;
    }

    bool crearTipoAlGrupo(string nombreCortoCurso, string grupo, string tipo){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end()) // Si el curso no existe, devuelve false
            return false;
        this->cursos[nombreCortoCurso]->crearTipoGrupoCurso(grupo, tipo);
        this->crearTipoCurso(tipo);
        this->crearGrupo(grupo);
        return true;
    }

};


#endif // HORARIO_H
