#include "cabecalhos.h"

void CheckReadyMultilevel(Circular *blocked,Circular **ready,int *Nblocked,int *Nready){
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
		insertCircular(ready[remove[i]->fila],remove[i]);
		*Nready= *Nready +1;
	}
	free(remove);
		
}

Circular *MultiLevelFeedback(int numberOfProcesses, int parallelismDegree,PCB **PCBList, int filas){
	Circular **ready = (Circular**)malloc(sizeof(Circular*) * filas);
	Circular *blocked = (Circular*)malloc(sizeof(Circular));
	Circular *finished = (Circular*)malloc(sizeof(Circular));
	Circular *new = (Circular*)malloc(sizeof(Circular));
	int i;
	for(i = 0; i < filas; i++){
		ready[i] = (Circular*)malloc(sizeof(Circular));
		ready[i]->head=ready[i]->tail=NULL;
	}
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
		CheckNew(ready[0],new,&Nready,&Nblocked,parallelismDegree,&Nnew);
		
		//i = 0;

		/* while(i < filas-1 && ready[i]->head == NULL){
			i++;
		}*/
		for(i=0;i<filas-1;i++)
			if(ready[i]->head != NULL)		
				break;

		active = ready[i]->head;

		if(active != NULL){
			Nactive = 1;
			active->fila = i + 1;
			if(active->fila==filas)
				active->fila--;
		}
	
		int clockResult, quantum = 4 * (i + 1);
		for(int j=0;j<quantum;j++){
			//globalTime++;
		
			clockResult = Clock(ready, ready[i] ,blocked,finished,new,active,&Nready,&Nblocked,&Nfinished,Nactive);
			if(clockResult==2)
				break;
			if(clockResult==1){
				active->waitingTime=0;					
				break;
			}
			if(Nactive == 0)
				break;
		}
		if(clockResult==0 && Nactive==1){
			removeCircular(ready[i],active);
			insertCircular(ready[active->fila],active);
		}
		Nactive = 0;
	}
	return finished;
}
