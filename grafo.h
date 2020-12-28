#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>

// LISTA DE COLORES QUE PUEDE USARSE EN EL GRAFO
enum Color{
    sincolor,
    amarillo, // 1
    verde, // 2
    rojo,  // 3
    morado, // 4
    azul, // 5
    turquoise3, //6
    firebrick, // 7
    goldenrod3, // 8
    aquamarine2, // 9
    darkolivegreen3, // 10
    mistyrose2, // 11
    chocolate, // 12
};

using namespace std;

template <typename T>
class Arista;

template <typename T>
class Grafo;

// CLASE VERTICE
template <typename T>
class Vertice{
private:
    T valor;        // El valor de vertices que es de tipo T, el cual se sustituye por un tipo que asignemos (int, string, char, float)
    unsigned int gradoPositivo;
    unsigned int gradoNegativo;
    vector<Arista<T> *> aristas; // Una lista de ARISTAS - Ver la Clase Arista
    int valorColor = sincolor;  // El color que se le asigne

public:
    Vertice(T valor){
        this->valor = valor;
        this->gradoPositivo = 0;
        this->gradoNegativo = 0;
    }
    vector<Arista<T> *> obtenerAristas(){
        return this->aristas;
    }
    T obtenerValor(){
        return this->valor;
    }

    // funciones de ayuda
    Vertice<T> * operator ++( int ){ // Sobrecarga de post-incremento -> para grado positivo del vertice
        this->gradoPositivo++;
        return this;
    }
    // funciones de ayuda
    Vertice<T> * operator ++(){
        this->gradoNegativo++; // Sobrecarga de pre-incremento -> para grado negativo del vertice
        return this;
    }

    // definimos a GRAFO como Amigo de la clase Vertice
    // para que pueda acceder a métodos y miembros datos privados
    friend class Grafo<T>;
};


// CLASE ARISTA
template <typename T>
class Arista{
private:
    Vertice<T> * extremo; // Puntero a un VERTICE extremo de la arista
    float peso; // Peso de la arista, tipo float

public:
    // Constructor de ARISTA con peso
    Arista(Vertice<T> * vertice, float nuevoPeso){
        this->extremo = vertice;
        this->peso = nuevoPeso;
    }

    // Constructor de ARISTA sin peso
    Arista(Vertice<T> * arista){
        this->extremo = arista;
        this->peso = 0;
    }

    // Obtener dirección de memoria del EXTREMO de la arista
    Vertice<T> * obtenerExtremo(){
        return this->extremo;
    }

    // Obtener el peso de la Arista
    float obtenerPeso(){
        return this->peso;
    }

    // definimos a GRAFO como Amigo de la clase Vertice
    // para que pueda acceder a métodos y miembros datos privados
    friend class Grafo<T>;
};

// CLASE GRAFO
template <typename T>
class Grafo{
private:
    // Colección de de VERTICES, definida por CLAVE - VALOR
    // Donde la CLAVE es el nombre/valor del VERTICE
    // y el VALOR es el puntero(dirección) del VERTICE creado en memoria
    map<T, Vertice<T> *> vertices;
    /*
     vertice["ED2"] --> Valor que se haya guardado: El puntero de Vertice<T> (#523546345)
    [
            STRING
            "ED2"
            FIRST    SECOND
        pair< T  , Vertice<T> *> vertice,
        pair< T  , Vertice<T> *> vertice,
        pair< T  , Vertice<T> *> vertice,
        pair< T  , Vertice<T> *> vertice,
    ]
    */

    unsigned int cantidadVertices;
    unsigned int cantidadAristas;
    bool dirigido;
    bool multigrafo;
    bool permitirLazos;
    bool autoinsertar;
    bool ponderado;
    string nombreArchivo;
    vector<T> valoresVertices; // Lista de solo nombres de VERTICES
public:
    Grafo(string nombreArchivo = "tmp", bool autoinsertar = false, bool permitirLazos = false, bool dirigido = false, bool ponderado = false, bool multigrafo = false){
        this->cantidadVertices = 0;
        this->cantidadAristas = 0;
        this->dirigido = dirigido;
        this->multigrafo = multigrafo;
        this->permitirLazos = permitirLazos;
        this->autoinsertar = autoinsertar; // Si se inserta una arista con Vertices que no existen, pues se crearan en ese instante
        this->ponderado = ponderado;
        this->nombreArchivo = nombreArchivo;
    }

