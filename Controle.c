#include "cabecalhos.h"

void CheckNew(Circular *ready,Circular *new,int *Nready,int *Nblocked,int parallelismDegree,int *Nnew){
	if(new->head==NULL)
		return;
	PCB *iterate=new->head,*stop=iterate;
	PCB **remove = (PCB**)malloc(sizeof(PCB*)*(*Nnew));
	int index=0;
	remove[index++]=iterate;
	iterate = iterate->next;
	while(iterate != stop){
		remove[index++]=iterate;
		iterate=iterate->next;
	}
	for(int i=0;i<index;i++){
		if(*Nready + *Nblocked < parallelismDegree){
			remove[i]->responseTime = globalTime - remove[i]->creationTime;
			removeCircular(new,remove[i]);
			*Nnew=*Nnew -1;
			insertCircular(ready,remove[i]);
			*Nready= *Nready +1;
		}
	}
	free(remove);
}

void CheckReady(Circular *blocked,Circular *ready,int *Nblocked,int *Nready){
	if(blocked->head==NULL)
		return;
	PCB *iterate=blocked->head,*stop=iterate;
	PCB **remove = (PCB**)malloc(sizeof(PCB*)*(*Nblocked));
	int index=0;
	if(iterate->blockedTime == iterate->process->blockTime)
		remove[index++]=iterate;
	iterate = iterate->next;
	while(iterate != stop){
		if(iterate->blockedTime == iterate->process->blockTime)
			remove[index++]=iterate;
		iterate=iterate->next;
	}
	for(int i=0;i<index;i++){
		removeCircular(blocked,remove[i]);
		*Nblocked=*Nblocked -1;
		insertCircular(ready,remove[i]);
		*Nready= *Nready +1;
	}
	free(remove);
		
}

int Clock(Circular **readyFila,Circular *ready,Circular *blocked,Circular *finished,Circular *new,PCB *active,int *Nready,int *Nblocked,int *Nfinished,int Nactive){	
	int result=0;
	if(Nactive==1){
		if(active->activeTime == active->process->timeToBlock){//checa se esta na hora de bloquear
			if(readyFila!=NULL){
				active->fila--;
				if(active->fila<0)
					active->fila++;
					
			}
			removeCircular(ready,active);
			*Nready= *Nready -1;
			insertCircular(blocked,active);
			*Nblocked=*Nblocked +1;
			result=1;	
			active->blockedTime--;
			
		}
		if(active->activeTime >= active->process->executionTime){//checa se ja finalizou
			active->finishTime=globalTime;
			removeCircular(ready,active);
			*Nready= *Nready -1;
			insertCircular(finished,active);
			*Nfinished = *Nfinished +1;
			result=2;
			active->activeTime--;
		}
		active->activeTime++;
	}
	globalTime++;
	IncrementeTotalTime(ready);//
	IncrementeTotalTime(blocked);//
	IncrementeTotalTime(new);//
	IncrementBlockedTime(blocked);//	incrementa os tempos
	IncrementWaitingTime(ready);//
	if(readyFila==NULL)
		CheckReady(blocked,ready,Nblocked,Nready);//checa se algeum esta pronto
	else
		CheckReadyMultilevel(blocked,readyFila,Nblocked,Nready);
	return result;
}

void IncrementBlockedTime(Circular *queue){
	if(queue->head==NULL)
		return;
	PCB *iterate=queue->head,*stop=iterate;
	iterate->blockedTime++;
	iterate = iterate->next;
	while(iterate != stop){
		iterate->blockedTime++;
		iterate=iterate->next;
	}
}

void IncrementeTotalTime(Circular *queue){
	if(queue->head==NULL)
		return;
	PCB *iterate=queue->head,*stop=iterate;
	iterate->totalTime++;
	iterate = iterate->next;
	while(iterate != stop){
		iterate->totalTime++;
		iterate=iterate->next;
	}
}

void IncrementWaitingTime(Circular *queue){
	if(queue->head==NULL)
		return;
	PCB *iterate=queue->head,*stop=iterate;
	iterate->waitingTime++;
	iterate = iterate->next;
	while(iterate != stop){
		iterate->waitingTime++;
		iterate=iterate->next;
	}
}