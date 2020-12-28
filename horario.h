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

    size_t encontrarSemestre(string nombreSemestre){
        for (size_t idx = 0; idx < this->semestres.size(); idx++){
            if (this->semestres[idx] == nombreSemestre)
                return idx;
        }
        return -1;
    }

    size_t encontrarProfesor(string nombreProfesor){
        for (size_t idx = 0; idx < this->profesores.size(); idx++){
            if (this->profesores[idx] == nombreProfesor)
                return idx;
        }
        return -1;
    }

    size_t crearProfesor(string nombreProfesor){
        size_t idProfesor = this->encontrarProfesor(nombreProfesor);
        if (idProfesor < 0){
            this->profesores.push_back(nombreProfesor);
            return 0;
        }
        return idProfesor;
    }

    size_t crearSemestre(string nombreSemestre){
        size_t idSemestre = this->encontrarSemestre(nombreSemestre);
        if (idSemestre < 0){
            this->semestres.push_back(nombreSemestre);
            return 0;
        }
        return idSemestre;
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

};


#endif // HORARIO_H
