//
// Created by jcasiano on 8/6/2021.
//

#include <iostream>


using namespace std;

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
};


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
    virtual E remover(Key K) = 0;


    //Remover y retornar un registro arbitrario del diccionario
    //Retornar: el registro que ha sido removido o NULL si no existe
    virtual E removerCualquiera() = 0;

    //Return: un registro o NULL si no existe
    //Si hay multiples registros, se debe retornar uno de manera aleatoria
    //K: la clave del registro a encontrar
    virtual E encontrar(Key K) = 0;

    //Retornar el numero de registros dentro del diccionario
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


template<typename Key, typename E> class DiccionarioArreglo : public Diccionario<Key, E>{
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

    //Remover y retornar un registro
    //k: la clave del registro que debe ser removido
    //Retornar: un registro. Si hay mas de un registro con la misma clave,
    //  se debe remover uno de manera arbitraria
    //Retornar NULL si la clave "K" no se encuentra en el diccionario
    E remover(Key K) {
        return "";
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
            return NULL;
        } else {
            return this->lista->getValor().valor();
        }
    };

    //Retornar el numero de registros dentro del diccionario
    int longitud() {
        int length = this->lista->longitud();
        return length;
    };
};
void ejemplo0()
{
    DiccionarioArreglo<int, string> *diccionario = new  DiccionarioArreglo<int, string>;
    diccionario->insertar(3912, "Luis");
    diccionario->insertar(2918, "Maria");
    diccionario->insertar(16881, "Juan");
    cout<<"Reportando Contenido de Diccionario"<<endl;
    cout<<"Elemento: "<<diccionario->encontrar(2918)<<endl;//reporta: Maria
    cout<<"Reportando Todos los elementos del Diccionario"<<endl;
    /*
    Reporta:
    Juan
    Maria
    Luis
    */
    while(diccionario->longitud()>0){
        cout<<diccionario->removerCualquiera()<<endl;
    }
}

/* Hash1 - Concatenación de idiomas
Sample Input 0
2
3 3
car
bar
baby
zar
bonus
city
2 2
bar
car
zar
day
Sample Output 0
Case 1: 9
Case 2: 4
 * */
void ejercicio1(){
    int T;
    cin>>T;
    for(int i=1;i<=T && T<=25;i++) //numeros de casos
    {

        int M,N;
        cin>>M;
        cin>>N;
        DiccionarioArreglo<int, string> *diccionarioA = new  DiccionarioArreglo<int, string>;
        DiccionarioArreglo<int, string> *diccionarioB = new  DiccionarioArreglo<int, string>;
        int j=0;
        for(j=0;j<M;j++)
        {
            string elemento;
            cin>>elemento;
            diccionarioA->insertar(j,elemento);
        }
        for(j=0;j<N;j++)
        {
            string elemento;
            cin>>elemento;
            diccionarioB->insertar(j,elemento);
        }
        DiccionarioArreglo<int, string> *diccionarioC = new  DiccionarioArreglo<int, string>;
        int contador=0;
        for(j=0;j<M;j++)
        {
            for(int k=0;k<N;k++)
            {
                diccionarioC->insertar(contador,diccionarioA->encontrar(j).append(diccionarioB->encontrar(k)));
                contador++;
            }
        }

        cout<<"Case "<<i<<": "<<diccionarioC->longitud()<<endl;
    }
}
/* Hash2 - CD
Sample Input 0
4 4
1
2
3
5
1
3
5
6
0 0
Sample Output 0
3
 * */
void ejercicio2()
{
    int N,M;
    cin>>N;
    cin>>M;
    DiccionarioArreglo<string, string> *diccionarioJack = new  DiccionarioArreglo<string, string>;
    DiccionarioArreglo<string, string> *diccionarioJill = new  DiccionarioArreglo<string, string>;
    int j=0;
    for(j=0;j<N;j++)
    {
        string elemento;
        cin>>elemento;
        diccionarioJack->insertar(elemento,elemento);
    }
    for(j=0;j<M;j++)
    {
        string elemento;
        cin>>elemento;
        diccionarioJill->insertar(elemento,elemento);
    }
    int casos=0;
    string valorencontraro="";
    while(diccionarioJill->longitud()>0)
    {
        valorencontraro=diccionarioJack->encontrar(diccionarioJill->removerCualquiera());
        if (!valorencontraro.empty()) casos++;
    }
    cout<<casos<<endl;

}
int main() {
    //ejemplo0();
    ejercicio1();
    //ejercicio2();


    return 0;
}
