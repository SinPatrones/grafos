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
    Arista(Vertice<T> * vertice, float nuevoPeso){
        this->extremo = vertice;
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

bool compararAristas(pair<Vertice<int> *, Arista<int> *> & a, pair<Vertice<int> *, Arista<int> *> & b){
    return a.second->obtenerPeso() < b.second->obtenerPeso();
}

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
            system(comando.c_str());
            cout << "------------ ARCHIVO IMAGEN CREADA ------------\n";
        }else{
            cout << endl << "No se pudo crear archivo" << endl;
        }
    }

    Vertice<T> * insertarVertice(T valor){
        if (this->encontrarVertice(valor)){
            return this->encontrarVertice(valor);
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
        }else{
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

    void crearVerticesAleatorios(unsigned int cantidadVertices = 10){
        srand(time(NULL));
        while(this->cantidadVertices < cantidadVertices){
            unsigned int valorArista = 1 + rand() % (999 - 0);
            this->insertarVertice(valorArista);
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
        cout << "SOLICITADO " << cantidadAristas << " - MAXIMO " << (this->cantidadVertices * (this->cantidadVertices - 1)) / 2 << endl;;
        if (cantidadAristas >=  ((this->cantidadVertices * (this->cantidadVertices - 1)) / 2)){
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

    void cambiarNombre(string nuevoNombre){
        this->nombreArchivo = nuevoNombre;
    }

    friend T operator << (Grafo<T> & grafo,const T p){
        grafo.insertarVertice(p);
        return p;
    }

    friend ostream& operator << (ostream &o,const Grafo<T> &grafo){
        o << endl;
        o << "-- MATRIZ DE ADYACENCIA DE " << grafo.nombreArchivo << endl;
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
        this->nombreArchivo = otro.nombreArchivo + "_copia";

        for (auto & vertice: otro.vertices){
            for (auto & arista: vertice.second->aristas){
                this->insertarArista(vertice.second->valor, arista->extremo->valor, arista->peso);
            }
        }

        return *this;
    }

    bool existeCamino(T valorVerticeInicio, T valorVerticeFinal){
        if (this->cantidadVertices < 3)
            return false;

        Vertice<T> * verticeInicio = this->encontrarVertice(valorVerticeInicio);
        if (!verticeInicio || !this->encontrarVertice(valorVerticeFinal))
            return false;

        queue<Arista<T> *> aristasPorVisitar;
        for(auto & arista: verticeInicio->aristas){
            if (arista->extremo->valor != valorVerticeFinal){
                aristasPorVisitar.push(arista);
            }
        }

        map<T, Vertice<T> *> verticesVisitados;
        verticesVisitados[valorVerticeInicio] = verticeInicio;

        while(!aristasPorVisitar.empty()){
            Arista<T> * aristaAux = aristasPorVisitar.front();
            aristasPorVisitar.pop();

            if (aristaAux->extremo->valor == valorVerticeFinal)
                return true;

            for(auto & aristaPendiente: aristaAux->extremo->aristas){
                if (verticesVisitados[aristaPendiente->extremo->valor] == NULL){
                    aristasPorVisitar.push(aristaPendiente);
                }
            }
        }
        return false;
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

    Grafo<T> generarArbolMinimoPorProfundida(T valorVerticeInicial){
        Grafo<T> arbolExpansionMinima(this->nombreArchivo + "_adexp", true, false, true);
        stack<Vertice<T> *> padres;

        Vertice<T> * verticeInicial = this->encontrarVertice(valorVerticeInicial);
        if (!verticeInicial){
            return arbolExpansionMinima;
        }
        arbolExpansionMinima.insertarVertice(valorVerticeInicial);
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

    Grafo<T> generarArbolMinimoPorAnchura(T valorVerticeInicial){
        Grafo<T> arbolExpansionMinima(this->nombreArchivo + "_adexa", true);

        Vertice<T> * verticeInicial;
        arbolExpansionMinima.insertarVertice(valorVerticeInicial);
        arbolExpansionMinima.mostrarListaDeAdyacencia();

        int idxVerticesAgregados = 0;

        while(arbolExpansionMinima.cantidadVertices != this->cantidadVertices){
            verticeInicial = this->encontrarVertice(arbolExpansionMinima.valoresVertices[idxVerticesAgregados++]);
            for (auto & arista: verticeInicial->aristas){
                if (arbolExpansionMinima.vertices.find(arista->extremo->valor) == arbolExpansionMinima.vertices.end()){
                    arbolExpansionMinima.insertarArista(verticeInicial->valor, arista->extremo->valor);
                }
            }
        }
        return arbolExpansionMinima;
    }

    Grafo<T> generarKruskal(){
        Grafo<T> grafoKruskal("kruskal",true,false,false,true);

        // Agrupamos todas las aristas, para poder ordenarlas
        vector<pair<Vertice<T> *, Arista<T> *>> listaAristas;
        for (auto & vertice: this->vertices){
            for (auto & arista: vertice.second->aristas){
                pair<Vertice<T> *, Arista<T> *> verticeAB (vertice.second, arista);
                listaAristas.push_back(verticeAB);
            }
        }
        // Ordenando aristas de menor a mayor
        sort(listaAristas.begin(), listaAristas.end(), compararAristas);

        // recorremos todas las aristas ordenadas
        for (auto & candidato: listaAristas){
            if (!grafoKruskal.existeCamino(candidato.first->valor, candidato.second->extremo->valor) && !grafoKruskal.encontrarArista(candidato.first->valor, candidato.second->extremo->valor)){
                grafoKruskal.insertarArista(candidato.first->valor, candidato.second->extremo->valor, candidato.second->peso);
            }
            if (grafoKruskal.cantidadVertices == this->cantidadVertices) // termina cuando tienen misma cantidad de vertices
                break;
        }

        return grafoKruskal;
    }

};

template <typename G, typename V1>
void insertarCaminoEn(G & grafo, const V1 & unico){
    grafo.insertarVertice(unico);
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