    // Constructor copia
    Grafo(const Grafo & original){
        (*this) = original;
    }

    // Función para encontrar la dirección de memoria de un vertice, siendo buscado por el valor del vertice
    Vertice<T> * encontrarVertice(T valor){
        auto itEncontrado = this->vertices.find(valor);
        if (itEncontrado == this->vertices.end())
            return NULL; // si el VERTICE no existe, devuelve NULL;
        return itEncontrado->second;    // SI es encontrado, devolvera el VALOR(ver linea 122) que es la dirección de memoria del VERTICE
    }

    // Función para encontrar una ARISTA, el cual nos devuelve el VERTICE INCIAL
    Vertice<T> * encontrarArista(T inicio, T final){
        Vertice<T> * encontradoInicio = this->encontrarVertice(inicio); // Buscamos si existe el VERTICE origen
        if (encontradoInicio){
            Vertice<T> * encontradoFinal = this->encontrarVertice(final); // Buscamos si existe el VERTICE final/extremo
            if (encontradoFinal){
                for (auto it = encontradoInicio->aristas.begin(); it != encontradoInicio->aristas.end(); it++){ // Recorremos las ARISTAS del VERTICE INICIAL
                    // SI existe la arista con el VERTICE FINAL/EXTREMO, devolvemos el VERTICE INICIAL
                    if ((*it)->extremo->valor == final)
                        return encontradoInicio;
                }
                return NULL;
            }else{
                return NULL; // SI NO EXISTE EL VERTICE EXTREMO/FINAL
            }
        }else{
            return NULL; // SI NO EXISTE EL VERTICE ORIGEN
        }
    }

    void mostrarNodos(){
        for (auto& vertice: this->vertices){
            cout << vertice.first << ", ";
        }

        cout << endl;
    }

    void mostrarListaDeAdyacencia(){
        cout << endl;
        cout << "-- MATRIZ DE ADYACENCIA DE " << this->nombreArchivo << endl;
        for (auto& vertice: this->vertices){
            cout << vertice.first << " = ";
            for (auto& aristas: vertice.second->aristas){
                cout << aristas->extremo->valor << ", ";
            }
            cout << endl;
        }
        cout << endl;
    }

    unsigned int obtenerCantidadVertices(){
        return this->cantidadVertices;
    }

    unsigned int obtenerCantidadAristas(){
        return this->cantidadAristas;
    }

    void crearArchivoDot(){
        ofstream salida;
        salida.open(this->nombreArchivo + ".dot", ios::out);
        if (salida.is_open()){
            cout << "------------ CREANDO ARCHIVO DOT ------------\n";
            salida << "digraph ";
            salida << this->nombreArchivo << " {\n";
            if (!this->dirigido) // graficara con flechas
                salida << "edge [dir=none];\n";

            for (auto& vertice: this->vertices){
                string color = ", style=filled, fillcolor=";
                switch (vertice.second->valorColor) {
                case amarillo:
                    color += "yellow";
                    break;
                case verde:
                    color += "green";
                    break;
                case rojo:
                    color += "red";
                    break;
                case morado:
                    color += "purple";
                    break;
                case azul:
                    color += "blue";
                    break;
                case turquoise3:
                    color += "turquoise3";
                    break;
                case firebrick:
                    color += "firebrick";
                    break;
                case goldenrod3:
                    color += "goldenrod3";
                    break;
                case aquamarine2:
                    color += "aquamarine2";
                    break;
                case darkolivegreen3:
                    color += "darkolivegreen3";
                    break;
                case mistyrose2:
                    color += "mistyrose2";
                    break;
                case chocolate:
                    color += "chocolate";
                    break;
                default:
                    color = "";
                }
                //salida << "\"" << vertice.second << "\"" << " [fixedsize=true label=\"" << vertice.first << "\"" << color << "]" << ";\n";
                salida << "\"" << vertice.second << "\"" << " [label=\"" << vertice.first << "\"" << color << "]" << ";\n";
            }

            if (!this->dirigido){
                vector<T> valoresNodos;
                for (auto& vertice: this->vertices){
                    for (auto& arista: vertice.second->aristas){
                        bool aristaYaDibujada = false;
                        for (int idx = 0; idx < valoresNodos.size(); idx++){
                            if (arista->extremo->valor == valoresNodos[idx]){
                                aristaYaDibujada = true;
                                break;
                            }
                        }
                        if (!aristaYaDibujada){
                            salida << "\"" << vertice.second << "\"" << " -> " << "\"" << arista->extremo << "\"";
                            if (this->ponderado){
                                salida << " [ label = \"" << arista->peso << "\" ]";
                            }
                            salida << ";\n";
                            valoresNodos.push_back(vertice.first);
                        }
                    }
                }
            }else{
                for (auto& vertice: this->vertices){
                    for (auto& arista: vertice.second->aristas){
                        salida << "\"" << vertice.second << "\"" << " -> " << "\"" << arista->extremo << "\"";
                        if (this->ponderado){
                            salida << " [ label = \"" << arista->peso << "\" ]";
                        }
                        salida << ";\n";
                    }
                }
            }

            salida << "}\n";
            salida.close();
            string comando = "dot " + this->nombreArchivo + ".dot -o " + this->nombreArchivo + ".pdf -Tpdf";
            system(comando.c_str());
        }else{
            cout << endl << "No se pudo crear archivo" << endl;
        }
    }

