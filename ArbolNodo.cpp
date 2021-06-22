//
// Created by jcasiano on 19/6/2021.
//

#include <iostream>
#include <string>

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
        this->derecha = der;
        this->izquierda = izq;
    }
};

template<typename E>
class ArbolBinario{
private:
public:
    ArbolBinario(){}
    ~ArbolBinario(){}
    virtual void insertar(E e) = 0;
    virtual E encontrar(E e) = 0;
    virtual int longitud()=0;
};

template<typename E>
class ArbolBinarioNodo : ArbolBinario<E>{
private:
    Nodo<E *> *arbol; //cabeza del arbol;
    int tam;//elementos que realmente estan dentro del arbol binario

public:
    ArbolBinarioNodo(){
        //this->arbol =new Nodo<E *>;
        this->arbol = NULL;
        this->tam=0;
    }

    ~ArbolBinarioNodo(){

    }
    void insertar(E e)
    {

        if(this->arbol == NULL)
        {
            *arbol =  new Nodo<E *>(new E(e), NULL, NULL);
        }
        else
        {
            int raiz_tmp= reinterpret_cast<int>(this->arbol->elemento);
            int e_tmp= reinterpret_cast<int>(new int(e));
            if(e_tmp < raiz_tmp) //izquierda
            {
                this->arbol = this->arbol->izquierda;
                insertar(e);
            }
            else //derecha
            {
                this->arbol = this->arbol->derecha;
                insertar(e);
            }
        }
    }
    void crearNodoArbol(E e)
    {
    }
    void insertar_old(E e){

        if(this->raiz == NULL)
        {
             this->raiz->elemento = new E(e);
        }else
        {
            int raiz_tmp= reinterpret_cast<int>(this->raiz->elemento);
            int e_tmp= reinterpret_cast<int>(new int(e));

            if(e_tmp < raiz_tmp) //izquierda
            {
                    this->raiz->izquierda = new Nodo<E *>(new E(e),NULL,NULL);
            }
            else //derecha
            {
                this->raiz->derecha = new Nodo<E *>(new E(e),NULL,NULL);

            }
        }
    }
    E encontrar(E e){}
    int longitud(){
        return this->tam;
    }


};


int main()
{
    ArbolBinarioNodo<int> *arbol= new ArbolBinarioNodo<int>;
    arbol->insertar(3);
    return 0;
}