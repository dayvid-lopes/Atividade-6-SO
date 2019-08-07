#include "cabecalhos.h"

PCB *GetHighestRatio(Circular *ready){
	if(ready->head==NULL)
		return NULL;
	PCB *best;
	PCB *iterate=ready->head,*stop=iterate;
	double highestRatio=-1,waitingTime = iterate->waitingTime,executionTime=iterate->process->executionTime;

	if((waitingTime + executionTime) / executionTime > highestRatio ){
		highestRatio= (waitingTime +executionTime) / executionTime;
		best = iterate;
	}
	iterate = iterate->next;
	while(iterate != stop){
		if((waitingTime + executionTime) / executionTime > highestRatio ){
			highestRatio= (waitingTime +executionTime) / executionTime;
			best = iterate;
		}
		iterate=iterate->next;
	}
	return best;
}

Circular *HRRN(int numberOfProcesses, int parallelismDegree,PCB **PCBList){
	Circular *ready = (Circular*)malloc(sizeof(Circular));
	Circular *blocked = (Circular*)malloc(sizeof(Circular));
	Circular *finished = (Circular*)malloc(sizeof(Circular));
	Circular *new = (Circular*)malloc(sizeof(Circular));
	ready->head=ready->tail=NULL;
	blocked->head=blocked->tail=NULL;
	finished->head=finished->tail=NULL;
	new->head=new->tail=NULL;
	int Nready=0,Nblocked=0,Nfinished=0,Nnew=0,Nrunning=0,Nactive=0;
	PCB *active=NULL,*temp;
	globalTime=0;
	while(Nfinished != numberOfProcesses){
		if((Nblocked + Nready) < parallelismDegree && (Nready + Nblocked + Nnew + Nfinished) < numberOfProcesses){
			PCBList[Nready+Nblocked+Nfinished+Nnew]->creationTime = globalTime;
			insertCircular(new,PCBList[Nready+Nblocked+Nfinished+Nnew]);	
			Nnew++;		
		}
		CheckNew(ready,new,&Nready,&Nblocked,parallelismDegree,&Nnew);
		active = GetHighestRatio(ready);//<============conta
		if(active != NULL){
			Nactive = 1;
		}
		int clockResult;
		while(1){
			//globalTime++;
		
			clockResult = Clock(NULL, ready,blocked,finished,new,active,&Nready,&Nblocked,&Nfinished,Nactive);
			if(clockResult==2)
				break;
			if(clockResult==1){
				//active->waitingTime=0;					
				break;
			}
			if(Nactive == 0)
				break;
		}	
		Nactive = 0;
	}
	return finished;
}
