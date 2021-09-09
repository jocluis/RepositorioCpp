//
// Created by jcasiano on 22/7/2021.
//

#include <iostream>
#include <queue>

using namespace std;

/***Inicio de Estructura Cola*/

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
    }

};

/***Fin de estructura Cola*/

/*Inicio de Grafo*/
class Grafo{
private:
public:
    //Constructor
    Grafo(){}
    //Metodo de inicializacion
    virtual void init(int n,char tipoGrafo) = 0;
    //Retornar el numero de vertices y aristas
    virtual int get_N_Vertices()=0;
    virtual int get_N_Aristas()=0;
    //Retornar el primer vecino
    virtual int primero(int v) = 0;
    //Retornar el siguiente vecino
    virtual int siguiente(int v, int w) = 0;
    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    virtual void setArista(int i, int j, int w) = 0;
    //Eliminar arista
    virtual void eliminarArista(int i, int j) = 0;
    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    virtual bool esArista(int i, int j) = 0;
    //Retornar el peso de una arista
    virtual int getPeso(int i, int j) = 0;
    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    virtual int getMarca(int v) = 0;
    virtual void setMarca(int v, int val) = 0;
};

//Implementacion usando representacion de matriz de adyacencia
class GrafoMA : public Grafo{
private:
    int numeroVertices;
    int numeroAristas;
    int **matriz;//matriz de ady
    int *marca; // vertices visitados
    int *distancia; //distancia entre nodos adyancentes
    char tipoGrafo;//Grafo Dirigido o No dirigido  N:No dirigido / D: Dirigido
public:
    //Metodo de inicializacion: inicializar la matriz
    void init(int n,char tipoGrafo) {
        int i,j;
        this->numeroVertices = n;
        this->numeroAristas = 0;
        this->marca = new int[n];
        this->distancia = new int[n];
        this->tipoGrafo = tipoGrafo;//N:No dirigido / D: Dirigido

        //Inicializamos el arreglo de marca (vertices visitados)
        for (i = 0; i < this->numeroVertices; i++) {
            this->marca[i] = 0; //NO VISITADO
        }
        //Inicializamos el arreglo de distancia (distancia entre nodos adyancentes) nivel profundidad
        for (i = 0; i < this->numeroVertices; i++) {
            this->distancia[i] = -1; //NO VISITADO
        }
        //Inicializar la matriz de adyacencia
        this->matriz = new int*[this->numeroVertices];
        for (i = 0; i < this->numeroVertices; i++) {
            this->matriz[i] = new int[this->numeroVertices];
        }
        //Debemos colocar a la matriz con valores CERO
        for (i = 0; i < this->numeroVertices; i++) {
            for (j = 0; j < this->numeroVertices; j++) {
                this->matriz[i][j] = 0; //Peso CERO
            }
        }
    }

    GrafoMA(int numVert,char tipoGrafo){
        this->init(numVert,tipoGrafo);
    }

    ~GrafoMA(){
        delete[] this->marca;
        delete[] this->matriz;
    }

    //Retornar el numero de vertices y aristas
    int get_N_Vertices(){
        return this->numeroVertices;
    }

    int get_N_Aristas(){
        return this->numeroAristas;
    }

