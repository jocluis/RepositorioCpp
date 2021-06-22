//
// Created by jcasiano on 15/6/2021.
//

//
// Created by jcasiano on 1/6/2021.
// Creacion de metodos de una pila basado en Arreglos (APila)
//Clase 5

#include <iostream>
using namespace std;

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