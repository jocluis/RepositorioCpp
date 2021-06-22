#include "PilasArreglo.cpp"
using namespace std;


void ejercicioPila1() {
    APila<int> *pila = new APila<int>();
    pila->push(10);
    pila->push(20);
    pila->push(30);
    pila->push(40);
    cout<<"Pila ahora tiene: "<<pila->longitud()<<" elementos"<<endl;
    while(pila->longitud()>0){
        cout<<pila->pop()<<endl;
    }
    cout<<"Pila ahora tiene: "<<pila->longitud()<<" elementos"<<endl;
    delete pila;
}

void ejercicioMayor(){
    APila<int> *pila=new APila<int>();
    pila->push(10);
    pila->push(20);
    pila->push(30);
    pila->push(40);
    cout<<"Pila ahora tiene: "<<pila->longitud()<<" elementos"<<endl;
    int mayor=0;
    while(pila->longitud()>0){
        if(pila->valorTop()>mayor)
        {
            mayor=pila->valorTop();
        }
        pila->pop();
    }

    cout<<"El numero mayor es: "<<mayor<<endl;

}
void ejercicioMenor(){
    APila<int> *pila=new APila<int>();
    pila->push(10);
    pila->push(20);
    pila->push(30);
    pila->push(40);
    cout<<"Pila ahora tiene: "<<pila->longitud()<<" elementos"<<endl;
    int menor=pila->valorTop();
    while(pila->longitud()>0){
        if(pila->valorTop()<menor)
        {
            menor=pila->valorTop();
        }
        pila->pop();
    }

    cout<<"El numero menor es: "<<menor<<endl;

}
void ejercicio2(){ //obtner el menor valor de una pila
    APila<int> *pila=new APila<int>();
    int cantidad;
    cin>>cantidad;

    for(int i=0;i<cantidad;i++)
    {
        int valor;
        cin>>valor;
        pila->push(valor);
    }

    cout<<"Pila ahora tiene: "<<pila->longitud()<<" elementos"<<endl;
    int menor=pila->valorTop();
    while(pila->longitud()>0){
        if(pila->valorTop()<menor)
        {
            menor=pila->valorTop();
        }
        pila->pop();
    }

    cout<<"El numero menor es: "<<menor<<endl;

}

int main() {
    ejercicioPila1();
    //ejercicioMayor();
    //ejercicioMenor();
    //ejercicio2();
    return 0;
}
