#include "cabecalhos.h"

Circular *PriorityRoundRobin(int numberOfProcesses, int parallelismDegree,PCB **PCBList){
	Circular *ready = (Circular*)malloc(sizeof(Circular));
	Circular *blocked = (Circular*)malloc(sizeof(Circular));
	Circular *finished = (Circular*)malloc(sizeof(Circular));
	Circular *new = (Circular*)malloc(sizeof(Circular));
	ready->head=ready->tail=NULL;
	blocked->head=blocked->tail=NULL;
	finished->head=finished->tail=NULL;
	new->head=new->tail=NULL;
	int Nready=0,Nblocked=0,Nfinished=0,Nnew=0,Nrunning=0,Nactive=0;
	PCB *active=NULL,*temp=NULL;
	int quantum=2;
	globalTime=0;
	while(Nfinished != numberOfProcesses){
		if((Nblocked + Nready) < parallelismDegree && (Nready + Nblocked + Nnew + Nfinished) < numberOfProcesses){
			PCBList[Nready+Nblocked+Nfinished+Nnew]->creationTime = globalTime;
			insertCircular(new,PCBList[Nready+Nblocked+Nfinished+Nnew]);	
			Nnew++;		
		}
		CheckNew(ready,new,&Nready,&Nblocked,parallelismDegree,&Nnew);
		if(active == NULL)
			active = ready->head;
		if(active != NULL){
			temp=active->next;
			Nactive = 1;
			quantum = 2*active->process->priority;
		}
		else
			quantum = 1;
		int clockResult=0;
		for(int i=0;i<quantum;i++){
			////globalTime++;
			if(active!=NULL)
				temp=active->next;
		
			clockResult = Clock(NULL, ready,blocked,finished,new,active,&Nready,&Nblocked,&Nfinished,Nactive);
			if(clockResult==1)
				break;
			if(clockResult==2)
				break;
			if(Nactive==0)	
				break;
		}
		if(clockResult==1 || clockResult == 2)
			if(temp == active) 
				temp = NULL;	
		active = temp;	
		Nactive = 0;	
	}
	return finished;
}

Circular *RatioRoundRobin(int numberOfProcesses, int parallelismDegree,PCB **PCBList){
	Circular *ready = (Circular*)malloc(sizeof(Circular));
	Circular *blocked = (Circular*)malloc(sizeof(Circular));
	Circular *finished = (Circular*)malloc(sizeof(Circular));
	Circular *new = (Circular*)malloc(sizeof(Circular));
	ready->head=ready->tail=NULL;
	blocked->head=blocked->tail=NULL;
	finished->head=finished->tail=NULL;
	new->head=new->tail=NULL;
	int Nready=0,Nblocked=0,Nfinished=0,Nnew=0,Nrunning=0,Nactive=0;
	PCB *active=NULL,*temp=NULL;
	int quantum=2;
	globalTime=0;
	while(Nfinished != numberOfProcesses){
		if((Nblocked + Nready) < parallelismDegree && (Nready + Nblocked + Nnew + Nfinished) < numberOfProcesses){
			PCBList[Nready+Nblocked+Nfinished+Nnew]->creationTime = globalTime;
			insertCircular(new,PCBList[Nready+Nblocked+Nfinished+Nnew]);	
			Nnew++;		
		}
		CheckNew(ready,new,&Nready,&Nblocked,parallelismDegree,&Nnew);
		if(active == NULL)
			active = ready->head;
		if(active != NULL){
			temp=active->next;
			Nactive = 1;
		}
		
		int clockResult=0;
		if(Nready>0)
			quantum = 400/Nready;
		else
			quantum = 1;
		for(int i=0;i<quantum;i++){
			//globalTime++;
			if(active!=NULL)
				temp=active->next;
		
			clockResult = Clock(NULL, ready,blocked,finished,new,active,&Nready,&Nblocked,&Nfinished,Nactive);
			if(clockResult==1)
				break;
			if(clockResult==2)
				break;
			if(Nactive==0)	
				break;
		}
		if(clockResult==1 || clockResult == 2)
			if(temp == active)
				temp = NULL;
				
			
		active = temp;	
		Nactive = 0;	
	}
	return finished;
}

Circular *RoundRobin(int numberOfProcesses,int parallelismDegree,PCB **PCBList){
	Circular *ready = (Circular*)malloc(sizeof(Circular));//fila pronto pra execucao
	Circular *blocked = (Circular*)malloc(sizeof(Circular));//fila bloqueado, esperando tempo
	Circular *finished = (Circular*)malloc(sizeof(Circular));//fila dos que acabaram de executar
	Circular *new = (Circular*)malloc(sizeof(Circular));//fila dos que foram criados e estao esperando espaco para entrar em ready

	ready->head=ready->tail=NULL;
	blocked->head=blocked->tail=NULL;
	finished->head=finished->tail=NULL;
	new->head=new->tail=NULL;

	int Nready=0,Nblocked=0,Nfinished=0,Nnew=0,Nrunning=0,Nactive=0;
	PCB *active=NULL,*temp=NULL;
	int quantum=4;
	globalTime=0;

	while(Nfinished != numberOfProcesses){
		if((Nblocked + Nready) < parallelismDegree && (Nready + Nblocked + Nnew + Nfinished) < numberOfProcesses){//enquanto pode criar
			PCBList[Nready+Nblocked+Nfinished+Nnew]->creationTime = globalTime;//Nready+Nblocked+Nfinished+Nnew=N de processos
			insertCircular(new,PCBList[Nready+Nblocked+Nfinished+Nnew]);	
			Nnew++;		
		}
		CheckNew(ready,new,&Nready,&Nblocked,parallelismDegree,&Nnew);//checa se alguem de new pode ir pra pronto
		if(active == NULL)
			active = ready->head;
		if(active != NULL){//checa se alguem pode executar agora
			temp=active->next;
			Nactive = 1;
		}
		int clockResult=0;
		for(int i=0;i<quantum;i++){
			////globalTime++;
			if(active!=NULL)
				temp=active->next;
		
			clockResult = Clock(NULL, ready,blocked,finished,new,active,&Nready,&Nblocked,&Nfinished,Nactive);
			if(clockResult==1)//bloqueado
				break;
			if(clockResult==2)//terminado
				break;
			if(Nactive==0)	
				break;
		}
		if(clockResult==1 || clockResult == 2)
			if(temp == active)//active era o ultimo elemento da fila, entao temp vai dar na fila blocked ou finished
				temp = NULL;
				
			
		active = temp;	
		Nactive = 0;	
	}
	return finished;
}
