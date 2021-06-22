//
// Created by jcasiano on 15/6/2021.
//

#include "ListaEnlazada.cpp"

using namespace std;

void casoListaEnlazada()
{
    ListaEnlazada<int> *lista = new ListaEnlazada<int>();
    lista->agregar(10); // agregar al final de la lista (nueva cola)
    lista->agregar(18);
    lista->insertar(15); // inserta en la posicion actual
    //Retornar: 0
    // cout << "Posicion actual:" << lista->posicionActual() << endl;
    /*Reportar:
     * Nodo: 15
     * Nodo: 10
     * Nodo: 18
     * */
    cout << "Los datos del nodo son:"  << endl;
    for (lista->moverAInicio(); lista->posicionActual() < lista->longitud(); lista->siguiente())
    {
        cout << "Nodo: [" << lista->posicionActual() << "] = " << lista->getValor() << endl;
    }

    /*Reporte inverso:
     * Nodo: 18
     * Nodo: 10
     * Nodo: 15
     * */
    cout << "Los datos del nodo invertido son:"  << endl;

    int i = 0;
    for (i = 0, lista->moverAlFinal(), lista->anterior(); i < lista->longitud(); lista->anterior(), i++)
    {
        cout << "Nodo: [" << lista->posicionActual() << "] = " << lista->getValor() << endl;
    }

    /*Reporte inverso:
     * Nodo: 18
     * Nodo: 10
     * Nodo: 15
     * */
    // for (lista->moverAlFinal(); lista->posicionActual() >= 0; lista->anterior())
    // {
    //     cout << "Posicion actual:" << lista->posicionActual() << endl;
    //     cout << "Nodo: " << valor << endl;
    // }
}

int main()
{
    casoListaEnlazada();
    return 0;
}


