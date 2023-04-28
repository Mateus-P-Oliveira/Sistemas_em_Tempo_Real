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
 Task task1;
    cin >> N;
    cin >> T;
    if(N != 0 && T !=0){
    for(int i = 0; i < N; i++){ //Se o numero de tarefas não for zero e não tiver o tempo O
       
        cin >> c;
        cin >> p; // Refazer essa parte
        cin >> d;
                    
         int i_c, i_p, i_d;
         i_c = c;
         i_p = p;
         i_d = d;
         

            
         cout << c << p << d << endl;
         cout << priority << endl;
            //Executa Tasks de teste
        }
       
    }


    cout << priority << endl;

    return 0;

}