#include "cabecalhos.h"

/* Structs já declaradas em "cabeçalhos.h", estão aqui apenas para consultas

typedef struct process{
	 int pid;
	 int submissionTime;
	 int priority;
	 int executionTime;
	 int blockTime;
	 int timeToBlock;
}Process;

typedef struct PCB{
	Process *process;
	struct PCB *next;
	int activeTime;
	int totalTime;
	int blockedTime;
	int responseTime;
	int waitingTime;
	int creationTime;
	int finishTime;
	int _1priority;
	int fila;
}PCB;

*/

PCB **createPCBList(int numberOfProcesses,char *file){
	//printf("%s\n",file);
	PCB **PCBList = (PCB**)malloc(sizeof(PCB*)*numberOfProcesses);	
	Process **processList = ReadProcesses(numberOfProcesses,file);
	for(int i=0;i<numberOfProcesses;i++){
		PCB *new = (PCB*)malloc(sizeof(PCB));
		new->next=NULL;
		new->process = processList[i];
		new->activeTime=new->totalTime=new->blockedTime=new->responseTime=new->waitingTime=0;
		new->creationTime=-1;
		new->finishTime=-1;
		new->_1priority=-1;
		new->fila = -1;
		PCBList[i]=new;	
	}
	return PCBList;
}

void PrintInfo(Process *process){
	printf("pid = %d | submission time = %d | priority = %d | execution tie = %d | block time = %d\n",process->pid,process->submissionTime,process->priority,process->executionTime,process->blockTime);
}

Process **ReadProcesses(int NumberOfProcesses,char *file){
	int cont=0;
	FILE *pont;
	pont = fopen(file,"r");
	Process *new,**newList = (Process**)malloc(sizeof(Process*)*NumberOfProcesses);
	char lixo;
	for(int i=0;i<NumberOfProcesses;i++){
	new = (Process*)malloc(sizeof(Process));
	fscanf(pont,"%d%c%d%c%d%c%d%c%d%c",&new->pid,&lixo,&new->submissionTime,&lixo,&new->priority,&lixo,&new->executionTime,&lixo,&new->blockTime,&lixo);
	new->timeToBlock = 1;
	new->priority++;
	newList[i]=new;
	cont++;
	}
	fclose(pont);
	//TODO
	//implementar ordenação da lista newList em ordem crescente do submissionTime.
	//para acessar o submissionTime do elemento i, use newList[i]->submissionTime
	return newList;
}
