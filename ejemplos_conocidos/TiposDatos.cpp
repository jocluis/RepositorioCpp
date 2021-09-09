//
// Created by jcasiano on 30/6/2021.
//

#include <iostream>
#include<typeinfo>
using namespace std;


template<typename E> class Clase{
private:
    E elemento;
    string tipo;
public:
    Clase(E e){
        elemento = e;
        tipo = typeid(elemento).name();
        cout<<"En la clase se detectó tipo: ";
        cout<<tipo<<endl;
    }
};

int main() {
    //Código ASCII
    char c = 'A';
    char c2 = 'B';
    int n = c-64;
    int n2 = c2-64;
    cout<<c<<"="<<n<<endl;
    cout<<c2<<"="<<n2<<endl;
    //Detección de Tipo de Dato
    cout<<"Detección de Tipo de Datos"<<endl;
    string cadena = "hola";
    cout<< typeid(cadena).name()<<endl;
    string cadena2 = "mundo";
    cout<< typeid(cadena2).name()<<endl;
    int numero1 = 256;
    cout<< typeid(numero1).name()<<endl;
    int numero2 = 588;
    cout<< typeid(numero2).name()<<endl;
    double numero3 = 58.88;
    cout<< typeid(numero3).name()<<endl;
    double numero4 = 158.488;
    cout<< typeid(numero4).name()<<endl;
    char ac = 'c';
    char bc = 'c';
    cout<< typeid(ac).name()<<endl;
    cout<< typeid(bc).name()<<endl;

    Clase<int> *clase1 = new Clase<int>(13);
    delete clase1;

    Clase<string> *clase2 = new Clase<string>("hola mundo");
    delete clase2;

    string var = "B9FCuygAKjE17856560683785213";
    cout<<"Imprimiendo caracter por caracter de una cadena"<<endl;
        for(char c : var){
            cout<<"C:"<<c<<endl;
            int entero=c;
            cout<<"en ascii: "<<entero<<endl;
        }


    return 0;
}