    //Retornar el primer vecino de v
    int primero(int v) {
        for (int i = 0; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Retornar el siguiente vecino
    int siguiente(int v, int w) {
        for (int i = w+1; i < this->numeroVertices; ++i) {
            if(this->matriz[v][i]!=0){
                return i;
            }
        }
        return this->numeroVertices;
    }

    //Cambiar el peso de las aristas
    // i, j: los vertices
    // w: peso
    void setArista(int i, int j, int w) {
        this->matriz[i][j] = w;
        if(this->tipoGrafo == 'N')
            this->matriz[j][i] = w;

    }

    //Eliminar arista
    void eliminarArista(int i, int j) {
        this->matriz[i][j] = 0;
    }

    //Determinar si una arista esta en el grafo
    //i, j: los vertices
    //retorna: true si la arista existe, y false en caso contrario
    bool esArista(int i, int j) {
        return this->matriz[i][j] != 0;
    }

    //Retornar el peso de una arista
    int getPeso(int i, int j) {
        return this->matriz[i][j];
    }

    //Valores de marca para cada nodo o vertice
    //v: el vertice
    //val: el valor a modificar
    int getMarca(int v) {
        return this->marca[v];
    }

    void setMarca(int v, int val) {
        this->marca[v] = val;
    }
    void bfs_cMarca(int s)
    {
        queue<int> *q=new queue<int>();
        q->push(s);
        setMarca(s,1);//visitado valor 1

        int actual,siguiente,i;
        while(!q->empty())
        {
            actual=q->front();
            q->pop();
            cout <<"-"<<actual<<endl;
            for(i=0;i<this->numeroVertices;i++)
            {
                if(this->matriz[actual][i]!=0 && this->getMarca(i)==0)
                {
                    setMarca(i,1);
                    q->push(i);
                }
            }
        }
    }

    void bfs_cNiveles(int s)
    {
        queue<int> *q=new queue<int>();
        q->push(s);
        this->distancia[s] = 0;
        int actual,i;
        while(!q->empty())
        {
            actual=q->front();
            q->pop();
            for(i=0;i<this->numeroVertices;i++)
            {
                if(this->matriz[actual][i]!=0 && this->distancia[i]==-1)
                {
                    this->distancia[i] = this->distancia[actual]+1;
                    q->push(i);
                }
            }
        }

        for (int i=0; i<this->numeroVertices;i++)
            cout<<"distancia: "<<this->distancia[i]<<endl;
    }



    void bfs_cRuta(int s,int f)
    {
        ACola<int> *q=new ACola<int>();
        q->encolar(s);
        this->distancia[s] = 0;
        int actual,i,longRuta=0;
        while(q->longitud()>0)
        {
            actual=q->valorFrontal();
            q->desencolar();
            for(i=0;i<this->numeroVertices;i++)
            {
                if(this->matriz[actual][i]!=0 && this->distancia[i]==-1)
                {
                    this->distancia[i] = this->distancia[actual]+1;
                    q->encolar(i);
                }
            }
        }

        //for (int i=0; i<this->numeroVertices;i++)
        //cout<<"distancia["<<i<<"]: "<<this->distancia[i]<<endl;

        if(distancia[f]!=-1) {
            ACola<int> *ruta = new ACola<int>();
            ruta->encolar(f);
            int nivelTop=distancia[f];
            while(nivelTop>0)
            {
                //cola temporal para obtener aristas unidas al top
                ACola<int> *temp = new ACola<int>();
                for(int i=0;i<f;i++)
                {
                    if(distancia[i]==nivelTop-1)
                    {
                        if(this->matriz[i][f]>0 || this->matriz[f][i]>0)
                        {
                            //cout<<"esta conectado con: "<<i<<"Nivel: "<<nivelTop-1<<endl;
                            longRuta+=this->matriz[i][f];
                            ruta->encolar(i);
                            f=i;
                            break;
                        }
                    }
                }
                nivelTop--;
            }
            cout<<"La ruta es: ";
            while(ruta->longitud()>0)
            {
                cout<<ruta->desencolar()<<" ";
            }
            cout<<endl;
            cout<<"Con una longuitud de: "<<longRuta<<endl;
            delete ruta;
            delete q;
        }else
            cout <<"No existe una ruta para los vertices seleccionados"<<endl;
    }

    /*
    void bfs_cRuta(int s,int f)
    {
        queue<int> *q=new queue<int>();
        q->push(s);
        this->distancia[s] = 0;
        int actual,i;
        while(!q->empty())
        {
            actual=q->front();
            q->pop();
            for(i=0;i<this->numeroVertices;i++)
            {
                if(this->matriz[actual][i]!=0 && this->distancia[i]==-1)
                {
                    this->distancia[i] = this->distancia[actual]+1;
                    q->push(i);
                }
            }
        }

        //for (int i=0; i<this->numeroVertices;i++)
            //cout<<"distancia["<<i<<"]: "<<this->distancia[i]<<endl;

        if(distancia[f]!=-1)
        {
            queue<int> *ruta=new queue<int>();
            ruta->push(f);
            int nivelTop=distancia[f];

            while(nivelTop>0)
            {
                for(int i=0;i<f;i++)
                {
                    if(distancia[i]==nivelTop-1)
                    {
                        if(this->matriz[i][f]>0 || this->matriz[f][i]>0)
                        {
                            //cout<<"esta conectado con: "<<i<<endl;
                            ruta->push(i);
                            f=i;
                            break;
                        }
                    }
                }
                nivelTop--;
            }
            cout<<"La ruta es: ";
            while(!ruta->empty())
            {
                cout<<ruta->front()<<" ";
                ruta->pop();
            }
        }else
            cout <<"No existe una ruta para los vertices seleccionados"<<endl;
    }

     */

    void dijkstra(int s,int f)
    {

    }
    void imprimiMatriz()
    {
        for(int i=0;i<this->numeroVertices;i++)
            for(int j=0;j<this->numeroVertices;j++)
                cout<<"matriz["<<i<<"]["<<j<<"]="<<this->matriz[i][j]<<endl;
    }
};

int main() {
    GrafoMA *grafo = new GrafoMA(7,'N');
    grafo->setArista(0,1, 1);
    grafo->setArista(0,2, 4);
    grafo->setArista(0,5, 3);
    grafo->setArista(1,2, 5);
    grafo->setArista(2,5, 7);
    grafo->setArista(5,6, 8);
    grafo->setArista(3,4, 2);

    //grafo->imprimiMatriz();

    grafo->bfs_cRuta(0,6);


    delete grafo;
    return 0;
}
