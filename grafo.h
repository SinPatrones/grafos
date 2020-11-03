#ifndef GRAFO_H
#define GRAFO_H
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <map>

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
    //vector<Vertice<T> *> vertices;
    map<T, Vertice<T> *> vertices;
    unsigned int cantidadVertices;
    unsigned int cantidadAristas;
    bool dirigido;
    bool multigrafo;
    bool permitirLazos;
    bool autoinsertar;
    bool ponderado;
    vector<T> valoresVertices;
public:
    Grafo(bool autoinsertar = false, bool permitirLazos = false, bool dirigido = false, bool ponderado = false, bool multigrafo = false){
        this->cantidadVertices = 0;
        this->cantidadAristas = 0;
        this->dirigido = dirigido;
        this->multigrafo = multigrafo;
        this->permitirLazos = permitirLazos;
        this->autoinsertar = autoinsertar;
        this->ponderado = ponderado;
    }

    Vertice<T> * encontrarVertice(T valor){
        auto itEncontrado = this->vertices.find(valor);
        if (itEncontrado == this->vertices.end())
            return NULL;
        return itEncontrado->second;
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
        for (auto& vertice: this->vertices){
            cout << vertice.first << ", ";
        }
        cout << endl;
    }

    void mostrarListaDeAdyacencia(){
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
        salida.open("migrafo.dot", ios::out);
        if (salida.is_open()){
            cout << "------------ CREANDO ARCHIVO DOT ------------\n";
            salida << "digraph regexp {\n";
            if (!this->dirigido) // graficara con flechas
                salida << "edge [dir=none];\n";
            for (auto& vertice: this->vertices){
                salida << "\"" << vertice.second << "\"" << " [fixedsize=true label=\"" << vertice.first << "\"]" << ";\n";
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
        this->vertices[valor] = nuevoVertice;
        this->cantidadVertices++;
        this->valoresVertices.push_back(valor);

        return nuevoVertice;
    }

    bool insertarArista(T inicio, T fin, float peso = 0){
        if (!this->permitirLazos && (inicio == fin)){
            return false;
        }

        Vertice<T> * inicioEncontrado = this->encontrarVertice(inicio);
        Vertice<T> * finEncontrado = this->encontrarVertice(fin);

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
        if (cantidadVertices != 0){
            this->crearVerticesAleatorios(cantidadVertices);
        }
        srand(time(NULL));
        for (auto& vertice: this->vertices){
            for (auto& verticeExtremo: this->vertices){
                if (vertice.first != verticeExtremo.first){
                    if (this->ponderado){
                        float peso = 1 + rand() % (100);
                        this->insertarArista(vertice.first, verticeExtremo.first, peso);
                    }else{
                        this->insertarArista(vertice.first, verticeExtremo.first);
                    }
                }
            }
        }
    }

    void crearAristasAleatorias(unsigned int cantidadAristas){
        if (cantidadAristas ==  ((cantidadAristas * (cantidadAristas - 1)) / 2)){
            this->crearGrafoCompleto();
        }else{
            if (this->vertices.size() > 0){
                if (this->ponderado){
                    srand(time(NULL));
                    while(this->obtenerCantidadAristas() < cantidadAristas){
                        int posInicio = rand() % (this->vertices.size());
                        int posFinal = rand() % (this->vertices.size());
                        float peso = 1 + rand() % (100);
                        this->insertarArista(this->valoresVertices[posInicio], this->valoresVertices[posFinal], peso);
                    }
                }else{
                    srand(time(NULL));
                    while(this->obtenerCantidadAristas() < cantidadAristas){
                        int posInicio = rand() % (this->vertices.size());
                        int posFinal = rand() % (this->vertices.size());
                        this->insertarArista(this->valoresVertices[posInicio], this->valoresVertices[posFinal]);
                    }
                }
            }
        }
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
};

#endif // GRAFO_H
