#include "cabecalhos.h"

PCB *Bet(Circular *ready,int totalOdds){
	if(totalOdds==0)
		return NULL;
	int sum=0,ticket = 1 + rand() % totalOdds;
	PCB *iterate=ready->head;
	while(sum <=totalOdds){
		sum+=iterate->process->priority;
		if(sum >= ticket){
			return iterate;
		}
		iterate=iterate->next;
	}
	printf("ops\n");
	return NULL;
}

Circular *Loterry(int numberOfProcesses, int parallelismDegree,PCB **PCBList){
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
	int totalOdds=0;
	while(Nfinished != numberOfProcesses){
		if((Nblocked + Nready) < parallelismDegree && (Nready + Nblocked + Nnew + Nfinished) < numberOfProcesses){
			PCBList[Nready+Nblocked+Nfinished+Nnew]->creationTime = globalTime;
			insertCircular(new,PCBList[Nready+Nblocked+Nfinished+Nnew]);	
			Nnew++;		
		}
		CheckNew(ready,new,&Nready,&Nblocked,parallelismDegree,&Nnew);
		if(active == NULL){
			totalOdds = UpdateTotalOdds(ready);
		}
		active = Bet(ready,totalOdds);
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
				active->waitingTime=0;					
				break;
			}
			if(Nactive == 0)
				break;
		}
		if(clockResult == 1 || clockResult ==2)
			totalOdds = UpdateTotalOdds(ready);
		Nactive = 0;
	}
	return finished;
}

int UpdateTotalOdds(Circular *ready){
	int totalOdds=0;
	if(ready->head==NULL)
		return totalOdds;
	PCB *iterate=ready->head,*stop=iterate;
	totalOdds+=iterate->process->priority;
	iterate = iterate->next;
	while(iterate != stop){
		totalOdds+=iterate->process->priority;
		iterate=iterate->next;
	}
	return totalOdds;
}
