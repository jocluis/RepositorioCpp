/*
 *  Created by jcasiano on 14/6/2021.
 *
 *  Titulo: Clase Grafo
 *  (Se han usados las siguientes estructuras para los métodos de la clase Grafo)
 *  - Lista Arreglo
 *  - Lista Enlazada
 *  - Cola (basada en lista arreglo)
 *  - Pila (basada en lista arreglo) - uso en priorizar cola
 *  - Set  (basado en lista arreglo)
 *  - Diccionario (basado en lista arreglo)
*/

#include <iostream>
#include <chrono>
#include<windows.h>
using namespace std;

//objeto auxiliar para guardar par x,y
template <typename E,typename Y>
class Objetopair
{
public:
    E x; //Primer valor
    Y y; //Segundo valor

    //Constructor
    Objetopair()
    {}
    Objetopair(E x,Y y)
    {
        this->x = x;
        this->y = y;
    }
};

class Arista{
public:
    int u,v,w;
    bool operator<(const Arista &e) const{
        return w < e.w;
    }
};


/*** INI - Estructura de datos lista Enlazada y lista Arreglo ***/
template <typename E>
//Clase nodo
class Nodo
{
public:
    E elemento;      //Valor para este nodo
    Nodo *siguiente; //Puntero al siguiente nodo de la lista

    //Constructor
    Nodo(E elem, Nodo *proximo = NULL)
    {
        this->elemento = elem;
        this->siguiente = proximo;
    }
    Nodo(Nodo *proximo = NULL)
    {
        this->siguiente = proximo;
    }
};

//Clase Padre: Lista
template <typename E>
class Lista
{
private:
public:
    //Constructor
    Lista() {}
    //Destructor
    ~Lista() {}

    //Limpiar la lista: dejarla vacia la lista
    virtual void limpiar() = 0;
    //Insertar un elemento donde se encuentra el puntero "actual"
    virtual void insertar(E elemento) = 0;
    //Agregar un elemento a la lista (al final)
    virtual void agregar(E elemento) = 0;
    //Libera de la memoria y retorna el elemento "actual"
    virtual E eliminar() = 0;
    //Mover "actual" al inicio de la lista
    virtual void moverAInicio() = 0;
    //Mover "actual" al final de la lista
    // primer espacio disponible
    virtual void moverAlFinal() = 0;
    //Mover "actual" a la posicion anterior (izquierda)
    virtual void anterior() = 0;
    //Mover "actual" a la posicion posterior (derecha)
    virtual void siguiente() = 0;
    //Retornar le numero de elementos de la lista
    virtual int longitud() = 0;
    //Retornar la posicion del elemento "actual"
    virtual int posicionActual() = 0;
    //"Actual" se mueve a la posicion "pos"
    virtual void moverAPosicion(int pos) = 0;
    //Retorna el valor que estaba en la posicion "actual"
    virtual E getValor() = 0;
    //Modificar el valor en la posicion "actual"
    virtual void setValor(E elemento) = 0;
};

//Lista Enlazada
//Clase hija: ListaEnlazada
template <typename E>
class ListaEnlazada : public Lista<E>
{
private:
    Nodo<E *> *cabeza; //puntero al primer elemento
    Nodo<E *> *cola;   //puntero al ultimo elemento
    Nodo<E *> *actual; //puntero al elemento actual
    int cantidad;      //tamanho de la lista

    void inicializar()
    {
        this->cantidad = 0;
        this->cola = this->actual = this->cabeza = new Nodo<E *>;
    }

    void eliminarTodo()
    {
        while (this->cabeza != NULL)
        {
            this->actual = this->cabeza;
            this->cabeza = this->cabeza->siguiente;
            delete actual;
        }
    }

public:
    //Constructor
    ListaEnlazada()
    {
        inicializar();
    }

