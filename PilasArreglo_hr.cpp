//
// Created by jcasiano on 15/6/2021.
// Problemas a resolver en hackerrank para pilas
//

#include "PilasArreglo.cpp"
#include <vector>
using namespace std;

/* Problema de rieles
 *
Sample Input 0
4
4 3 2 1
1 2 4 3
0
5
1 2 3 4 5
1 5 4 2 3
0
0
Sample Output 0
SI
SI
SI
NO

 * */

void problema1_Rieles(){
    int N;
    while(cin>>N,N>0)
    {
        int arr[N];
        while(cin>>arr[0],arr[0]>0)
        {
            for(int i=1;i<N;i++)
            {
                cin>>arr[i];
            }
            //solucion
            APila<int> *si=new APila<int>();
            int contador = 0;
            bool validador = false;
            for(int i = 1;i<=N;i++) {
                si->push(i);
                if(si->valorTop()==arr[contador]) {
                    si->pop();
                    contador++;
                    validador = true;
                }
                while(validador) {
                    if(si->longitud()>0 && si->valorTop()==arr[contador]) {
                        si->pop();
                        contador++;
                    }
                    else validador = false;
                }
            }
            if(si->longitud()>0) puts("NO");
            else puts("SI");
            //fin solucion
            delete si;
        }
    }
}

/* Stk02 - Contenedores
 *
Sample Input 0
CCBBBBBAA
AAABBBCCCC
BBBCCAAA
FIN
Sample Output 0
Caso 1: 1
Caso 2: 3
Caso 3: 2

 * */

void problema2_Contenedores(){
    string cadena; //cadena input
    bool valida=false;
    int contador=1;
    vector <APila<char>> v;//creando un vector de pilas
    APila<char> *si;

    while (getline(cin, cadena),"FIN"!=cadena && cadena.size()<=1000)
    {
        si=new APila<char>();
        si->push(cadena[0]);
        v.push_back(*si);
        si->pop();
        for(int i=1;i<cadena.size();i++)
        {
            valida=false;
            for(int j=0;j<v.size();j++){
                if(cadena[i]<=v[j].valorTop()){
                    v[j].push(cadena[i]);
                    valida=true;
                    break;
                }
            }
            if(!valida){
                si->push(cadena[i]);
                v.push_back(*si);
                si->pop();
            }
        }
        cout << "Caso " << contador << ": " << v.size() << endl;
        contador++;
        v.clear();
    }
    delete si;//eliminando pila
}

int main() {
    //problema1_Rieles();
    problema2_Contenedores();
    return 0;
}
