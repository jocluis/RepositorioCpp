//
// Created by jcasiano on 27/6/2021.
// 3 Formas de generar el nùmero de Fibonacci F(n)
//

#include <iostream>
#include <chrono> //para uso de cronometro
#define N 100 // para la matriz de fibonacci_memoizado

using namespace std;


/* 1. Forma normal de generar el numero de fibonacci */
void fibonacci_normal(int n)
{
    //n= numero fibonacci pedido F(n)
    int contador=1;
    double x=0,y=1,z=1;
    while(contador<n)
    {
        z=x+y;
        x=y;
        y=z;
        contador=contador+1;
    }
    cout<<"Resultado F("<<n<<")="<<z<<endl;
}


/* 2. Forma recursiva de generar el numero de fibonacci */
long int fibonacci_recursivo(long int n)
{
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    return fibonacci_recursivo(n-1)+ fibonacci_recursivo(n-2);
}


/* 3. Forma memoizada/programacion dinamica de generar el numero de fibonacci */
const int NIL = -1;
int lookup_table[N];
void init()
{
    for(int i=0; i<N; i++)
        lookup_table[i] = NIL;
}
int fibonacci_memoizado(int n) {
    if(lookup_table[n] == NIL) {
        if(n <= 1)
            lookup_table[n] = n;
        else
            lookup_table[n] = fibonacci_memoizado(n-1) + fibonacci_memoizado(n-2);
    }
    return lookup_table[n];
}


int main()
{
    auto start = std::chrono::system_clock::now(); //Inicio cronometro

    //1.
    //fibonacci_normal(50); //Ejemplo1: Para F(50) -> 0.002104 segundos

    //2.
    //cout<<fibonacci_recursivo(50)<<endl; //Ejemplo2: Para F(50) -> 116.766 segundos

    //3.
    init();
    cout<<fibonacci_memoizado(50)<<endl;//Ejemplo3: F(50) -> 0.000995 segundos


    auto end = std::chrono::system_clock::now(); //Fin cronometro
    std::chrono::duration<double> elapsed_seconds = end-start; //calculo cronometro
    std::cout << "Tiempo de ejecucion: " << elapsed_seconds.count() << "s"<<endl; //Resultado del cronometro
}