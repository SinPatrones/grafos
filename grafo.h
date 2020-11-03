#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <typename T>
class Arista;

// CLASE VERTICE
template <typename T>
class Vertice{
public:
    T valor;
    vector<Arista<T> *> aristas;

    Vertice(T valor){
        this->valor = valor;
    }
};


// CLASE ARISTA
template <typename T>
class Arista{
public:
    Vertice<T> * extremo;
    float peso;

    Arista(Vertice<T> * arista, float nuevoPeso){
        this->extremo = arista;
        this->peso = nuevoPeso;
    }

    Arista(Vertice<T> * arista){
        this->extremo = arista;
        this->peso = 0;
    }
};


// CLASE GRAFO
template <typename T>
class Grafo{
private:
    vector<Vertice<T> *> vertices;
    unsigned int cantidadVertices;
    unsigned int cantidadAristas;
    bool dirigido;
    bool multigrafo;
    bool permitirLazos;
    bool autoinsertar;
    vector<T> valoresVertices;
public:
    Grafo(bool autoinsertar = false, bool permitirLazos = false, bool dirigido = false, bool multigrafo = false){
        this->cantidadVertices = 0;
        this->cantidadAristas = 0;
        this->dirigido = dirigido;
        this->multigrafo = multigrafo;
        this->permitirLazos = permitirLazos;
        this->autoinsertar = autoinsertar;
    }

    Vertice<T> * encontrarVertice(T valor){
        for(auto it = this->vertices.begin(); it != this->vertices.end(); it++){
            if ((*it)->valor == valor){
                return *it;
            }
        }
        return NULL;
    }

    Vertice<T> * encontrarArista(T inicio, T final){
        Vertice<T> * encontradoInicio = this->encontrarVertice(inicio);
        if (encontradoInicio){
            Vertice<T> * encontradoFinal = this->encontrarVertice(final);
            if (encontradoFinal){
                for (auto it = encontradoInicio->aristas.begin(); it != encontradoInicio->aristas.end(); it++){
                    if ((*it)->extremo->valor == final)
                        return encontradoInicio;
                }
                return NULL;
            }else{
                return NULL;
            }
        }else{
            return NULL;
        }
    }

    void mostrarNodos(){
        for (auto it = this->vertices.begin(); it != this->vertices.end(); it++){
            cout << (*it)->valor << ", ";
        }
        cout << endl;
    }