    // Función para insertar un VERTICE de tipo T(int, string, char) y nos devolvera la dirección de memoria de dicho VERTICE
    Vertice<T> * insertarVertice(T valor){
        if (this->encontrarVertice(valor)){ // En el caso de que ya exista el VERTICE
            return this->encontrarVertice(valor); // devolvera su dirección de memoria
        }
        // SI NO EXISTE, crearemos el vertice y lo insertaremos en el grafo
        Vertice<T> * nuevoVertice = new Vertice<T>(valor);
        this->vertices[valor] = nuevoVertice;
        this->cantidadVertices++;
        this->valoresVertices.push_back(valor);

        return nuevoVertice;
    }

    // FUNCIÓN PARA INSERTAR UNA ARISTA, PIDIENDO EL VERTICE ORIGEN Y VERTICE DESTINO
    bool insertarArista(T inicio, T fin, float peso = 0){
        if (!this->permitirLazos && (inicio == fin)){ // Control para ver si se pueden aceptar LAZOS (arista con mismo VERTICES origen y final)
            return false;
        }

        Vertice<T> * inicioEncontrado = this->encontrarVertice(inicio); // Buscamos el vertice origen
        Vertice<T> * finEncontrado = this->encontrarVertice(fin);   // Buscamos el vertice destino/final/extremo

        if (inicioEncontrado){      // |    VEMOS SI EXISTEN LOS VERTICES
            if (finEncontrado){     // |
                if (this->encontrarArista(inicio, fin)){ // Comprobamos si ya existe una arista entre estos dos vertices
                    if (this->multigrafo){ // En el caso de ser un MULTIGRAFO, volvemos a insertar una arista más
                        inicioEncontrado->aristas.push_back(new Arista<T>(finEncontrado, peso));
                        (*inicioEncontrado)++;
                        ++(*finEncontrado);
                        if (!this->dirigido){
                            finEncontrado->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                            (*finEncontrado)++;
                            ++(*inicioEncontrado);
                        }
                        this->cantidadAristas++;
                        return true;
                    }
                    // si no es multigrafo, devolvemos FALSE, porque no insertamos arista
                    return false;
                }else{ // Si la arista a insertar no existe
                    // Insertamos la nueva arista en el nodo origen
                    inicioEncontrado->aristas.push_back(new Arista<T>(finEncontrado, peso));
                    (*inicioEncontrado)++;
                    ++(*finEncontrado);
                    if (!this->dirigido){ // y si no es dirigido, tenemos que insertar la arista en el sentido opuesto
                        finEncontrado->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                        (*finEncontrado)++;
                        ++(*inicioEncontrado);
                    }
                    this->cantidadAristas++;
                    return true;
                }
            }else{ // si no se encuentra el nodo final
                if (this->autoinsertar){
                    Vertice<T> * verticeFinal = this->insertarVertice(fin);
                    Arista<T> * nuevaArista = new Arista<T>(verticeFinal, peso);
                    inicioEncontrado->aristas.push_back(nuevaArista);
                    (*inicioEncontrado)++;
                    ++(*verticeFinal);
                    if (!this->dirigido){
                        verticeFinal->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                        (*verticeFinal)++;
                        ++(*inicioEncontrado);
                    }
                    this->cantidadAristas++;
                    return true;
                }
                return false;
            }
        }else{ // En el caso que no exista en nodo inicial/origen
            if (this->autoinsertar){
                Vertice<T> * nuevoInicio = this->insertarVertice(inicio);
                Vertice<T> * nuevoFin = this->insertarVertice(fin);
                nuevoInicio->aristas.push_back(new Arista<T>(nuevoFin, peso));
                (*nuevoInicio)++;
                ++(*nuevoFin);
                if (!this->dirigido){
                    nuevoFin->aristas.push_back(new Arista<T>(nuevoInicio, peso));
                    (*nuevoFin)++;
                    ++(*nuevoInicio);
                }
                this->cantidadAristas++;
                return true;
            }
        }
        return false;
    }

