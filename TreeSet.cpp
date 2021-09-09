//
// Created by jcasiano on 29/6/2021.
//

#include <iostream>
using namespace std;


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
};
//Nodo
template<typename E> class Nodo{
public:
    E elemento; //Valor para este Nodo
    Nodo *derecha; // Puntero al hijo derecho del arbol
    Nodo *izquierda;// Puntero al hijo izquierdo del arbol

    //Constructor
    Nodo(E elem, Nodo* der=NULL,Nodo* izq=NULL){
        this->elemento = elem;
        this->derecha = der;
        this->izquierda = izq;
    }
    Nodo(Nodo* der=NULL,Nodo* izq=NULL){
        this->elemento = NULL;
        this->derecha = der;
        this->izquierda = izq;
    }
};

//TreeSet
template<typename Key>
class TreeSet : public Set<Key>{
private:
    Nodo<E *> *arbol; //arbol;
public:
    SetBasico()  {
        this->arbol =new Nodo<E *>;
    }

    ~SetBasico(){
        delete arbol;
    }

    void limpiar(){
    }
    //O
    void insertar(Key k)
    {
        if(!this->arbol->encontrar(k))
        //    this->arbol->insertar(k);
    }
    //O
    void remover(Key k)
    {
        if(!this->arbol->encontrar(k))
           // this->arbol->eliminar(k);
    }
    //O(1)
    Key removerCualquiera()
    {

    }
    //O
    int encontrar(Key k)
    {

    }

    int longitud()
    {
    }

    void imprimirArreglo()
    {
    }
};
