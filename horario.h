#ifndef HORARIO_H
#define HORARIO_H
#include "grafo.h"

class Horario{
private:
    vector<string> grupos;
    vector<string> tiposDeCursos;
    // <NOMBRE CURSO PRINCIPAL , GRUPOS DE CURSO>
    map<string, vector<string>> cursos; // lista de los cursos y sus grupos que tiene
    map<string, int> semestreDelCurso; // muesta el id del semestre al que pertenece el curso
    vector<string> listaSemestres; // lista de nombres de Semestres
    vector<string> listaProfesores; // Lista de profesores, y su indice será su ID
    map<int, vector<string>> profesoresDicta;


    Grafo<string> grafo;

public:
    Horario(){
        this->grupos = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
        this->tiposDeCursos = {};
    }

    // mostrar cursos registrados y sus grupos
    void mostrarCursos(){
        cout << "-------- MOSTRANDO CURSOS REGISTRADOS ------------" << endl;
        for (auto & curso: this->cursos){
            string semestre = "";
            int idSemestre = this->semestreDelCurso[curso.first];
            if (idSemestre < 0){
                semestre = "(Sin Semestre)";
            }else{
                semestre = "( " + this->listaSemestres[idSemestre] + " )";
            }
            cout << curso.first << " " << semestre << " = ";
            for (auto & grupo: curso.second){
                cout << grupo << ", ";
            }
            cout << endl;
        }
        cout << "---------------------------------------------------" << endl;
    }

    string extrarNombreCurso(string nombreCurso){
        size_t pos = nombreCurso.find(":");
        if (pos == string::npos)
            return nombreCurso; // si no tiene marca de tener grupo da el mismo nombre

        string soloNombre = "";
        for (size_t idx = 0; idx < pos; idx++){
            soloNombre += nombreCurso[idx];
        }

        return soloNombre;
    }

    char extraerGrupoCurso(string nombreCurso){
        size_t pos = nombreCurso.find(":");
        if (pos == string::npos)
            return ' ';

        return nombreCurso[pos + 1];
    }

    string extraerTipoCurso(string nombreCurso){
        size_t pos = nombreCurso.find("-");
        if (pos == string::npos)
            return "  ";

        return nombreCurso.substr(pos + 1, 2);
    }

    int encontrarSemestre(string nombreSemestre){
        for (int idx = 0; idx < this->listaSemestres.size(); idx++){
            if (nombreSemestre == this->listaSemestres[idx])
                return idx;
        }
        return -1;
    }

    int crearSemestre(string nombreSemestre){
        int id = this->encontrarSemestre(nombreSemestre);
        if (id < 0){
            this->listaSemestres.push_back(nombreSemestre);
            return this->listaSemestres.size() - 1;
        }
        return id;
    }

    int encontrarProfesor(string nombreProfesor){
        for (int idx = 0; idx < this->listaProfesores.size(); idx++){
            if (nombreProfesor == this->listaProfesores[idx])
                return idx;
        }
        return -1;
    }

    int crearProfesor(string nombreProfesor){
        int id = this->encontrarProfesor(nombreProfesor);
        if (id < 0){
            this->listaProfesores.push_back(nombreProfesor);
            return this->listaProfesores.size() - 1;
        }
        return id;
    }

    // función que solo insertara un curso SI es que no existe
    // sin asignarle un semestre
    bool crearCurso(string nombreCurso){
        vector<string> grupo;
        if (this->cursos.find(nombreCurso) == this->cursos.end()){
            this->cursos[nombreCurso] = grupo;
            this->semestreDelCurso[nombreCurso] = -1;
            return true;
        }
        return false;
    }

    // crear curso con base al nombre del semestre
    bool crearCurso(string nombreCurso, string nombreSemestre){
        int idSemestre = this->encontrarSemestre(nombreSemestre);
        if (idSemestre < 0)
            return false;   // cuando no exista el nombre del semestre no crea el curso

        vector<string> grupo;
        if (this->cursos.find(nombreCurso) == this->cursos.end()){
            this->cursos[nombreCurso] = grupo;
            this->semestreDelCurso[nombreCurso] = idSemestre;
            return true;
        }
        return false;
    }

    // crear curso con base al ID del semestre
    bool crearCurso(string nombreCurso, int idSemestre){
        if (idSemestre < 0 || idSemestre > this->listaSemestres.size())
            return false;

        vector<string> grupo;
        if (this->cursos.find(nombreCurso) == this->cursos.end()){
            this->cursos[nombreCurso] = grupo;
            this->semestreDelCurso[nombreCurso] = idSemestre;
            return true;
        }
        return false;
    }

    // insertará un grupo
    bool crearGrupoEnCurso(string cursoMaster){
        int cantidadGrupos = this->cursos[cursoMaster].size();

        // dara false si la cantidad de grupo excede el limite establecido
        if (cantidadGrupos > this->grupos.size()) return false;

        // si no hay excedente, continuamos
        this->cursos[cursoMaster].push_back(cursoMaster + ":" + this->grupos[cantidadGrupos]);
        return true;
    }

    bool crearTipoCurso(string cursoMaster, string tipoCurso){

    }

};


#endif // HORARIO_H