    unsigned int obtenerGradoPositivoVertice(T valor){
        return this->encontrarVertice(valor)->gradoPositivo;
    }

    unsigned int obtenerGradoNegativoVertice(T valor){
        return this->encontrarVertice(valor)->gradoNegativo;
    }

    bool esDirigido(){
        return this->dirigido;
    }

    bool esMultigrafo(){
        return this->multigrafo;
    }

    bool esPonderado(){
        return this->ponderado;
    }

    void cambiarNombre(string nuevoNombre){
        this->nombreArchivo = nuevoNombre;
    }

    friend T operator << (Grafo<T> & grafo,const T p){
        grafo.insertarVertice(p);
        return p;
    }

    // Sobrecarga del operador de asignación
    Grafo<T> & operator = (const Grafo & otro){
        this->dirigido = otro.dirigido;
        this->multigrafo = otro.multigrafo;
        this->ponderado = otro.ponderado;
        this->cantidadAristas = otro.cantidadAristas;
        this->cantidadVertices = otro.cantidadVertices;
        this->permitirLazos = otro.permitirLazos;
        this->autoinsertar = otro.autoinsertar;
        this->ponderado = otro.ponderado;
        this->valoresVertices = otro.valoresVertices;
        this->nombreArchivo = otro.nombreArchivo + "_copia";

        for (auto & vertice: otro.vertices){
            for (auto & arista: vertice.second->aristas){
                this->insertarArista(vertice.second->valor, arista->extremo->valor, arista->peso);
            }
        }

        return *this;
    }

    void vaciarGrafo(){
        vector<int> i;
        this->vertices.clear();
        this->cantidadAristas = 0;
        this->cantidadVertices = 0;
        this->valoresVertices.clear();
    }

    void exportarAtributosA(Grafo<T> & tmp){
        tmp.dirigido = this->dirigido;
        tmp.multigrafo = this->multigrafo;
        tmp.ponderado = this->ponderado;
        tmp.permitirLazos = this->permitirLazos;
        tmp.autoinsertar = this->autoinsertar;
        tmp.nombreArchivo = this->nombreArchivo + "_copia";
    }

    void mostrarPropiedades(){
        cout << endl;
        cout << ">>>>> PROPIEDADES <<<<<" << endl;
        cout << "Nombre: " << this->nombreArchivo << endl;
        cout << "Dirigido: " << this->dirigido << endl;
        cout << "Multigrafo: " << this->multigrafo << endl;
        cout << "Ponderado: " << this->ponderado << endl;
        cout << "Permitir Lazos: " << this->permitirLazos << endl;
        cout << "Permitir autoinsertar: " << this->autoinsertar << endl;
        cout << "<<<<<<<<<>>>>>>>>" << endl;
    }

    void guardarEnArchivo(){
        ofstream salida;
        salida.open(this->nombreArchivo + ".gph", ios::out);
        salida << this->dirigido << endl;
        salida << this->multigrafo << endl;
        salida << this->ponderado << endl;
        salida << this->permitirLazos << endl;
        salida << this->autoinsertar << endl;
        salida << "-\n";

        for (auto & vertice: this->vertices){
            salida << vertice.first << endl;
            for (auto & arista: vertice.second->aristas){
                salida << arista->extremo->valor << endl;
                salida << arista->peso << endl;
            }
            salida << "-" << endl;
        }

        salida.flush();
        salida.close();
    }