    void mostrarListaDeAdyacencia(){
        for (auto itVertices = this->vertices.begin(); itVertices != this->vertices.end(); itVertices++){
            cout << (*itVertices)->valor << "= ";
            for (auto itAristas = (*itVertices)->aristas.begin(); itAristas != (*itVertices)->aristas.end(); itAristas++){
                cout << (*itAristas)->extremo->valor << ", ";
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
        salida.open("migrafo.dot", ios::out);
        if (salida.is_open()){
            cout << "------------ CREANDO ARCHIVO DOT ------------\n";
            salida << "digraph regexp {\n";
            if (!this->dirigido) // graficara con flechas
                salida << "edge [dir=none];\n";
            for (auto it = this->vertices.begin(); it != this->vertices.end(); it++){
                salida << "\"" << (*it) << "\"" << " [fixedsize=true label=\"" << (*it)->valor << "\"]" << ";\n";
            }

            if (!this->dirigido){
                vector<T> valoresNodos;
                for (auto itVertices = this->vertices.begin(); itVertices != this->vertices.end(); itVertices++){
                    for (auto itAristas = (*itVertices)->aristas.begin(); itAristas != (*itVertices)->aristas.end(); itAristas++){
                        bool aristaYaDibujada = false;
                        for (int idx = 0; idx < valoresNodos.size(); idx++){
                            if ((*itAristas)->extremo->valor == valoresNodos[idx]){
                                aristaYaDibujada = true;
                                break;
                            }
                        }
                        if (!aristaYaDibujada){
                            salida << "\"" << (*itVertices) << "\"" << " -> " << "\"" << (*itAristas)->extremo << "\"" << ";\n";
                            valoresNodos.push_back((*itVertices)->valor);
                        }
                    }
                }
            }else{
                for (auto itVertices = this->vertices.begin(); itVertices != this->vertices.end(); itVertices++){
                    for (auto itAristas = (*itVertices)->aristas.begin(); itAristas != (*itVertices)->aristas.end(); itAristas++){
                        salida << "\"" << (*itVertices) << "\"" << " -> " << "\"" << (*itAristas)->extremo << "\"" << ";\n";
                    }
                }
            }

            salida << "}\n";
            salida.close();
            cout << "------------ FINALIZADA LA CREACION DEL ARCHIVO DOT ------------\n";
            cout << "------------ CREANDO ARCHIVO IMAGEN ------------\n";
            system("dot migrafo.dot -o migrafo.pdf -Tpdf");
            cout << "------------ ARCHIVO IMAGEN CREADA ------------\n";
        }else{
            cout << endl << "No se pudo crear archivo" << endl;
        }
    }

    Vertice<T> * insertarNodo(T valor){
        if (this->encontrarVertice(valor)){
            return NULL;
        }
        Vertice<T> * nuevoVertice = new Vertice<T>(valor);
        this->vertices.push_back(nuevoVertice);
        this->cantidadVertices++;
        this->valoresVertices.push_back(valor);

        return nuevoVertice;
    }

    bool insertarArista(T inicio, T fin, float peso = 0){
        Vertice<T> * inicioEncontrado = this->encontrarVertice(inicio);
        Vertice<T> * finEncontrado = this->encontrarVertice(fin);
        if (!this->permitirLazos && (inicio == fin)){
            return false;
        }

        if (inicioEncontrado){
            if (finEncontrado){
                if (this->encontrarArista(inicio, fin)){
                    if (this->multigrafo){
                        inicioEncontrado->aristas.push_back(new Arista<T>(finEncontrado, peso));
                        if (!this->dirigido){
                            finEncontrado->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                        }
                        this->cantidadAristas++;
                        return true;
                    }
                    return false;
                }else{
                    inicioEncontrado->aristas.push_back(new Arista<T>(finEncontrado, peso));
                    if (!this->dirigido){
                        finEncontrado->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                    }
                    this->cantidadAristas++;
                    return true;
                }
            }else{ // si no se encuentra el nodo final
                if (this->autoinsertar){
                    Vertice<T> * verticeFinal = this->insertarNodo(fin);
                    Arista<T> * nuevaArista = new Arista<T>(verticeFinal);
                    inicioEncontrado->aristas.push_back(nuevaArista);
                    if (!this->dirigido){
                        verticeFinal->aristas.push_back(new Arista<T>(inicioEncontrado, peso));
                    }
                    this->cantidadAristas++;
                    return true;
                }
                return false;
            }
        }else{
            if (this->autoinsertar){
                Vertice<T> * nuevoInicio = this->insertarNodo(inicio);
                Vertice<T> * nuevoFin = this->insertarNodo(fin);
                nuevoInicio->aristas.push_back(new Arista<T>(nuevoFin, peso));
                if (!this->dirigido){
                    nuevoFin->aristas.push_back(new Arista<T>(nuevoInicio, peso));
                }
                this->cantidadAristas++;
                return true;
            }
        }
        return false;
    }

    void crearVerticesAleatorios(unsigned int cantidadVertices = 10){
        srand(time(NULL));
        while(this->cantidadVertices < cantidadVertices){
            unsigned int valorArista = 1 + rand() % (999 - 0);
            this->insertarNodo(valorArista);
        }
    }

    void crearGrafoCompleto(unsigned int cantidadVertices = 0){
        // n (n-1)/2
        if (cantidadVertices != 0){
            this->crearVerticesAleatorios(cantidadVertices);
        }
        for (auto itVertices = this->vertices.begin(); itVertices != this->vertices.end(); itVertices++){
            for (auto itExtremo = this->vertices.begin(); itExtremo != this->vertices.end(); itExtremo++){
                if (itVertices != itExtremo){
                    this->insertarArista((*itVertices)->valor, (*itExtremo)->valor);
                }
            }
        }
    }

    void crearAristasAleatorias(unsigned int cantidadAristas){
        srand(time(NULL));
        while(this->obtenerCantidadAristas() < cantidadAristas){
            int posInicio = rand() % (this->vertices.size());
            int posFinal = rand() % (this->vertices.size());
            this->insertarArista(this->valoresVertices[posInicio], this->valoresVertices[posFinal]);
        }
    }

    bool esDirigido(){
        return this->dirigido;
    }

    bool esMultigrafo(){
        return this->multigrafo;
    }
};

#endif // GRAFO_H
