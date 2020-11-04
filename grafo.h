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

using namespace std;

template <typename T>
class Arista;

template <typename T>
class Grafo;

// CLASE VERTICE
template <typename T>
class Vertice{
private:
    T valor;
    unsigned int gradoPositivo;
    unsigned int gradoNegativo;
    vector<Arista<T> *> aristas;

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

    Vertice<T> * operator ++( int ){
        this->gradoPositivo++;
        return this;
    }

    Vertice<T> * operator ++(){
        this->gradoNegativo++;
        return this;
    }

    friend class Grafo<T>;
};


// CLASE ARISTA
template <typename T>
class Arista{
private:
    Vertice<T> * extremo;
    float peso;

public:
    Arista(Vertice<T> * arista, float nuevoPeso){
        this->extremo = arista;
        this->peso = nuevoPeso;
    }

    Arista(Vertice<T> * arista){
        this->extremo = arista;
        this->peso = 0;
    }

    Vertice<T> * obtenerExtremo(){
        return this->extremo;
    }

    float obtenerPeso(){
        return this->peso;
    }
    friend class Grafo<T>;
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
    string nombreArchivo;
    vector<T> valoresVertices;
public:
    Grafo(string nombreArchivo = "tmp", bool autoinsertar = false, bool permitirLazos = false, bool dirigido = false, bool ponderado = false, bool multigrafo = false){
        this->cantidadVertices = 0;
        this->cantidadAristas = 0;
        this->dirigido = dirigido;
        this->multigrafo = multigrafo;
        this->permitirLazos = permitirLazos;
        this->autoinsertar = autoinsertar;
        this->ponderado = ponderado;
        this->nombreArchivo = nombreArchivo;
    }

    Grafo(const Grafo & original){
        (*this) = original;
    }

    Vertice<T> * encontrarVertice(T valor){
        cout << "-- Buscando " << valor << endl;
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
        salida.open(this->nombreArchivo + ".dot", ios::out);
        if (salida.is_open()){
            cout << "------------ CREANDO ARCHIVO DOT ------------\n";
            salida << "digraph ";
            salida << this->nombreArchivo << " {\n";
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
            string comando = "dot " + this->nombreArchivo + ".dot -o " + this->nombreArchivo + ".pdf -Tpdf";
            cout << "GENERANDO: " << comando;
            system(comando.c_str());
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
                    return false;
                }else{ // Si la arista a insertar no existe
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
            }else{ // si no se encuentra el nodo final
                if (this->autoinsertar){
                    Vertice<T> * verticeFinal = this->insertarNodo(fin);
                    Arista<T> * nuevaArista = new Arista<T>(verticeFinal);
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
        }else{
            if (this->autoinsertar){
                Vertice<T> * nuevoInicio = this->insertarNodo(inicio);
                Vertice<T> * nuevoFin = this->insertarNodo(fin);
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

    friend T operator << (Grafo<T> & grafo,const T p){
        grafo.insertarNodo(p);
        return p;
    }

    friend ostream& operator << (ostream &o,const Grafo<T> &grafo){
        o << endl;
        for (auto& vertice: grafo.vertices){
            o << vertice.first << " = ";
            for (auto& aristas: vertice.second->obtenerAristas()){
                o << aristas->obtenerExtremo()->obtenerValor() << ", ";
            }
            o << endl;
        }
        o << endl;

        return o;
    }

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
        this->nombreArchivo = this->nombreArchivo + "_copia";

        for (auto & vertice: otro.vertices){
            for (auto & arista: vertice.second->aristas){
                this->insertarArista(vertice.second->valor, arista->extremo->valor, arista->peso);
            }
        }

        return *this;
    }

    bool existeCiclo(T valorVerticeInicio, T valorVerticeFinal){
        Vertice<T> * verticeFinal = this->encontrarVertice(valorVerticeFinal);

        queue<Arista<T> *> aristasPorVisitar;
        for(auto & arista: verticeFinal->aristas){
            if (arista->extremo->valor != valorVerticeInicio){
                aristasPorVisitar.push(arista);
            }
        }

        map<T, Vertice<T> *> verticesVisitados;
        verticesVisitados[valorVerticeFinal] = verticeFinal;

        while(!aristasPorVisitar.empty()){
            Arista<T> * aristaAux = aristasPorVisitar.front();
            aristasPorVisitar.pop();

            if (aristaAux->extremo->valor == valorVerticeInicio)
                return true;

            for(auto & aristaPendiente: aristaAux->extremo->aristas){
                if (verticesVisitados[aristaPendiente->extremo->valor] == NULL){
                    aristasPorVisitar.push(aristaPendiente);
                }
            }
        }
        return false;
    }

    Grafo<T> generarArbolMinimoPorProfundida(T valorVerticeInicial){
        Grafo<T> arbolExpansionMinima(this->nombreArchivo + "_adexm", true);
        stack<Vertice<T> *> padres;

        Vertice<T> * verticeInicial = this->encontrarVertice(valorVerticeInicial);
        if (!verticeInicial){
            return arbolExpansionMinima;
        }
        arbolExpansionMinima.insertarNodo(valorVerticeInicial);
        padres.push(verticeInicial);
        while(!padres.empty()){
            verticeInicial = padres.top();
            padres.pop();
            list<Arista<T> *> aristas;
            for(auto & arista: verticeInicial->aristas){
                if (arbolExpansionMinima.vertices.find(arista->extremo->valor) == arbolExpansionMinima.vertices.end()){
                    aristas.push_back(arista);
                }
            }
            while(!aristas.empty()){
                Arista<T> * candidato = aristas.front();
                aristas.pop_front();
                if (arbolExpansionMinima.vertices.find(candidato->extremo->valor) == arbolExpansionMinima.vertices.end()){
                    arbolExpansionMinima.insertarArista(verticeInicial->valor, candidato->extremo->valor);
                    padres.push(verticeInicial);
                    verticeInicial = candidato->extremo;
                    aristas.clear();
                    arbolExpansionMinima.mostrarListaDeAdyacencia();
                    for(auto & arista: verticeInicial->aristas){
                        if (arbolExpansionMinima.vertices.find(arista->extremo->valor) == arbolExpansionMinima.vertices.end()){
                            aristas.push_back(arista);
                        }
                    }
                }
            }
        }

        return arbolExpansionMinima;
    }

};

template <typename G, typename V1>
void insertarCaminoEn(G & grafo, const V1 & unico){
    grafo.insertarNodo(unico);
}

template <typename G, typename V1, typename V2>
void insertarCaminoEn(G & grafo, const V1 & primero, const V2 & segundo){
    grafo.insertarArista(primero, segundo);
}

template <typename G, typename V1, typename V2, typename V3, typename ... V>
void insertarCaminoEn(G & grafo, const V1 & primero, const V2 & segundo, const V3 & tercero, const V &... restoValores){
    grafo.insertarArista(primero, segundo);
    insertarCaminoEn(grafo, segundo, tercero, restoValores...);
}


#endif // GRAFO_H
