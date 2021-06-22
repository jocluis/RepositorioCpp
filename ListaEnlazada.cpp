//
// Created by jcasiano on 14/6/2021.
//

#include <iostream>

using namespace std;

//ini - Nodo (creacion de una estructura nodo)
template <typename E>
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
//fin - Nodo

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
            return -1;
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

Nodo<int *> *findNesimoNodo(Nodo<int *> *cabeza, int n_esimo, int &i)
{
    if (cabeza == NULL)
        return NULL;

    Nodo<int *> *nodo = findNesimoNodo(cabeza->siguiente, n_esimo, i);
    i++;

    if (i == n_esimo)
        return cabeza;

    return nodo;
}

Nodo<int *> *getNesimoNodo(ListaEnlazada<int> *lista, int n_esimo)
{
    int i = 0;
    Nodo<int *> *nodo = lista->getCabezaNodo();
    return findNesimoNodo(nodo, n_esimo, i);
}


/*
int main()
{
    return 0;
}
 */

//Las tildes han sido omitidas intencionalmente