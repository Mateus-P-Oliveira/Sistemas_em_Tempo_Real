/*
 * main.c
 *
 *  Created on: 27-Jan-2016
 *      Author: winston
 */
#include <stdio.h>
#include "edf.h"




//Something like a Timer in a Microcontroller
int timer = 0;

int main()
{
	task *t; //Struct dela ta no edf.h
	int n, hyper_period, active_task_id;
	float cpu_utilization;
	printf("Enter number of tasks\n"); //Isso é o meu N
	scanf("%d", &n);
	t = malloc(n * sizeof(task)); //Crio e aloco novas tasks e coloco na lista
	get_tasks(t, n); //Pego  as tasks feitas e o numero delas e mando para a func_def
	cpu_utilization = cpu_util(t, n); //Teste de escanabilidade
	printf("CPU Utilization %f\n", cpu_utilization);

	if (cpu_utilization < 1)
		printf("Tasks can be scheduled\n");
	else
		printf("Schedule is not feasible\n");

	hyper_period = hyperperiod_calc(t, n);
	copy_execution_time(t, n, ALL);
	update_abs_arrival(t, n, 0, ALL);
	update_abs_deadline(t, n, ALL);

	while (timer <= hyper_period) //Aqui processa as tasks a serem feitea //O meu hyper_period é o T 
	{

		if (sp_interrupt(t, timer, n))
		{
			active_task_id = min(t, n, abs_deadline);
		}

		if (active_task_id == IDLE_TASK_ID)
		{
			printf("%d  Idle\n", timer);
		}

		if (active_task_id != IDLE_TASK_ID)
		{

			if (t[active_task_id].T[execution_copy] != 0)
			{
				t[active_task_id].T[execution_copy]--;
				printf("%d  Task %d\n", timer, active_task_id + 1);
			}

			if (t[active_task_id].T[execution_copy] == 0)
			{
				t[active_task_id].instance++;
				t[active_task_id].alive = 0;
				copy_execution_time(t, active_task_id, CURRENT);
				update_abs_arrival(t, active_task_id, t[active_task_id].instance, CURRENT);
				update_abs_deadline(t, active_task_id, CURRENT);
				active_task_id = min(t, n, abs_deadline);
			}
		}
		++timer;
	}
	free(t);
	return 0;
}