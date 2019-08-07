#include "cabecalhos.h"

PCB *_1Bet(Circular *ready,int totalOdds){
	if(totalOdds==0)
		return NULL;
	int sum=0,ticket = 1 + rand() % totalOdds;
	PCB *iterate=ready->head;
	while(sum <=totalOdds){
		sum+=iterate->_1priority;
		if(sum >= ticket){
			return iterate;
		}
		iterate=iterate->next;
	}
	printf("ops\n");
	return NULL;
}

Circular *_1Loterry(int numberOfProcesses, int parallelismDegree,PCB **PCBList){
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
			totalOdds = _1UpdateTotalOdds(ready,numberOfProcesses);
		}
		active = _1Bet(ready,totalOdds);
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
			totalOdds = _1UpdateTotalOdds(ready,numberOfProcesses);
		Nactive = 0;
	}
	return finished;
}

int _1UpdateTotalOdds(Circular *ready,int Nprocesses){
	int totalOdds=0;
	Process *medianProcess = (Process*)malloc(sizeof(Process));
	medianProcess->pid=-1;
	medianProcess->submissionTime=medianProcess->priority=medianProcess->executionTime=medianProcess->blockTime=medianProcess->timeToBlock=0;
	if(ready->head==NULL)
		return totalOdds;
	PCB *iterate=ready->head,*stop=iterate;
	medianProcess->submissionTime += iterate->process->submissionTime;
	medianProcess->priority += iterate->process->priority;
	medianProcess->executionTime += iterate->process->executionTime;
	medianProcess->blockTime += iterate->process->blockTime;
	medianProcess->timeToBlock += iterate->process->timeToBlock;
	iterate = iterate->next;
	while(iterate != stop){
		medianProcess->submissionTime += iterate->process->submissionTime;
		medianProcess->priority += iterate->process->priority;
		medianProcess->executionTime += iterate->process->executionTime;
		medianProcess->blockTime += iterate->process->blockTime;
		medianProcess->timeToBlock += iterate->process->timeToBlock;
		iterate=iterate->next;
	}
	medianProcess->submissionTime = (int) (medianProcess->submissionTime/Nprocesses);
	medianProcess->priority = (int) (medianProcess->priority/Nprocesses);
	medianProcess->executionTime = (int) (medianProcess->executionTime/Nprocesses);
	medianProcess->blockTime = (int) (medianProcess->blockTime/Nprocesses);
	medianProcess->timeToBlock = (int) (medianProcess->timeToBlock/Nprocesses);

	iterate=ready->head;
	stop=iterate;
	iterate->_1priority = iterate->process->priority + distance(iterate->process,medianProcess);
	totalOdds+=iterate->_1priority;
	iterate = iterate->next;
	while(iterate != stop){
		iterate->_1priority = iterate->process->priority + distance(iterate->process,medianProcess);
		totalOdds+=iterate->_1priority;
		iterate=iterate->next;
	}
	return totalOdds;
}

int distance(Process *p1, Process *p2){
	int result = 0;
	result += (p1->submissionTime - p2->submissionTime)*(p1->submissionTime - p2->submissionTime);
	result += (p1->priority - p2->priority)*(p1->priority - p2->priority);
	result += (p1->executionTime - p2->executionTime)*(p1->executionTime - p2->executionTime);
	result += (p1->blockTime - p2->blockTime)*(p1->blockTime - p2->blockTime);
	result += (p1->timeToBlock - p2->timeToBlock)*(p1->timeToBlock - p2->timeToBlock);
	return result;
}
