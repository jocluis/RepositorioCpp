//
// Created by jcasiano on 15/6/2021.
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



//ini - clase abstracta cola
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
//fin - clase abstracta cola





template <typename E> class LCola : public Cola<E> {
private:
    Nodo<E>* base;
    Nodo<E>* cima;
    int tam;  //Tamanio de la cola


public:

    /*
     * Constructor
     */
    LCola(){
        this->base = NULL;
        this->cima = NULL;
        this->tam = 0;
    }

    /*
     * Destructor
     */
    ~LCola(){
        clear();
    }

    void clear(){
        while (this->base!=NULL){
            Nodo<E> *toDelete = this->base;
            this->base = this->base->siguiente;
            delete toDelete;
        }
        this->tam=0;
    }

    void encolar(E val){

        Nodo<E> *aux = new Nodo<E>(val,NULL);

        if(this->tam==0)
        {
            this->base = aux;
        }else
        {
            this->cima->siguiente = aux;
        }
        this->cima=aux;
        this->tam++;
    }

    E desencolar(){
        E elemento = this->base->elemento;
        if(this->tam==0){
            return NULL;
        }
        Nodo<E> *toDelete = this->base;
        this->base=this->base->siguiente;
        delete toDelete;
        this->tam--;
        return elemento;
    }

    E valorFrontal(){
        return this->base->elemento;
    }

    int longitud(){
        return this->tam;
    }


};


int main() {

    LCola<int> *Colatest = new LCola<int>();

    Colatest->encolar(10);
    Colatest->encolar(20);
    Colatest->encolar(30);
    Colatest->encolar(40);
    /*
     * Debe reportarse en pantalla:
     * 10
     * 20
     * 30
     * 40
     */

    while(Colatest->longitud()>0){
        cout<<Colatest->desencolar()<<endl;
    }
    delete Colatest;
    return 0;
}

