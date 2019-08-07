#include "cabecalhos.h"

/* Struct já declarada em "cabeçalhos.h", está aqui apenas para consulta da estrutura

typedef struct circular{
	PCB *head;
	PCB *tail;
}Circular; 

*/

void FreeCircular(Circular *queue){
	if(queue->head==NULL)
		return;
	PCB *iterate=queue->head,*stop=iterate;
	PCB *delete =iterate;
	iterate = iterate->next;
	free(delete);
	while(iterate != stop){
		delete = iterate;
		iterate=iterate->next;	
		free(delete);
	}
}

void insertCircular(Circular *queue,PCB *element){
	if(queue->tail==NULL){
		queue->head=queue->tail=element;
		element->next=element;	
		return;
	}
	element->next=queue->head;
	queue->tail->next=element;
	queue->tail=element;
}

void PrintCircular(Circular *queue){
	if(queue->head==NULL)
		return;
	PCB *iterate=queue->head,*stop=iterate;
	printf("%d ",queue->head->process->pid);
	iterate = iterate->next;
	while(iterate != stop){
		printf("%d ",iterate->process->pid);
		iterate=iterate->next;
	}
	printf("\n");
}

void removeCircular(Circular *queue,PCB *element){
	if(queue->head==element){
		if(element->next==element){
			queue->head=NULL;
			queue->tail=NULL;
			return;
		}
		else{
			queue->tail->next=queue->head->next;
			queue->head=queue->head->next;
			return;
		}
	}
	PCB *iterate = queue->head->next,*before=queue->head;
	PCB *stop = queue->head;
	while(iterate!=stop){
		if(iterate==element){
			before->next=iterate->next;
			if(iterate==queue->tail)
				queue->tail=before;
			return;
		}
		before=before->next;
		iterate=iterate->next;
	}
}