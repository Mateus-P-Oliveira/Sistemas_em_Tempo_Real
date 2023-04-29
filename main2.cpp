//Modificação do exercicio 
//https://github.com/jabezwinston/Earliest_Deadline_First
#include <iostream>
#define C 0 //Execution
#define P 1 //Period
#define D 2 //Deadline
#define copia_exec 3
#define abs_D 4


using namespace std;

class Task{
    private:
    int T[5]; //Armazena as caracteristicas da classe 
    int instance,alive; //Talvez mude dps
    public:
    void get_tasks(Task *t1,int n);	
    float cpu_util(Task *t1,int n);	
    int sp_interrupt(Task *t1,int tmr,int n);	
    int min(Task *t1,int n,int p);		
    void update_abs_deadline(Task *t1,int n,int all);
    void copy_execution_time(Task *t1,int n,int all);
};

 void Task::get_tasks(Task *t1, int n) //A função cria e pega os dados das tasks
{
	int i = 0;
	while (i < n)
	{
		printf("Enter Task %d parameters\n", i + 1);
		printf("Execution time: ");
		cin >> t1->T[C];
		printf("Deadline time: ");
		cin >> t1->T[D];
		printf("Period: ");
		cin >>  t1->T[P];
		//t1->T[abs_arrival] = 0; //O T esta na h file
		//t1->T[execution_copy] = 0;
		//t1->T[abs_deadline] = 0;
		t1->instance = 0;
		t1->alive = 0;
		t1++;
		i++;
	}
}

float Task::cpu_util(Task *t1,int n){    
	int i = 0;
	float cu = 0;
	while (i < n)
	{
		cu = cu + (float)t1->T[C] / (float)t1->T[D];
		t1++;
		i++;
	}
	return cu;


}	

int main(){
 int N, T; //time_T e tasks_N
 float tempo_de_compu;
 //int priority = 0; 
 //int c, p, d;
 Task *task;
    cin >> N;
    task =(Task *) malloc(N * sizeof(Task));
    cin >> T;
    task->get_tasks(task,N);
    tempo_de_compu = task->cpu_util(task,N);
    cout << tempo_de_compu << endl;
    
    /*if(N != 0 && T !=0){
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


    cout << priority << endl;*/

    return 0;

}