//
// Created by jcasiano on 1/6/2021.
// Creacion de metodos de una cola basado en Array (circular) (ACola)
//Clase 6

#include <iostream>
#include "PilasArreglo.cpp"

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

    void encolarPrioridad(E val){
        if(this->longitud()==0)
            this->encolar(val);
        else
            prioridad(val);
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

};


void encolar()
{
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
}

void encolarconPrioridad()
{
    ACola<int> *Colatest = new ACola<int>();

    Colatest->encolarPrioridad(124);
    Colatest->encolarPrioridad(0);
    Colatest->encolarPrioridad(233);
    Colatest->encolarPrioridad(412);
    Colatest->encolarPrioridad(1);

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
}

int main() {
    //1. encolar normal
    //encolar();
    //2. encolar con prioridad
    encolarconPrioridad();
    return 0;
}

