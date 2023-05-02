//Modificação do exercicio 

#include <iostream>
#include <bits/stdc++.h>
#define C 0 //Execution
#define P 1 //Period
#define D 2 //Deadline
#define copia_exec 3
#define abs_D 4
#define abs_upd 5
#define old_exec 6
#define ESPERA_TASK_ID 9955
using namespace std;

class Task{
    private:
   
    public:
    
    int instancia,alive;
    int T[7]; //Armazena as caracteristicas da classe 
    void pegar_tarefas(Task *t1,int n);	
    float cpu_time(Task *t1,int n);	
    int interrup(Task *t1,int tmr,int n);	
    int minimo(Task *t1,int n,int p);		
    void update_internal_deadline(Task *t1,int n,int all);
    void copy_C_time(Task *t1,int n,int all);
    void update_internal_ini(Task *t1, int n, int k, int all);
};

 void Task::pegar_tarefas(Task *t1, int n) //A função cria e pega os dados das tasks
{
	int i = 0;
	while (i < n)
	{
		
		cin >> t1->T[C] >>  t1->T[P]  >> t1->T[D];	
		t1->T[copia_exec] = 0;
		t1->T[abs_D] = 0;
        t1->T[abs_upd] = 0;
		t1->instancia = 0;
		t1->alive = 0;
		t1++;
		i++;
	}
}

float Task::cpu_time(Task *t1,int n){    
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

int Task::interrup(Task *t1,int tmr,int n){
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

int Task::minimo(Task *t1,int n,int p){
    int i = 0, minimo = 0x7FFF, task_id = ESPERA_TASK_ID;
	while (i < n)
	{
		if (minimo > t1->T[p] && t1->alive == 1)
		{
			minimo = t1->T[p];
			task_id = i;
		}
		t1++;
		i++;
	}
	return task_id;

}	

void Task::update_internal_deadline(Task *t1,int n,int all){
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

void Task::update_internal_ini(Task *t1, int n, int k, int all)
{
	int i = 0;
	if (all)
	{
		while (i < n)
		{
			t1->T[abs_upd] = 0 + k * (t1->T[P]);
			t1++;
			i++;
		}
	}
	else
	{
		t1 += n;
		t1->T[abs_upd] = 0 + k * (t1->T[P]);
		
	}
}

void Task::copy_C_time(Task *t1,int n,int all){
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
 int N = 1, T= 1; //time_T e tasks_N
 int active_task_id = ESPERA_TASK_ID;
 int timer = 0;
 float tempo_de_compu;
 char taskNo;

 Task *task;
 int trocaContx, oldTask=-1;
int preemp = 0;
int already = 1;
	while(N != 0 || T !=0 ){		
		cin >> N >> T;
		trocaContx = 0;
		preemp = 0;
		task =(Task *) malloc(N * sizeof(Task));
		
		task->pegar_tarefas(task,N);
		tempo_de_compu = task->cpu_time(task,N);
	
		task->copy_C_time(task, N, 1);
		task->update_internal_ini(task, N, 0, 1);
		task->update_internal_deadline(task, N, 1);

		while (timer < T) 
		{

			if (task->interrup(task, timer, N))
			{				
			
				active_task_id = task->minimo(task, N, abs_D);
			
				
			}

			if (active_task_id == ESPERA_TASK_ID)
			{
				printf(".");
				trocaContx++;
			}

			if (active_task_id != ESPERA_TASK_ID)
			{

				if (task[active_task_id].T[copia_exec] != 0)
				{
					
					if(active_task_id + 1 != oldTask){
						trocaContx++;	
						if(task[oldTask].T[old_exec] != 0){
							preemp++;
						}	 
				
						
						
				}
					task[active_task_id].T[copia_exec]--;
					switch(active_task_id + 1) {
						case 1:
							taskNo = 'A';
						break;
						case 2:
							taskNo = 'B';
						break;
						case 3:
							taskNo = 'C';
						break;
						case 4:
							taskNo = 'C';
						break;
						default:
							taskNo = 'D';
	
					}
					printf("%c",  taskNo );
					oldTask = active_task_id + 1;
					task[oldTask].T[old_exec] = task[active_task_id].T[copia_exec];
				}

				if (task[active_task_id].T[copia_exec] == 0)
				{
					
					task[active_task_id].instancia++;
					task[active_task_id].alive = 0;
					task->copy_C_time(task, active_task_id, 0);
					task->update_internal_ini(task, active_task_id, task[active_task_id].instancia, 0);
					task->update_internal_deadline(task, active_task_id, 0);
					active_task_id = task->minimo(task, N, abs_D);
						
					
				}
			}
			++timer;
		}
			cout << endl;
		cout << trocaContx << " " << preemp << endl;
	
		if(tempo_de_compu <= 1){
			cout << fixed << setprecision(4) << tempo_de_compu << " OK" << endl;
		}
		else{
			cout << fixed << setprecision(4) << tempo_de_compu << " NOK" << endl;
		}
		
		free(task);
		timer = 0;
	}
	
    return 0;
}