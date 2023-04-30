//Modificação do exercicio 
//https://github.com/jabezwinston/Earliest_Deadline_First
#include <iostream>
#define C 0 //Execution
#define P 1 //Period
#define D 2 //Deadline
#define copia_exec 3
#define abs_D 4
#define abs_upd 5

using namespace std;

class Task{
    private:
   
    public:
    
    int instance,alive; //Talvez mude dps
    int T[6]; //Armazena as caracteristicas da classe 
    void get_tasks(Task *t1,int n);	
    float cpu_util(Task *t1,int n);	
    int sp_interrupt(Task *t1,int tmr,int n);	
    int min(Task *t1,int n,int p);		
    void update_abs_deadline(Task *t1,int n,int all);
    void copy_execution_time(Task *t1,int n,int all);
    void update_abs_arrival(Task *t1, int n, int k, int all);
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
		t1->T[copia_exec] = 0;
		t1->T[abs_D] = 0;
        t1->T[abs_upd] = 0;
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

int Task::sp_interrupt(Task *t1,int tmr,int n){
    int i = 0, n1 = 0, a = 0; //I é só contador
	Task *t1_copy;
	t1_copy = t1;
	while (i < n)
	{
		if (tmr == t1->T[abs_upd]) //Se o timer for igual ao valor da chegada absoluta da task ele diz que a task esta viva //Isso inicia as tasks
		{
			t1->alive = 1;
			a++;
		}
		t1++;
		i++;
	}

	t1 = t1_copy;
	i = 0;

	while (i < n)
	{
		if (t1->alive == 0)
			n1++;
		t1++;
		i++;
	}

	if (n1 == n || a != 0)
	{
		return 1;
	}

	return 0;



}

int Task::min(Task *t1,int n,int p){
    int i = 0, min = 0, task_id = 9595;
	while (i < n)
	{
		if (min > t1->T[p] && t1->alive == 1)
		{
			min = t1->T[p];
			task_id = i;
		}
		t1++;
		i++;
	}
	return task_id;

}	

void Task::update_abs_deadline(Task *t1,int n,int all){
    int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[abs_D] = t1->T[D] + t1->T[abs_upd];
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_D] = t1->T[D] + t1->T[abs_upd];
	}


}

void Task::update_abs_arrival(Task *t1, int n, int k, int all)
{
	int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[abs_upd] = 1 + k * (t1->T[P]);
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_upd] = 1 + k * (t1->T[P]);
	}
}

void Task::copy_execution_time(Task *t1,int n,int all){
    	int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[copia_exec] = t1->T[C];
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[copia_exec] = t1->T[C];
	}



}


int main(){
 int N, T; //time_T e tasks_N
 int active_task_id;
 int timer = 0;
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

    while (timer <= T) //Aqui processa as tasks a serem feitea //O meu hyper_period é o T 
	{

		if (task->sp_interrupt(task, timer, N))
		{
            cout << "OI" << endl;
			active_task_id = task->min(task, N, abs_D);
            cout << active_task_id << endl;
		}

		if (active_task_id == 9595)
		{
			printf("%d  Idle\n", timer);
		}

		if (active_task_id != 9595)
		{

			if (task[active_task_id].T[copia_exec] != 0)
			{
				task[active_task_id].T[copia_exec]--;
				printf("%d  Task %d\n", timer, active_task_id + 1);
			}

			if (task[active_task_id].T[copia_exec] == 0)
			{
				task[active_task_id].instance++;
				task[active_task_id].alive = 0;
				task->copy_execution_time(task, active_task_id, 0);
				task->update_abs_arrival(task, active_task_id, task[active_task_id].instance, 0);
				task->update_abs_deadline(task, active_task_id, 0);
				active_task_id = task->min(task, N, abs_D);
			}
		}
		++timer;
	}

    return 0;

}