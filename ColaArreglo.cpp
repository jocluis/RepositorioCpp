//
// Created by jcasiano on 1/6/2021.
// Creacion de metodos de una cola basado en Array (circular) (ACola)
//Clase 6

#include <iostream>
using namespace std;

//clase abstracta cola
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
        //this->listaArreglo[this->frente]=NULL;
    }


};


int main() {

    ACola<int> *Colatest = new ACola<int>();

    Colatest->encolar(10);
    Colatest->encolar(20);
    Colatest->encolar(30);
    Colatest->encolar(40);
    /*
     * Debe reportarse en pantalla:
     * 40
     * 30
     * 20
     * 10
     */

    while(Colatest->longitud()>0){
        cout<<Colatest->desencolar()<<endl;
    }
    delete Colatest;
    return 0;
}

