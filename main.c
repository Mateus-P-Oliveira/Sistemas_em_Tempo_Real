/* edf.c */

#include <stdio.h>

#define MAX_N 26
#define MAX_T 100000

typedef struct {
	unsigned c;
	unsigned p;
	unsigned d;
} tarefa_t;

int main() {
	tarefa_t tarefas[MAX_N];
	unsigned n, t;
	
	while(1) {
		// Leitura
		scanf("%u %u", &n, &t);
		if (n == 0 || t == 0) break;
		for (int i=0; i<n; i++)
			scanf("%u %u %u", &tarefas[i].c, &tarefas[i].p, &tarefas[i].d);
		
		// Processamento
		char grade[MAX_T+1];
		unsigned t_atual = 0;
		grade[t_atual] = '\0';
		unsigned tr_contexto = 0, preemp = 0;
		double utilizacao = 0.0;
		// ...
		
		// Resultado
		printf("%s\n", grade);
		printf("%u %u\n", tr_contexto, preemp);
		printf("%.4lf %s\n\n", utilizacao, utilizacao<=1.0 ? "OK" : "NOK" );
	}
	return 0;
}