    void leerDesdeArchivo(string nombreArchivo){
        ifstream entrada;
        entrada.open(nombreArchivo, ios::in);
        char buffer[100];
        // Si es dirigido
        entrada.getline(buffer,100);
        this->dirigido = atoi(buffer);
        // si es multigrafo
        entrada.getline(buffer,100);
        this->multigrafo = atoi(buffer);
        // si es ponderado
        entrada.getline(buffer,100);
        this->ponderado = atoi(buffer);
        // permite lazos
        entrada.getline(buffer,100);
        this->permitirLazos = atoi(buffer);
        // Si permite autoinsertar
        entrada.getline(buffer,100);
        this->autoinsertar = atoi(buffer);
        // TERMINAMOS DE LEER LA CABECERA DEL ARCHIVO
        T valorVertice;
        while (!entrada.eof()) {
            entrada.getline(buffer, 100);
            if (strcmp(buffer, "-") == 0){
                entrada.getline(buffer, 100);
                valorVertice = atoi(buffer);
            }else{
                T valorVerticeFinal = atoi(buffer);
                entrada.getline(buffer, 100);
                float peso = atof(buffer);
                this->insertarArista(valorVertice, valorVerticeFinal, peso);
            }
        }
        // cerrando archivo
        entrada.close();
    }

    // IMPLEMENTACIÓN DEL ALGORIMO VORAZ
    void colorearGrafoVoraz(){
        vector<T> verticesOrdenados = {1,2,3,4,5,6,7};
        vector<Color> coloresOrdenados = {verde, rojo, amarillo};

        // Coloreando el primer vertice
        this->vertices[verticesOrdenados.at(0)]->valorColor = verde;
        cout << "VERTICE : " << this->vertices[verticesOrdenados.at(0)]->valor << " = " << this->vertices[verticesOrdenados.at(0)]->valorColor;
        cout << endl << endl;
        for (int idx = 1; idx < verticesOrdenados.size(); idx++){
            Vertice<T> * nodoElegido = this->vertices[verticesOrdenados.at(idx)];
            vector<Color> coloresDisponibles; // vamos a agrupar los colores disponibles
            for (int idx_c = 0; idx_c < coloresOrdenados.size(); idx_c++){
                // Vamos a recorrer los vertices adyacentes
                bool existe = false;
                for (auto & arista: nodoElegido->aristas){ // peso, Vertice<T> *
                    if (arista->extremo->valorColor == coloresOrdenados.at(idx_c)){
                        existe = true;
                        break;
                    }
                }
                if (!existe){
                    coloresDisponibles.push_back(coloresOrdenados.at(idx_c));
                }
            }
            if (coloresDisponibles.size() > 0){
                nodoElegido->valorColor = coloresDisponibles.at(0);
            }else{
                cout << "NOS FALTAN COLORES";
                return;
            }
        }

        // mostrando los colores pintados
        for (auto & vertice: this->vertices){
            cout << "El color del vertice " << vertice.first << " = " << vertice.second->valorColor << endl;
        }
    }

    void colorearGrafoWP(){
        vector<Vertice<T> *> verticesOrdenados;
        for (auto & vertice: this->vertices){
            verticesOrdenados.push_back(vertice.second); // Vertice<T> *
        }
        // Función para ordenar los vetices en base a su grado          | Función Lambda / Función Anonima
        sort(verticesOrdenados.begin(), verticesOrdenados.end(), [] (Vertice<T> * a, Vertice<T> * b){
            return a->aristas.size() > b->aristas.size();
        });
        vector<Color> coloresOrdenados = {verde, rojo, amarillo};

        // Coloreando el primer vertice
        this->vertices[verticesOrdenados.at(0)->valor]->valorColor = coloresOrdenados.at(0);
        cout << "VERTICE : " << this->vertices[verticesOrdenados.at(0)->valor]->valor << " = " << this->vertices[verticesOrdenados.at(0)->valor]->valorColor;
        cout << endl << endl;
        for (int idx = 1; idx < verticesOrdenados.size(); idx++){
            Vertice<T> * nodoElegido = this->vertices[verticesOrdenados.at(idx)->valor];
            vector<Color> coloresDisponibles; // vamos a agrupar los colores disponibles

            for (int idx_c = 0; idx_c < coloresOrdenados.size(); idx_c++){
                // Vamos a recorrer los vertices adyacentes
                bool existe = false;
                for (Arista<T> * & arista: nodoElegido->aristas){ // peso, Vertice<T> *
                    if (arista->extremo->valorColor == coloresOrdenados.at(idx_c)){
                        existe = true;
                        break;
                    }
                }
                if (!existe){
                    coloresDisponibles.push_back(coloresOrdenados.at(idx_c));
                }
            }

            if (coloresDisponibles.size() > 0){
                nodoElegido->valorColor = coloresDisponibles.at(0);
            }else{
                cout << "NOS FALTAN COLORES";
                return;
            }
        }

        // mostrando los colores pintados
        for (auto & vertice: this->vertices){
            cout << "El color del vertice " << vertice.first << " = " << vertice.second->valorColor << endl;
        }
    }

