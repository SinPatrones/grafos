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

    vector<int> paleta;

    // Lista de cursos ordenados a manera de colección
    // en el cual la CLAVE es el nombre corto del curso
    // y el VALOR es el puntero(dirección) del curso creado en memoria
    map<string, Curso *> cursos;

    unsigned int cantidadCursos;

    Grafo<string> * grafo;

    string extrarNombreCurso(string nombreCurso){
        size_t pos = nombreCurso.find(":");
        if (pos == string::npos){
            pos = nombreCurso.find("-");
            if (pos == string::npos)
                return nombreCurso; // si no tiene marca de tener grupo o tipo, devolvera el mismo nombre
        }

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

public:
    Horario(vector<int> paleta){
        this->grafo = nullptr;
        this->cantidadCursos = 0;
        this->paleta = paleta;
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

    bool existeCurso(string nombreCortoCurso){
        return !(this->cursos.find(nombreCortoCurso) == this->cursos.end());
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

    // Asignar profesor por nombre ----- DE MANERA GENERAL PARA EL CURSO
    bool asignarProfesorAlCurso(string nombreCortoCurso, string nombreProfesor){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end())
            return false;
        this->cursos[nombreCortoCurso]->asignarProfesor(this->crearProfesor(nombreProfesor));
        return true;
    }

    bool asignarProfesorAtipoYgrupo(string nombreCortoCurso, string nombreTipo, string nombreGrupo, string nombreProfesor){
        if (!this->existeCurso(nombreCortoCurso)) return false;
        if (nombreTipo.length() < 1){
            if (this->cursos[nombreCortoCurso]->asignarProfesorSoloAlGrupo(this->crearProfesor(nombreProfesor), nombreGrupo) >= 0){
                this->crearGrupo(nombreGrupo);
                return true;
            }
            return false;
        }else if (nombreGrupo.length() < 1){
            if (this->cursos[nombreCortoCurso]->asignarProfesorSoloAlTipo(this->crearProfesor(nombreProfesor), nombreTipo) >= 0){
                this->crearTipoCurso(nombreTipo);
                return true;
            }
            return false;
        }else{
            cout << "# INSERTANDO AMBOS GRUPOS" << endl;
            if (this->cursos[nombreCortoCurso]->asignarProfesorAlTipoYgrupo(this->crearProfesor(nombreProfesor), nombreTipo, nombreGrupo) >= 0){
                this->crearGrupo(nombreGrupo);
                this->crearTipoCurso(nombreTipo);
                return true;
            }
            return false;
        }
    }

    // Asignar Semestre por nombre
    bool asignarSemestreAlCurso(string nombreCortoCurso, string nombreSemestre){
        if (this->cursos.find(nombreCortoCurso) == this->cursos.end())
            return false;
        this->cursos[nombreCortoCurso]->asignarSemestre(this->crearSemestre(nombreSemestre));
        return true;
    }

    // Asignar profesor por ID ----- DE MANERA GENERAL PARA EL CURSO
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


    // Con esta función cargamos todos los datos al GRAFO
    bool cargarDatos(){
        this->grafo = new Grafo<string>("horario", true); // RECREAMOS el grafo
        map<string, Curso *> nombresCursos;


        for (auto & curso1: this->cursos){// curso es pair<string, Curso *>
            // Vamos a estructurar el VERTICES para insertar en el grafo
            if (curso1.second->profesor == -1 && curso1.second->profesorAsignado.size() > 0){
                for (auto & profesor: curso1.second->profesorAsignado){
                    for(auto & tipoGrupo: profesor.second){
                        string nombreCurso = curso1.first;
                        if (tipoGrupo.second != "" && tipoGrupo.first != ""){
                            nombreCurso += ":" + tipoGrupo.second + "-" + tipoGrupo.first;
                        }else if(tipoGrupo.second != "" && tipoGrupo.first == ""){
                            nombreCurso += ":" + tipoGrupo.second;
                        }else if(tipoGrupo.second == "" && tipoGrupo.first != ""){
                            nombreCurso += "-" + tipoGrupo.first;
                        }
                        nombresCursos[nombreCurso] = curso1.second;
                    }
                }
            }else{
                string nombreCurso = curso1.first;
                nombresCursos[nombreCurso] = curso1.second;
            }

        }
        // MOSTRANDO E ISNERTANDO AL GRAFO
        for (auto & curso: nombresCursos){
            this->grafo->insertarVertice(curso.first);
            cout << "CURSO: " << curso.first << endl;
        }
        cout << endl;

        // Empezamos a aplicar las reglas para cada curso
        for (auto & cursoPivote: nombresCursos){
            for (auto & curso: nombresCursos){
                if (cursoPivote.first != curso.first){ // Aseguramos de no crear lazos en el grafo
                    // Crearmos aristas con los cursos que son del mismo semestre
                    if (cursoPivote.second->semestre == curso.second->semestre && cursoPivote.second->semestre != -1){
                        // Pero tenemos que tomar en cuenta que aún siendo del mismo semestre
                        // pueden ser de diferente grupo y esos no tendrían que tener una arista
                        string nombreCursoPivote = this->extrarNombreCurso(cursoPivote.first);
                        string nombreCurso = this->extrarNombreCurso(curso.first);

                        char grupoCursoPivote = this->extraerGrupoCurso(cursoPivote.first);
                        char grupoCurso = this->extraerGrupoCurso(curso.first);

                        string tipoCursoPivote = this->extraerTipoCurso(cursoPivote.first);
                        string tipoCurso = this->extraerTipoCurso(curso.first);

                        // Si son del mismo grupo y del mismo tipo de curso, no se pueden llevar en simultaneo
                        // a su vez si no tienen ni tipo ni grupo también se creara aristas
                        if (grupoCursoPivote == grupoCurso && tipoCursoPivote == tipoCurso){
                            this->grafo->insertarArista(cursoPivote.first, curso.first);
                        }

                        // Si no tiene grupo pero el otro curso si lo tiene, entonces se uniran (arista)
                        if (grupoCursoPivote == ' ' && grupoCurso != ' '){
                            this->grafo->insertarArista(cursoPivote.first, curso.first);
                        }

                        // si no tiene tipo y el otro si, entonces se uniran (arista)
                        if (tipoCursoPivote == "  " && tipoCurso != "  "){
                            this->grafo->insertarArista(cursoPivote.first, curso.first);
                        }

                        // Todos que tengna el mismo grupo no pueden ser llevados a la misma hora
                        if (grupoCursoPivote == grupoCurso){
                            this->grafo->insertarArista(cursoPivote.first, curso.first);
                        }

                        //cout << "-------> " << cursoPivote.first << " - " << curso.first << endl;
                        //cout << "CONDICION: " << (grupoCursoPivote == ' ' && grupoCurso != ' ') <<  "-->" << grupoCursoPivote << "-" << grupoCurso << endl;


                        if(nombreCursoPivote == nombreCurso && grupoCursoPivote == grupoCurso){
                            this->grafo->insertarArista(cursoPivote.first, curso.first);
                        }

                    }

                    // LA otra condición es que si tienen el mismo profesor
                    if (cursoPivote.second->profesor == curso.second->profesor && cursoPivote.second->profesor != -1){
                        this->grafo->insertarArista(cursoPivote.first, curso.first);
                    }

                }
            }

        }

        this->grafo->colorearHorario(this->paleta);
        this->grafo->crearArchivoDot();

        return true;

    }
};


#endif // HORARIO_H
