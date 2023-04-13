// Cpu.cpp (Roland Teodorowitsch; 30 ago. 2022)

#include <iostream>

using namespace std;

class Cpu {
private:
	int pid;
	char symbol;
	int numPreemp;
	int numContSwitch;
	string grid;
	int comput;
	int deadline;
	unsigned int time;
public:
	Cpu();
	~Cpu();
	void load(int p, char s, int c, int d);
	void run();
	string getGrid();
	int getNumPreemp();
	int getNumContSwitch();
};

Cpu::Cpu() {
	grid = "";
	numPreemp = numContSwitch = 0;
	pid = -1;
	symbol = ' ';
	comput = 0;
	time = 0;
	deadline = -1;
}

Cpu::~Cpu() {}

void Cpu::load(int p, char s, int c, int d) { //P é o periodo da tarefa 
	symbol = s; //Simbolo da Thread
	deadline = d; //Deadline do processo
	if (pid == -1) //Para ver se a tarefa já foi inicializada  
		pid = p; 
	else {
		if (pid != p) {
			pid = p;
			++numContSwitch;
			if (comput > 0)
				++numPreemp;
		}
	}
	comput = c;
}

void Cpu::run() {
	if (pid != -1) {
		if (deadline!=-1 && time>=deadline)
			grid.append(1, tolower(symbol));
		else
			grid.append(1, symbol);
		++time;
		comput--;
	}
	else {
		++time;
		grid.append(1, '_');
	}
}

string Cpu::getGrid() {
	return grid;
}

int Cpu::getNumPreemp() {
	return numPreemp;
}

int Cpu::getNumContSwitch() {
	return numContSwitch;
}

int main() {
	Cpu cpu;
	
	cout << "----- (LST)" << endl;
	cpu.load((0<<5)|0,'A',2,4); // Carrega a atividade A
	cpu.run();
	cpu.run();
	cpu.load((0<<5)|1,'B',5,10);// Carrega a atividade B
	cpu.run();
	cpu.run();
	cpu.load((1<<5)|0,'A',2,8);
	cpu.run();
	cpu.run();
	cpu.load((0<<5)|1,'B',3,10);
	cpu.run();
	cpu.run();
	cpu.run();
	cpu.load((2<<5)|0,'A',2,12);
	cpu.run();
	cpu.run();
	cpu.load((1<<5)|1,'B',5,20);
	cpu.run();
	cpu.load((3<<5)|0,'A',2,16);
	cpu.run();
	cpu.run();
	cpu.load((1<<5)|1,'B',4,20);
	cpu.run();
	cpu.run();
	cpu.load((4<<5)|0,'A',2,20);
	cpu.run();
	cpu.load((1<<5)|1,'B',2,20);
	cpu.run();
	cpu.load((4<<5)|0,'A',1,20);
	cpu.run();
	cpu.load((1<<5)|1,'B',1,20);
	cpu.run();
	
	cpu.load(0,'A',2,24);	

	cout << cpu.getGrid() << endl;
	cout << cpu.getNumContSwitch() << " " << cpu.getNumPreemp() << endl;

	cout << "----- (NÃO É LST)" << endl;
	
	// A 2 8 8
	// B 2 4 4
	// AA,, ,,,,|
	//   BB|BB,,|
	
	// AABBBB..
	// 4 1
	Cpu cpu2;
	
	cpu2.load((0<<5)|0,'A',2,8);
	cpu2.run();
	cpu2.run();
	cpu2.load((0<<5)|1,'B',2,4);
	cpu2.run();
	cpu2.run();
	cpu2.load((1<<5)|1,'B',2,8);
	cpu2.run();
	cpu2.run();
	cpu2.load(26,'.',2048,2048);
	cpu2.run();
	cpu2.run();
	
	cpu2.load(0,'A',2,16);
	cout << cpu2.getGrid() << endl;
	cout << cpu2.getNumContSwitch() << " " << cpu2.getNumPreemp() << endl;


	
	return 0;
}