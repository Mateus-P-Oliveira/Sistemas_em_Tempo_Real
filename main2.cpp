//Modificação do exercicio 
#include <iostream>

using namespace std;

class Task{
    private:
    char id;
    int computation, period, deadline;

//
    //public:



};

class TaskRunning{
    private:
    int time_T, tasks_N;
};


int main(){
 int N, T; //time_T e tasks_N
 int priority = 0; 
 int c, p, d;
    while(N != 0 && T !=0){
        cin >> N;
        cin >> T;
        cin >> c;
        cin >> p; // Refazer essa parte
        cin >> d;
        if(N != 0 && T !=0){
            for(int i = 0; i < N; i++){
                int i_c, i_p, i_d;
                i_c = c;
                i_p = p;
                i_d = d;
                priority++;
                //Passa dados para a classe Task

            }
            cout << c << p << d << endl;
             cout << priority << endl;
            //Executa Tasks de teste
        }
        priority = 0;
    }

    cout << priority << endl;

    return 0;

}