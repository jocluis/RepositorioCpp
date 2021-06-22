//
// Created by jcasiano on 19/6/2021.
//

#include <iostream>

using namespace std;


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
    Nodo<E *> *arbol; //arbol;
    int tam;//elementos que realmente estan dentro del arbol binario

public:
    ArbolBinarioNodo(){
        inicializar();
    }
    ~ArbolBinarioNodo(){
        eliminarTodo();
    }
    void inicializar()
    {
        this->arbol =new Nodo<E *>;
        this->tam=0;
    }
    void eliminarTodo()
    {
        if(this->arbol->derecha == NULL && this->arbol->izquierda == NULL)
        {
            delete arbol;
        }
        else
        {
            delete arbol->derecha;
            delete arbol->izquierda;
            delete arbol;
        }
    }
    //Limpiar el arbol: dejarla vacia el arbol
    void limpiar()
    {
        eliminarTodo();
        inicializar();
    }
    void insertar(E e)
    {
        insertar(this->arbol,e); //metodo recursivo
    }
    void insertar(Nodo<E*> *&arbolNodo, E e)
    {
        if(arbolNodo->derecha == NULL && arbolNodo->izquierda == NULL && arbolNodo->elemento== NULL)
        {
            arbolNodo->elemento = new E(e);
            arbolNodo->derecha = new Nodo<E *>;
            arbolNodo->izquierda = new Nodo<E *>;
            this->tam++;
        }
        else
        {
            int raiz_tmp= *arbolNodo->elemento;
            int e_tmp= e;
            if(e_tmp < raiz_tmp) //izquierda (menores que la raiz)
            {
                insertar(arbolNodo->izquierda,e);
            }
            else //derecha (mayores que la raiz)
            {
                insertar(arbolNodo->derecha,e);
            }
        }
    }
    E encontrar(E e){
        bool encontrado=false;
        encontrado=encontrar(this->arbol,e); //metodo recursivo
        if(encontrado) return e;
        else return -1; //no encontrado
    }
    bool encontrar(Nodo<E*> *&arbolNodo, E e)
    {
        if(arbolNodo->derecha == NULL && arbolNodo->izquierda == NULL && arbolNodo->elemento== NULL)
        {
            return false;
        }
        else
        {
            int raiz_tmp= *arbolNodo->elemento;
            int e_tmp= e;
            if(e_tmp <= raiz_tmp) //izquierda (menores que la raiz)
            {
                if(e_tmp == raiz_tmp) return true;
                encontrar(arbolNodo->izquierda,e);
            }
            else //derecha (mayores que la raiz)
            {
                encontrar(arbolNodo->derecha,e);
            }
        }
    }
    int longitud(){
        return this->tam;
    }
};


int main()
{
    /*Se inserta un arbol
     *                      13
     *              7                15
     *      6           9       14          20
     *                                  19         22
     * */
    ArbolBinarioNodo<int> *arbol= new ArbolBinarioNodo<int>;
    arbol->insertar(13);
    arbol->insertar(7);
    arbol->insertar(15);
    arbol->insertar(20);
    arbol->insertar(22);
    arbol->insertar(9);
    arbol->insertar(6);
    arbol->insertar(14);
    arbol->insertar(19);

    cout<<"Se ingresaron correctamente los datos."<<endl<<endl;
    cout<<"El arbol contiene el valor 22: Valor encontrado: "<<arbol->encontrar(22)<<endl;




    delete arbol;

    return 0;
}