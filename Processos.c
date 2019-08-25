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
		new->activeTime=new->totalTime=new->blockedTime=new->waitingTime=0;
		new->_1priority=new->fila =new->finishTime=new->creationTime=new->responseTime=-1;
		PCBList[i]=new;	
	}
	return PCBList;
}

int comparadorSubmissionTime(const void **a, const void **b) {
    int timeA, timeB;
    timeA = ((Process*)*a)->submissionTime;
    timeB = ((Process*)*b)->submissionTime;

    if (timeA == timeB)
        return 0;

    if (timeA < timeB)
        return -1;

    return 1;
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
		new->timeToBlock = new->executionTime/2;
		new->priority++;
		newList[i]=new;
		cont++;
	}
	fclose(pont);
	qsort(newList, NumberOfProcesses, sizeof(Process*), comparadorSubmissionTime);
	return newList;
}