    void colorearHorario(vector<int> paleta){
        vector<Vertice<T> *> verticesOrdenados; // Creamos un vector de vertices el cuales ordenaremos segun su grado
        for (auto & vertice: this->vertices){
            verticesOrdenados.push_back(vertice.second); // Vertice<T> * | insertamos todos los vertices del grafo (aún desordenados)
        }
        // Función para ordenar los vetices en base a su grado          | Función Lambda / Función Anonima
        sort(verticesOrdenados.begin(), verticesOrdenados.end(), [] (Vertice<T> * a, Vertice<T> * b){
            return a->aristas.size() > b->aristas.size();   // en base a la cantidad de aristas que tengan(grado)
        });

        // Coloreando el primer vertice que esta en el vector de VERTICES ORDENADOS
        this->vertices[verticesOrdenados.at(0)->valor]->valorColor = paleta.at(0);

        // Para cada vertices en el vector de vertices ordenados, excepto el primero
        for (int idx = 1; idx < verticesOrdenados.size(); idx++){
            // Seleccionamos el siguiente vertice a colorear
            Vertice<T> * verticeElegido = this->vertices[verticesOrdenados.at(idx)->valor];
            vector<int> coloresDisponibles; // vamos a agrupar los colores disponibles, los que no son adyacentes al vertices escogido

            for (int idx_c = 0; idx_c < paleta.size(); idx_c++){
                // Vamos a recorrer los vertices adyacentes
                bool existe = false;
                for (Arista<T> * & arista: verticeElegido->aristas){ // peso, Vertice<T> *
                    if (arista->extremo->valorColor == paleta.at(idx_c)){
                        existe = true;
                        break;
                    }
                }
                if (!existe){
                    coloresDisponibles.push_back(paleta.at(idx_c));
                }
            }

            if (coloresDisponibles.size() > 0){
                verticeElegido->valorColor = coloresDisponibles.at(0);
            }else{
                cout << "NOS FALTAN COLORES";
                return;
            }
        }

        // mostrando los colores pintados
        for (auto & vertice: this->vertices){
            cout << "El color del vertice " << vertice.first << " = " << vertice.second->valorColor << endl;
        }
    }

    void colorearGrafoMMI(){
        vector<T> verticesOrdenados = {7,5,5,4,3,2,6,1};
        vector<Color> coloresOrdenados = {verde, rojo, amarillo, morado};

        // Coloreando el primer vertice
        this->vertices[verticesOrdenados.at(0)]->valorColor = verde;
        cout << "VERTICE : " << this->vertices[verticesOrdenados.at(0)]->valor << " = " << this->vertices[verticesOrdenados.at(0)]->valorColor;
        cout << endl << endl;
        for (int idx = 1; idx < verticesOrdenados.size(); idx++){
            Vertice<T> * nodoElegido = this->vertices[verticesOrdenados.at(idx)];
            vector<Color> coloresDisponibles; // vamos a agrupar los colores disponibles
            for (int idx_c = 0; idx_c < coloresOrdenados.size(); idx_c++){
                // Vamos a recorrer los vertices adyacentes
                bool existe = false;
                for (auto & arista: nodoElegido->aristas){ // peso, Vertice<T> *
                    if (arista->extremo->valorColor == coloresOrdenados.at(idx_c)){
                        existe = true;
                        break;
                    }
                }
                if (!existe){
                    coloresDisponibles.push_back(coloresOrdenados.at(idx_c));
                }
            }
            if (coloresDisponibles.size() > 0){
                nodoElegido->valorColor = coloresDisponibles.at(0);
            }else{
                cout << "NOS FALTAN COLORES";
                return;
            }
        }

        // mostrando los colores pintados
        for (auto & vertice: this->vertices){
            cout << "El color del vertice " << vertice.first << " = " << vertice.second->valorColor << endl;
        }
    }
};


#endif // GRAFO_H
