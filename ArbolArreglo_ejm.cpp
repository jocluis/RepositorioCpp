//
// Created by jcasiano on 20/6/2021.
//

#include "ArbolArreglo.cpp"

using namespace std;

void ejemploArbol()
{
    ArbolBinarioArreglo<int> *arbol = new ArbolBinarioArreglo<int>;

    // 13, 7, 15, 20, 22, 9, 6, 14, 19
    arbol->insertar(13);
    arbol->insertar(7);
    arbol->insertar(15);
    arbol->insertar(20);
    arbol->insertar(22);
    arbol->insertar(9);
    arbol->insertar(6);
    arbol->insertar(14);
    arbol->insertar(19);

    arbol->imprimirArreglo();
}
void problema2()
{
    int dato;
    ArbolBinarioArreglo<int> *arbol = new ArbolBinarioArreglo<int>;

    while(cin>>dato,dato!=-1)
    {
        arbol->insertar(dato);
    }
}

int main()
{

    //ejemploArbol();
    problema2();

    return 0;
}


