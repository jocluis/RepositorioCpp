//
// Created by jcasiano on 15/6/2021.
//

#include "ListaArreglo.cpp"

using namespace std;

void casoInsertar(){
    ListaArreglo<int> *lista = new ListaArreglo<int>();
    lista->agregar(18);//agregar en la ultima posicion
    lista->agregar(23);
    lista->agregar(25);
    lista->moverAPosicion(1);
    lista->insertar(38);//insertar en una posicion dada

    //Reportar
    /*
     * Deberia reportar:
     * 18
     * 38
     * 23
     * 25
     * */
    for(lista->moverAInicio(); //Inicializacion
        lista->posicionActual()<lista->longitud(); //Condicion de parada
        lista->siguiente()){ //Incremento

        cout<<"Elemento: "<<lista->getValor()<<endl;

    }
    delete lista;
}

void casoEliminar(){
    ListaArreglo<int> *lista = new ListaArreglo<int>();
    lista->agregar(18);
    lista->agregar(23);
    lista->agregar(25);
    lista->moverAPosicion(1);
    lista->insertar(38); //insertar en una posicion dada
    int eliminado = lista->eliminar();

    cout<<"Eliminado:"<<eliminado<<" en posicion actual = "<<lista->posicionActual()<<endl;

    //Reportar
    /*
     * Deberia reportar:
     * 18
     * 23
     * 25
     * */
    for(lista->moverAInicio(); //Inicializacion
        lista->posicionActual()<lista->longitud(); //Condicion de parada
        lista->siguiente()){ //Incremento

        cout<<"Elemento: "<<lista->getValor()<<endl;

    }
    delete lista;
}


int main ()
{
    cout<<"1. Caso Insertar"<<endl;
    casoInsertar();
    cout<<endl<<endl;
    cout<<"2. Caso Eliminar"<<endl;
    casoEliminar();
    return 0;

}