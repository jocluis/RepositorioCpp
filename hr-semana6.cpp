//
// Created by jcasiano on 1/6/2021.
//

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>


using namespace std;

//Clase Padre: Pila
template<typename E> class Pila{
public:
    Pila(){}
    ~Pila(){}
    virtual void limpiar() = 0;
    virtual void push(E var) = 0;
    virtual E pop() = 0;
    virtual E valorTop() = 0;
    virtual int longitud() = 0;
};

//Clase hija: Pila Arreglo: Arreglo Pila (APila)
template<typename E> class APila : public Pila<E>{
private:
    E *arregloLista;
    int tamMaximo;
    int cima; //top
public:
    APila(int tam = 100){
        this->tamMaximo = tam;
        this->cima = 0;
        this->arregloLista = new E[this->tamMaximo];
    }

    ~APila(){
        delete[] this->arregloLista;
    }

    //En tiempo O(1): borrado logico
    void limpiar() {
        this->cima = 0;
    }

    //En tiempo O(1)
    void push(E elemento) {
        this->arregloLista[this->cima++] = elemento;
    }

    //En tiempo O(1): retorna el valor top y SI lo borra de la pila
    E pop() {
        return this->arregloLista[--this->cima];
    }

    //En tiempo O(1): retorna el valor top pero NO lo borra de la pila
    E valorTop() {
        return this->arregloLista[this->cima-1];
    }

    //En tiempo O(1)
    int longitud() {
        return this->cima;
    }
};

/* Stk04 - Anidacion de Bloques
 */
bool abierto(char c) {
    if (c == '(' || c == '[' || c == '<' || c == '{')
        return true;
    return false;
}

bool cerrado(char c) {
    if (c == ')' || c == ']' || c == '>' || c == '}')
        return true;
    return false;
}
vector<string> getStringVector(string s) {
    vector<string> res;
    char delimiter = ' ';
    size_t pos = 0;
    std::string token;

    if (s.find(delimiter) == std::string::npos) {
        res.push_back(s);
        return res;
    }

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + 1);
    }
    res.push_back(s);
    return res;
}
void run(string s) {

    APila<char> *pStack = new APila<char>();

    int count = 0;
    int len = s.size(), i;
    for (i = 0; i < len; i++) {
        count++;
        if (abierto(s[i])) {
            if (s[i] == '(' && s[i + 1] == '*') {
                pStack->push('*');
                i++;
            } else {
                pStack->push(s[i]);
            }
        } else if (cerrado(s[i]) || (s[i] == '*' && s[i + 1] == ')')) {
            if (pStack->longitud() == 0)
                break;
            if (s[i] == '*') {
                if (pStack->valorTop() != '*') {
                    break;
                }
                pStack->pop();
                i++;
            } else if (s[i] == ')') {
                if (pStack->valorTop() != '(') {
                    break;
                }
                pStack->pop();
            } else if (s[i] == ']') {
                if (pStack->valorTop() != '[') {
                    break;
                }
                pStack->pop();
            } else if (s[i] == '>') {
                if (pStack->valorTop() != '<') {
                    break;
                }
                pStack->pop();
            } else if (s[i] == '}') {
                if (pStack->valorTop() != '{') {
                    break;
                }
                pStack->pop();
            }
        }
    }

    if (i < len || pStack->longitud() > 0) {
        cout << "No " << count << ' ';
    } else
        cout << "YES ";

    while (pStack->longitud() > 0)
        pStack->pop();

    delete pStack;
}
void ejercicio2(){
    char input[100];
    cin.getline(input, sizeof(input));
    vector<string> t = getStringVector(input);
    for (auto &i : t) {
        run(i);
    }
}

void ejercicio1(){
    APila<string> *pila=new APila<string>();
    string N;
    int sleep;
    int kick;
    int test;
    getline(cin,N);
    for(int i=1;i<=stoi(N);i++)
    {
        string cadena;
        getline(cin,cadena);

        sleep=cadena.find("Sleep")+cadena.find("sleep");
        kick=cadena.find("Kick")+cadena.find("kick");
        test=cadena.find("Test")+cadena.find("test");
        if(sleep==-1) pila->push(cadena.substr(6));
        if(kick==-1 && pila->longitud()>0) pila->pop();
        if(test==-1)
        {
            if(pila->longitud()==0) cout<<"Not in a dream"<<endl;
            else cout<<pila->valorTop()<<endl;
            //cout<<"free"<<endl;
        }

    }
}

/*Inicio de la implementacion del ejercicio 4
 * */
const int maxn = 800;
int n, a[maxn][maxn];
struct Item {
    int s, b;
    Item(int s, int b) : s(s), b(b) {}
    bool operator < (const Item &rhs) const {
        return s > rhs.s;
    }
};
void juntar(int *x, int *y, int *z) {
    priority_queue<Item> q;
    for (int i = 0; i < n; i++) q.push(Item(x[i]+y[0], 0));
    for (int i = 0; i < n; i++)
    {
        Item item = q.top();
        q.pop();
        z[i] = item.s;
        int b = item.b;
        if (b + 1 < n) q.push(Item(item.s-y[b]+y[b+1], b+1));
    }
}
void ejercicio4()
{
        while (~scanf("%d", &n),n!=0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) scanf("%d", &a[i][j]);
                sort(a[i], a[i]+n);
            }
            for (int i = 1; i < n; i++)  juntar(a[0], a[i], a[0]);
            if(n!=0) printf("%d", a[0][0]);
            for (int i = 1; i < n; i++) printf(" %d", a[0][i]);
            printf("\n");
        }

}
/* Ejercicio 3
 * */
void ejercicio3(){
    int n, casos = 0;
    while (scanf("%d", &n) == 1 && n) {
        int A[32], B[32], C[32], D[32];
        int dormir = 0, despierta = 0, ciclo = 1;
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &A[i], &B[i], &C[i]);
            D[i] = A[i] + B[i];
            ciclo *= D[i];
        }
        int ret = -1;
        for (int time = 1; time <= ciclo; time++) {
            despierta = 0, dormir = 0;
            for (int i = 0; i < n; i++)
                if (C[i] <= A[i])
                    despierta++;
                else
                    dormir++;
            if (despierta == n) {
                ret = time;
                break;
            }
            for (int i = 0; i < n; i++) {
                C[i]++;
                if (C[i] == D[i] + 1) {
                    C[i] = 1;
                } else if (C[i] == A[i] + 1 && despierta >= dormir) {
                    C[i] = 1;
                }
            }
        }
        cout<<"Caso "<<++casos<<": "<<ret<<endl;
    }
}
int main() {

    ejercicio1();
    //ejercicio2();
    //ejercicio3();
    //ejercicio4();
    return 0;
}