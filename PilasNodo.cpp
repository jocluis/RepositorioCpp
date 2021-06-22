//
// Created by jcasiano on 1/6/2021.
// Creacion de metodos de una pila basado en Nodos(LPila)
//

#include <iostream>
using namespace std;

//Nodo
template<typename E> class Nodo{
public:
    E elemento; //Valor para este Nodo
    Nodo *siguiente; // Puntero al siguiente nodo de la lista

    //Constructor
    Nodo(E elem, Nodo* proximo=NULL){
        this->elemento = elem;
        this->siguiente = proximo;
    }
    Nodo(Nodo* proximo=NULL){
        this->siguiente = proximo;
    }
};

//Clase Padre: Pila
template<typename E> class Pila {
public:
    Pila(){}
    ~Pila(){}
    virtual void limpiar() = 0;
    virtual void push(E var) = 0;
    virtual E pop() = 0;
    virtual E valorTop() = 0;
    virtual int longitud() = 0;
};

template<typename E> class LPila : public Pila<E>{
private:
    Nodo<E>* cima;
    int tam;
public:
    /*
     * Constructor
     */
    LPila(){
        this->cima = NULL;
        this->tam = 0;
    }
    /*
     * Destructor
     */
    ~LPila(){
        limpiar();
    }

    void limpiar(){
        while (this->cima!=NULL){
            Nodo<E> *toDelete = this->cima;
            this->cima = this->cima->siguiente;
            delete toDelete;
        }
        this->tam=0;
    }

    void push(E var){
        Nodo<E> *aux = new Nodo<E>(var,cima);
        this->cima = aux;
        this->tam++;
    }

    E pop(){
        E elemento = this->cima->elemento;
        if(this->tam==0){
            return NULL;
        }
        Nodo<E> *toDelete = this->cima;
        this->cima=this->cima->siguiente;
        delete toDelete;
        this->tam--;
        return elemento;
    }

    E valorTop(){
        return this->cima->elemento;
    }

    int longitud(){
        return this->tam;
    }

};


int main() {

    LPila<int> *pila = new LPila<int>();
    pila->push(10);
    pila->push(20);
    pila->push(30);
    pila->push(40);

    while (pila->longitud()>0){
        cout<<"Elemento ["<<pila->longitud()<<"] : "<<pila->pop()<<endl;
    }

    delete pila;


    return 0;
}