    //Destructor
    ~ListaEnlazada()
    {
        eliminarTodo();
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar()
    {
        eliminarTodo();
        inicializar();
    }

    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento)
    {
        this->actual->siguiente = new Nodo<E *>(new E(elemento), this->actual->siguiente);
        if (this->cola == this->actual)
            this->cola = this->actual->siguiente;
        this->cantidad++;
    }
    //Insertar - otra forma de implementar el metodo anterior
    void insertar_otro(E elemento)
    {
        Nodo<E *> *aux=new Nodo<E *>;
        aux->elemento=new E(elemento);
        aux->siguiente=this->actual->siguiente;
        this->actual->siguiente=aux;
        if (this->cola == this->actual)
            this->cola = this->actual->siguiente;
        this->cantidad++;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento)
    {
        this->cola = this->cola->siguiente = new Nodo<E *>(new E(elemento), NULL);
        this->cantidad++;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio()
    {
        this->actual = this->cabeza;
    }

    //Mover "actual" al final de la lista
    // primer espacio disponible
    void moverAlFinal()
    {
        this->actual = this->cola;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente()
    {
        if (this->actual != this->cola)
            this->actual = this->actual->siguiente;
    }

    //Retornar le numero de elementos de la lista
    int longitud()
    {
        return this->cantidad;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor()
    {
        if (this->actual->siguiente == NULL)
        {
            cout << "Valor no existe";
            //return -1;
        }
        return *this->actual->siguiente->elemento;
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento)
    {
        if (this->actual->siguiente == NULL)
            cout << "Valor no existe";
        else
            *this->actual->siguiente->elemento = elemento;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior()
    {
        Nodo<E *> *temp = cabeza;
        Nodo<E *> *tempActual = actual;

        moverAInicio();
        // int i;
        for (int i = 0; tempActual != temp; ++i)
        {
            temp = temp->siguiente;
            if (tempActual != temp)
            {
                siguiente();
            }
        }
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual()
    {
        Nodo<E *> *temp = cabeza;
        int i;
        for (i = 0; actual != temp; ++i)
        {
            temp = temp->siguiente;
        }
        return i;
    }

    //Libera de la memoria y retorna el elemento "actual"
    E eliminar()
    {
        Nodo<E *> *tempActual = actual;
        Nodo<E *> *temp = cabeza;

        moverAInicio();
        // int i;
        for (int i = 0; tempActual != temp; ++i)
        {
            temp = temp->siguiente;
            if (temp == tempActual && temp != cola)
            {
                actual = actual->siguiente->siguiente;
            }
            else
            {
                siguiente();
            }
        }

        return *tempActual->elemento;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos)
    {
    }

    Nodo<E *> *getActualNodo()
    {
        return this->actual;
    }

    Nodo<E *> *getCabezaNodo()
    {
        return this->cabeza;
    }

    Nodo<E *> *getColaNodo()
    {
        return this->cola;
    }

    void reportarConNodos()
    {
        Nodo<int *> *temp = this->getCabezaNodo();
        temp = temp->siguiente;

        while (temp != NULL)
        {
            cout << "[" << *temp->elemento << "]";
            temp = temp->siguiente;
        }

        cout << endl;
    }
};

//Clase Hija: ListaArreglo
template <typename E>
class ListaArreglo : public Lista<E>
{
private:
    E *arreglo;   //Arreglo de elementos
    int tamMax;   //Tamanho fijo
    int tamLista; //Tamanho de la lista
    int actual;   //Indice "actual"

public:
    //Constructor
    ListaArreglo(int tamMax = 100)
    {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Destructor
    ~ListaArreglo()
    {
        delete[] this->arreglo;
    }

    //Mover "actual" al inicio de la lista
    void moverAInicio()
    {
        this->actual = 0;
    }

    //Mover "actual" al final de la lista:
    // primer espacio disponible
    void moverAlFinal()
    {
        this->actual = this->tamLista;
    }

    //Mover "actual" a la posicion posterior (derecha)
    void siguiente()
    {
        //Sentinela
        if (this->actual < this->tamLista)
            this->actual++;
    }

    //Mover "actual" a la posicion anterior (izquierda)
    void anterior()
    {
        //Sentinela
        if (this->actual > 0)
            this->actual--;
    }

    //Agregar un elemento a la lista (al final)
    void agregar(E elemento)
    {
        this->arreglo[this->tamLista++] = elemento;
    }

    //Agregar un elemento a la lista (al final)
    void agregarOrdenadamente(E elemento)
    {
        for (int i = 0; this->tamLista; i++)
            if (this->arreglo[i] >= elemento)
            {
                this->moverAPosicion(i);
                this->insertar(elemento);
                break;
            }
    }

    //Retornar le numero de elementos de la lista
    int longitud()
    {
        return this->tamLista;
    }

    //Retornar la posicion del elemento "actual"
    int posicionActual()
    {
        return this->actual;
    }

    //"Actual" se mueve a la posicion "pos"
    void moverAPosicion(int pos)
    {
        //Sentinela
        if (pos >= 0 && pos < this->tamLista)
            this->actual = pos;
    }

    //Retorna el valor que estaba en la posicion "actual"
    E getValor()
    {
        return this->arreglo[this->actual];
    }

    E getValor(int pos)
    {
        return this->arreglo[pos];
    }

    //Modificar el valor en la posicion "actual"
    void setValor(E elemento)
    {
        this->arreglo[this->actual] = elemento;
    }

    //Limpiar la lista: dejarla vacia la lista
    void limpiar()
    {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Insertar un elemento donde se encuentra el puntero "actual"
    void insertar(E elemento)
    {
        for (int i = this->tamLista; i > this->actual; i--)
            this->arreglo[i] = this->arreglo[i - 1];
        this->arreglo[this->actual] = elemento;
        this->tamLista++;
    }

    //Eliminar y retornar el elemento "actual"
    E eliminar()
    {
        E eliminado = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista; ++i)
            this->arreglo[i] = this->arreglo[i + 1];
        this->tamLista--;
        return eliminado;
    }

    //ordenar Lista de enteros
    void ordenarListaInt()
    {
        int pos,aux;
        for(this->moverAInicio(); //Inicializacion
            this->posicionActual()<this->longitud(); //Condicion de parada
            this->siguiente()){ //Incremento
            pos = this->posicionActual();
            aux = this->getValor();
            //cout<<"posicion:"<<lista->posicionActual()<<endl;

            while((pos>0) && ((int)this->getValor(pos-1)>aux))
            {
                this->setValor((int)this->getValor(pos-1));
                pos--;
            }
            this->moverAPosicion(pos);
            this->setValor(aux);

            this->moverAPosicion(pos);

        }
    }
};

/*** FIN - Estructura de datos lista Enlazada y lista Arreglo ***/


/*** INI - Estructura de datos Diccionario basado en Lista Arreglo***/
template<typename Key, typename E> class Diccionario{
private:
public:
    Diccionario(){} //Constructor
    ~Diccionario(){} //Destructor

    //Reinicializacion de un diccionario
    virtual void limpiar() = 0;

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    virtual void insertar(Key K, E e) = 0;

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    //virtual E remover(Key K) = 0;


    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    virtual E removerCualquiera() = 0;

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    virtual E encontrar(Key K) = 0;

    //Retornar el número de registros dentro del diccionario
    virtual int longitud() = 0;
};

template<typename Key, typename E> class KVPar{
private:
    Key k;
    E e;
public:
    //Constructor
    KVPar(){}
    KVPar(Key kval, E eval){this->k = kval; this->e = eval;}
    KVPar(KVPar& o){ this->k = o.k; this->e = o.e; }

    Key key(){
        return this->k;
    }

    void setKey(Key ink){
        this->k = ink;
    }

    E valor(){
        return this->e;
    }
};

template<typename Key, typename E>
class DiccionarioArreglo : public Diccionario<Key, E>{
private:
    ListaArreglo<KVPar<Key, E>> *lista;
public:

    DiccionarioArreglo() {
        this->lista = new ListaArreglo<KVPar<Key, E>>();
    }

    ~DiccionarioArreglo() {
        delete[] this->lista;
    }

    //Reinicializacion de un diccionario
    void limpiar() {
        delete[] this->lista;
        this->lista = new ListaArreglo<KVPar<Key, E>>();
    };

    //Insertar un registro
    //k: la clave para el reigstro
    //e: el registro
    void insertar(Key K, E e) {
        this->lista->insertar(*new KVPar<Key, E>(K, e));
    };



    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    E removerCualquiera() {
        return (this->lista->eliminar()).valor();
    };

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    E encontrar(Key K) {
        this->lista->moverAInicio();
        int i=0;
        while (this->lista->getValor().key()!=K && this->longitud()!=i){
            this->lista->siguiente();
            i++;
        }
        if (this->longitud()<i){
            return -1;
        } else {
            return this->lista->getValor().valor();
        }
    };

    //Retornar el número de registros dentro del diccionario
    int longitud() {
        int length = this->lista->longitud();
        return length;
    };
};
/*** FIN - Estructura de datos Diccionario basado en Lista Arreglo***/


/*** INI - Estructura de datos Pila basado en Lista Arreglo***/
//Clase Padre: Pila
template<typename E> class Pila{
public:
    Pila(){}
    ~Pila(){}
    virtual void limpiar() = 0;
    virtual void push(E var) = 0;
    virtual E pop() = 0;
    virtual E valorTop() = 0;
    virtual int longitud() = 0;
};

//Clase hija: Pila Arreglo: Arreglo Pila (APila)
template<typename E> class APila : public Pila<E>{
private:
    E *arregloLista;
    int tamMaximo;
    int cima; //top
public:
    APila(int tam = 100){
        this->tamMaximo = tam;
        this->cima = 0;
        this->arregloLista = new E[this->tamMaximo];
    }

    ~APila(){
        delete[] this->arregloLista;
    }

    //En tiempo O(1): borrado logico
    void limpiar() {
        this->cima = 0;
    }

    //En tiempo O(1)
    void push(E elemento) {
        this->arregloLista[this->cima++] = elemento;
    }

    //En tiempo O(1): retorna el valor top y SI lo borra de la pila
    E pop() {
        return this->arregloLista[--this->cima];
    }

    //En tiempo O(1): retorna el valor top pero NO lo borra de la pila
    E valorTop() {
        return this->arregloLista[this->cima-1];
    }

    //En tiempo O(1)
    int longitud() {
        return this->cima;
    }
};
/*** FIN - Estructura de datos Pila basado en Lista Arreglo***/


/*** INI - Estructura de datos Cola basado en Lista Arreglo***/
template<typename E> class Cola {
private:
    void operator = (const Cola&) {}  //Proteccion asignada
    Cola(const Cola&) {}  //Constructor Proteccion copia
public:
    Cola(){}  //por defecto
    virtual ~Cola() {}  //Base destructor

    //Reinicializar la cola. El usuario es responsable
    //por reclamar el espacio utilizado por el elemento
    //de la cola
    virtual void clear() = 0;

    //colocar un elemento en la parte de atras de la cola
    //it: el elemento siendo encolado
    virtual void encolar( E) = 0;

    //Remover y retornar elementos al frente de la cola
    //Retornar: El elemento en el frente de la cola.
    virtual E desencolar() = 0;

    //Retornar: Una copia de el elemento frontal
    virtual E valorFrontal() = 0;

    //Retornar: El numero de elementos in la cola .
    virtual int longitud() = 0;
};

template <typename E> class ACola : public Cola<E> {
private:
    int tamanhoMax;  //Tamaño maximo de la cola
    int frente;     //Indice del elemento frontal
    int elemFin;    //Indice del elemento final
    E *listaArreglo;  //Arreglo conteniendo los elementos de la cola

public:

    /*
     * Constructor
     */
    ACola(int l=100){
        this->tamanhoMax = l;
        this->frente=1;
        this->elemFin=0;
        this->listaArreglo = new E[this->tamanhoMax+1];
    }

    /*
     * Destructor
     */
    ~ACola(){
        //limpiar();
    }

    void encolar(E val){
        this->listaArreglo[elemFin+1] = val;
        this->elemFin++;
    }

    E desencolar(){
        E val = this->listaArreglo[frente];
        this->frente++;
        return val;
    }

    void encolarPrioridad(E val){
        if(this->longitud()==0)
            this->encolar(val);
        else
            prioridad(val);
    }

    E valorFrontal(){
        return this->listaArreglo[frente];
    }

    int longitud(){
        if(this->elemFin==this->tamanhoMax){
            return tamanhoMax;
        }else {
            return (this->tamanhoMax - this->frente + this->elemFin + 1) % (this->tamanhoMax);
        }
    }

    void clear(){
        this->frente=1;
        this->elemFin=0;
    }

    void prioridad(E val)
    {
        APila<int> *pilaAux = new APila<int>;
        E *auxArr= new E[this->longitud()];
        int unico=1;
        auxArr=this->listaArreglo;
        for(int i=this->elemFin;i>0;i--)
        {
            if(val < auxArr[i])
            {
                pilaAux->push(auxArr[i]);
            } else
            {
                if(unico==1)
                {
                    pilaAux->push(val);
                    unico++;
                }
                pilaAux->push(auxArr[i]);
            }
        }
        if(unico==1)
        {
            pilaAux->push(val);
        }
        this->clear();
        while(pilaAux->longitud()>0){
            this->encolar(pilaAux->valorTop());
            pilaAux->pop();
        }
    }
    int priorizar(int v, int d)
    {
        int min=d;
        for(int i=this->elemFin;i>0;i--)
        {
            if(listaArreglo[i].y==v)
                if(min >listaArreglo[i].x)
                    min=listaArreglo[i].x;
        }
        return min;
    }

};

/*** FIN - Estructura de datos Cola basado en Lista Arreglo***/


/*** INI - Estructura de datos Set basado en lista arreglo***/
//Clase Abstracta: Set
template<typename Key>
class Set{
public:
    //Constructor
    Set(){}

    //Base destructor
    ~Set(){}

    //Permite reinicializar la estructura de datos
    virtual void limpiar() = 0;

    //La inserción del valor k
    virtual void insertar(Key k) = 0;

    //Dada una clave, el registro correspondiente debe ser removido
    virtual void remover(Key k) = 0;

    //Retorna y remueve un registro arbitrario del set
    virtual Key removerCualquiera() = 0;

    //Retorna una posición del registro que se asocie con k
    virtual int encontrar(Key k) = 0;

    //Retornar el número de registros o claves existentes en el set
    virtual int longitud() = 0;

    //Obtner el valor iniciar
    virtual Key obtenerInicio()=0;
};

//SetBasico
template<typename Key>
class SetBasico : public Set<Key>{
private:
    ListaArreglo<Objetopair<int,int>*> *lista;
public:
    SetBasico(int tamanho = 100)  {
        this->lista = new ListaArreglo<Key*>(tamanho);
    }

    ~SetBasico(){
        delete lista;
    }

    void limpiar(){
        this->lista->limpiar();
    }
    //O(n)
    void insertar(Key k)
    {
        int pos = this->encontrar(k);
        if (pos == -1) {
            this->lista->agregar(new Key(k));
        }
    }
    //O(n)
    void remover(Key k)
    {
        int pos = this->encontrar(k);
        this->lista->moverAPosicion(pos);
        this->lista->eliminar();
    }
    //O(n)
    Key removerCualquiera()
    {
        this->lista->moverAlFinal();
        this->lista->anterior();
        return *this->lista->eliminar();
    }
    //O(n)
    Key obtenerInicio()
    {
        this->lista->moverAInicio();
        return *this->lista->getValor();
    }
    //O(n)
    int encontrar(Objetopair<int,int> k)
    {
        this->lista->moverAInicio();
        for (this->lista->moverAInicio(); this->lista->posicionActual() < this->lista->longitud(); this->lista->siguiente())
        {
            if (this->lista->getValor() != nullptr && (this->lista->getValor()->x == k.x) && (this->lista->getValor()->y == k.y)) {
                return this->lista->posicionActual();
            }
        }
        return -1;
    }

    int longitud()
    {
        return this->lista->longitud();
    }

    void imprimirArreglo()
    {
        this->lista->imprimirArreglo();
    }
};
/*** FIN - Estructura de datos Set basado en lista arreglo***/



class DSU {
private:
    int n;
    ListaArreglo<int> *par;
    ListaArreglo<int> *rank;

public:
    DSU(int n)
    {
        this->n=n;
        this->par = new ListaArreglo<int>();
        this->rank = new ListaArreglo<int>();
        for (int i=0;i<n;i++)
        {
            this->par->setValor(i);
            this->rank->setValor(0);
        }
    }
    int root(int x)
    {
        this->par->moverAPosicion(x);
        while(this->par->getValor()!=x)
        {
            this->par->setValor(this->par->getValor(this->par->getValor()));
            x=this->par->getValor();
            this->par->moverAPosicion(x);
        }
        return x;
    }
    bool join(int x,int y)
    {
        x=root(x);
        y=root(y);

        if(x==y) return false;
        if(this->rank[x].getValor()<this->rank[y].getValor()) swap(x,y);
        this->par[y].setValor(x);
        if(this->rank[y].getValor()==this->rank[x].getValor())
            this->rank[x].setValor(this->rank[x].getValor()+1);
        return true;
    }

};


class DSU2 {
private:
    int n;
    int *par;
    int *rank;

public:
    DSU2(int n)
    {
        this->n=n;
        this->par = new int[n];
        this->rank = new int[n];
        for (int i=0;i<n;i++)
        {
            this->par[i]=i;
            this->rank[i]=0;
        }
    }
    int root(int x)
    {
        while(this->par[x]!=x)
        {
            this->par[x]=this->par[this->par[x]];
            x=this->par[x];
        }
        return x;
    }
    bool join(int x,int y)
    {
        x= root(x);
        y=root(y);

        if(x==y) return false;

        if(rank[x]< rank[y])
            swap(x,y);
        par[y]=x;
        if(rank[y]==rank[x])
            rank[x]++;

        return true;
    }

};


/*** INI - Estructura de datos Grafo basado en lista adyacencia (ListaEnlazada)***/
/*Inicio de Grafo*/
class Grafo{
private:
public:
    //Constructor
    Grafo(){}
    //Metodo de inicializacion
    virtual void init(int n,char tipoGrafo) = 0;
    virtual int get_N_Vertices()=0;
    virtual int get_N_Aristas()=0;
    virtual void setArista(int i, int j, int w) = 0;
    virtual int getPeso(int i, int j) = 0;
    virtual int getMarca(int v) = 0;
    virtual void setMarca(int v, int val) = 0;
};

//Implementacion usando representacion de Lista de adyacencia
class GrafoLA : public Grafo{
private:
    int numeroVertices;
    int numeroAristas;
    ListaEnlazada<Objetopair<int,int>> *listaAd;
    DiccionarioArreglo<string,int> *aristas; //aristas guardadas como diccionario
    int *marca; // vertices visitados
    int *distancia; //distancia entre nodos adyancentes
    int *distanciaDis;//distancia para dijkstra
    bool *visitadosPrim;//visitados Prim
    char tipoGrafo;//Grafo Dirigido o No dirigido  N:No dirigido(ida y vuelta) / D: Dirigido(flecha ida)

    ListaArreglo<Arista> *edges;
    //vector<Arista> edges;
public:
    //Metodo de inicializacion: inicializar la matriz
    void init(int n,char tipoGrafo) {
        int i,j;
        this->numeroVertices = n;
        this->numeroAristas = 0;
        this->marca = new int[n];
        this->listaAd=new ListaEnlazada<Objetopair<int,int>>[n];
        this->distancia = new int[n];
        this->distanciaDis = new int[n];
        this->visitadosPrim = new bool[n];
        this->aristas = new DiccionarioArreglo<string,int>;
        this->tipoGrafo = tipoGrafo;//N:No dirigido / D: Dirigido
        this->edges=new ListaArreglo<Arista>();
        //Inicializamos el arreglo de marca (vertices visitados)
        for (i = 0; i < this->numeroVertices; i++) {
            this->marca[i] = 0; //NO VISITADO
        }
        //Inicializamos el arreglo de distancia (distancia entre nodos adyancentes) nivel profundidad
        for (i = 0; i < this->numeroVertices; i++) {
            this->distancia[i] = -1; //NO VISITADO
            this->distanciaDis[i]=5555555;//NO VISITADO DIJKSTRA
            this->visitadosPrim[i]=false;//visitados para prim
        }
    }

    GrafoLA(int numVert,char tipoGrafo){
        this->init(numVert,tipoGrafo);
    }

    ~GrafoLA(){
        delete[] this->marca;
        delete[] this->listaAd;
    }

    //Retornar el numero de vertices y aristas
    int get_N_Vertices(){
        return this->numeroVertices;
    }

    int get_N_Aristas(){
        return this->numeroAristas;
    }




    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    void setArista(int i, int j, int w) {
        this->listaAd[i].agregar(*new Objetopair<int,int>(j,w));
        if(this->tipoGrafo=='N')
        {
            this->listaAd[j].agregar(*new Objetopair<int,int>(i,w));
        }
        this->edges->setValor(*new Arista{i,j,w});
    }




    //Retornar el peso de una arista
    int getPeso(int i, int j) {
        return this->aristas->encontrar(i+","+j);
    }

    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    int getMarca(int v) {
        return this->marca[v];
    }

    void setMarca(int v, int val) {
        this->marca[v] = val;
    }

    void bfs(int src)
    {
        ACola<int> *q=new ACola<int>();
        q->encolar(src);
        this->distancia[src]=0;

        while (q->longitud()>0) {
            int v = q->valorFrontal();
            q->desencolar();

            for(this->listaAd[v].moverAInicio();this->listaAd[v].posicionActual()<this->listaAd[v].longitud();this->listaAd[v].siguiente())
            {
                Objetopair<int,int> temporal=this->listaAd[v].getValor();
                int u=temporal.x;
                if (this->distancia[u] == -1) {
                    this->distancia[u] = this->distancia[v] + 1;
                    q->encolar(u);
                }
            }
        }

        for (int i = 0; i < this->numeroVertices; i++) {
            cout << this->distancia[i] << ' ';
        }
        cout << endl;
        delete q;
    }
    void bfs_ruta(int ini,int fin)
    {
        ACola<int> *q=new ACola<int>();
        q->encolar(ini);
        this->distancia[ini]=0;

        while (q->longitud()>0) {
            int v = q->valorFrontal();
            q->desencolar();

            //if(v==fin) break; ////fin encontrado
            for(this->listaAd[v].moverAInicio();this->listaAd[v].posicionActual()<this->listaAd[v].longitud();this->listaAd[v].siguiente())
            {
                Objetopair<int,int> temporal=this->listaAd[v].getValor();
                int u=temporal.x;
                if (this->distancia[u] == -1) {
                    this->distancia[u] = this->distancia[v] + 1;
                    q->encolar(u);
                }
            }
        }

       /*for (int i = 0; i < this->numeroVertices; i++) {
            cout << this->distancia[i] << ' ';
        }
        cout << endl;*/
        delete q;
    }
    void dijkstra_ruta(int ini,int fin)
    {
        SetBasico<Objetopair<int,int>> *pq=new SetBasico<Objetopair<int,int>>;//priozacion con Set
        distanciaDis[ini]=0;

        pq->insertar(*new Objetopair<int,int>(0,ini));
        while(pq->longitud()>0)
        {
            int d=pq->obtenerInicio().x;
            int v=pq->obtenerInicio().y;
            pq->remover(pq->obtenerInicio());

            //if(distanciaDis[v] && v==fin) break;////fin encontrado
            if(d!=distanciaDis[v])
                continue;
            for(this->listaAd[v].moverAInicio();this->listaAd[v].posicionActual()<this->listaAd[v].longitud();this->listaAd[v].siguiente()) {
                Objetopair<int, int> temporal = this->listaAd[v].getValor();
                int u = temporal.x;
                int w = temporal.y;
                if(distanciaDis[v]+w<distanciaDis[u])
                {
                    distancia[u]=v;
                    distanciaDis[u]=distanciaDis[v]+w;
                    pq->insertar(*new Objetopair<int,int>(distanciaDis[u],u));
                }
            }
        }

        /*ruta
         * for(int i=0;i<this->numeroVertices;i++)
        {
            cout<<this->distanciaDis[i]<<' ';
        }
        cout<<endl;
        for(int i=0;i<this->numeroVertices;i++)
        {
            cout<<this->distancia[i]<<' ';
        }
        cout<<endl;
         */
    }


    void prim_ruta(int ini,int fin)
    {
        ACola<Objetopair<int,int>> *pq=new ACola<Objetopair<int,int>>();
        pq->encolar(*new Objetopair<int,int>(0,ini));
        int mst=0;
        while(pq->longitud()>0)
        {
            int d=pq->valorFrontal().x;
            int v=pq->valorFrontal().y;
            pq->desencolar();

            //if(visitadosPrim[v] && v==fin) break;////fin encontrado
            if(visitadosPrim[v])
                continue;

            d=pq->priorizar(v,d);//priorizacion de la cola
            mst +=d;
            visitadosPrim[v]=true;
            for(this->listaAd[v].moverAInicio();this->listaAd[v].posicionActual()<this->listaAd[v].longitud();this->listaAd[v].siguiente()) {
                Objetopair<int, int> temporal = this->listaAd[v].getValor();
                int u = temporal.x;//vertice
                int w = temporal.y;//distancia
                pq->encolar(*new Objetopair<int,int>(w,u));
            }
        }

        //cout<<"arbol de minima expansion: "<<mst<<endl;
    }

    void kruskal_ruta(int ini,int fin)
    {
        DSU2 dsu(this->numeroVertices);
        int mst=0;
       /* while(!edges.empty())
        {
            if(dsu.join(edges.begin()->u,edges.begin()->v))
            {
                mst+=edges.begin()->w;
                //if(fin==edges.begin()->v) break; ////fin encontrado
            }
            edges.erase(edges.begin());
        }*/
       for(this->edges->moverAInicio();this->edges->posicionActual()<this->edges->longitud();this->edges->siguiente())
       {
           if(dsu.join(this->edges->getValor().u,this->edges->getValor().v))
           {
               mst+=this->edges->getValor().w;
           }
       }
    }
};
/*** FIN - Estructura de datos Grafo basado en lista adyacencia (ListaEnlazada)***/


int main()
{
    //datos de test con 20 vertices
    GrafoLA *grafo = new GrafoLA(40,'N');
    grafo->setArista(0,1, 1);
    grafo->setArista(0,2, 6);
    grafo->setArista(0,7, 4);
    grafo->setArista(1,2, 1);
    grafo->setArista(1,4, 2);
    grafo->setArista(1,4, 7);
    grafo->setArista(2,8, 1);
    grafo->setArista(2,16, 2);
    grafo->setArista(2,4, 7);
    grafo->setArista(3,5, 1);
    grafo->setArista(3,6, 2);
    grafo->setArista(3,9, 7);
    grafo->setArista(4,10, 1);
    grafo->setArista(4,11, 2);
    grafo->setArista(4,12, 7);
    grafo->setArista(4,13, 1);
    grafo->setArista(4,14, 2);
    grafo->setArista(4,15, 7);
    grafo->setArista(4,17, 7);
    grafo->setArista(4,9, 1);
    grafo->setArista(4,19, 2);
    grafo->setArista(4,18, 7);
    grafo->setArista(5,20, 7);
    grafo->setArista(20,21, 7);
    grafo->setArista(21,22, 7);
    grafo->setArista(22,23, 7);
    grafo->setArista(23,24, 7);
    grafo->setArista(24,25, 7);
    grafo->setArista(25,26, 7);
    grafo->setArista(26,27, 7);
    grafo->setArista(28,24, 7);
    grafo->setArista(28,30, 7);
    grafo->setArista(30,39, 7);


    int iniRuta=0;
    int finRuta=39;

    auto t_start = std::chrono::high_resolution_clock::now();
    Sleep(10);
    grafo->bfs_ruta(iniRuta,finRuta);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    cout << "1. tiempo ejecucion de BFS: " << elapsed_time_ms<<" milisegundos."<< endl;

    t_start = std::chrono::high_resolution_clock::now();
    Sleep(10);
    grafo->dijkstra_ruta(iniRuta,finRuta);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    cout << "2. tiempo ejecucion de Dijkstra: " << elapsed_time_ms<<" milisegundos."<< endl;

    t_start = std::chrono::high_resolution_clock::now();
    Sleep(10);
    grafo->prim_ruta(iniRuta,finRuta);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    cout << "3. tiempo ejecucion de Prim: " << elapsed_time_ms<<" milisegundos."<< endl;

    t_start = std::chrono::high_resolution_clock::now();
    Sleep(10);
    grafo->kruskal_ruta(iniRuta,finRuta);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    cout << "4. tiempo ejecucion de Kruskal: " << elapsed_time_ms<<" milisegundos."<< endl;

    return 0;
}