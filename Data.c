#include "cabecalhos.h"

/* Struct já declarada em "cabeçalhos.h", está aqui apenas para consulta da estrutura

typedef struct data{
	double turnaroundTime;
	double averageServiceTime;
	double CpuUsage;
	double averageResponseTime;
	double throughput;
	double averageWaitingTime;
}Data;

*/

void dividir(Data *data,float razao){
	data->turnaroundTime /= razao;
	data->CpuUsage /= razao;
	data->averageResponseTime /= razao;
	data->throughput /= razao;
	data->averageWaitingTime /= razao;
	data->averageServiceTime /= razao;
}

void measure(Circular *finished,int numberOfProcesses,int parallelismDegree,Data *data){
	if(finished->head==NULL)
		return;
	zerar(data);
	PCB *iterate=finished->head,*stop=iterate;
	iterate->responseTime = iterate->finishTime - iterate->creationTime;
	data->turnaroundTime = data->turnaroundTime + iterate->finishTime-iterate->creationTime;	
	data->CpuUsage = data->CpuUsage +iterate->activeTime;
	data->averageResponseTime = data->averageResponseTime + iterate->responseTime;
	data->throughput = data->throughput + 1;
	data->averageWaitingTime = data->averageWaitingTime + iterate->finishTime-iterate->creationTime - iterate->process->executionTime;
	data->averageServiceTime = data->averageServiceTime + iterate->process->executionTime; 
	iterate = iterate->next;
	while(iterate != stop){
		data->turnaroundTime = data->turnaroundTime + iterate->finishTime-iterate->creationTime;	
		data->CpuUsage = data->CpuUsage +iterate->activeTime;
		data->averageResponseTime = data->averageResponseTime + iterate->responseTime;
		data->throughput = data->throughput + 1;
		data->averageWaitingTime = data->averageWaitingTime + iterate->finishTime-iterate->creationTime - iterate->process->executionTime;
		data->averageServiceTime = data->averageServiceTime + iterate->process->executionTime; 
		iterate=iterate->next;
	}
	data->turnaroundTime = data->turnaroundTime/numberOfProcesses;
	data->averageResponseTime = data->averageResponseTime/numberOfProcesses;
	data->averageWaitingTime = data->averageWaitingTime/numberOfProcesses;
	data->CpuUsage = data->CpuUsage/globalTime;
	data->throughput = data->throughput/globalTime;
	data->averageServiceTime = data->averageServiceTime/numberOfProcesses;
}

void PrintData(Data *data){
	printf("average turnaround Time = %f \naverage Response Time = %f \naverage Waiting Time = %f \nCpu Usage = %f \nthroughput = %f \naverage Service Time = %f",data->turnaroundTime,data->averageResponseTime,data->averageWaitingTime,data->CpuUsage,data->throughput,data->averageServiceTime);
	printf("\ntime = %d\n",globalTime);
}

void SaveData(Data *data,int algorithm,int instance){
	char pasta[30], arquivo[30], comando[30];

	strcpy(pasta, "Relatórios");

	strcpy(comando, "mkdir -p ");
	strcat(comando, pasta);

	strcat(pasta, "/");

	system(comando);

	switch(algorithm){
		case 1:
			strcpy(arquivo,"RoundRobin");
		break;
		case 2:
			strcpy(arquivo,"Loterry");
		break;
		case 3:
			strcpy(arquivo,"HRRN");
		break;
		case 4:
			strcpy(arquivo,"PriorityRoundRobin");
		break;
		case 5:
			strcpy(arquivo,"RatioRoundRobin");
		break;
		case 6:
			strcpy(arquivo,"1-loterry");
		break;
		case 7:
			strcpy(arquivo,"multilevelFeedback");
		break;
	}
	char temp[12];
	sprintf(temp,"%d",instance);
	char cenario[]="Cenario";
	strcat(cenario,temp);
	strcat(arquivo,cenario);
	strcat(arquivo,".txt");
	char endereco[50];
	strcpy(endereco, pasta);
	strcat(endereco, arquivo);
	FILE *pont = fopen(endereco,"w");
	fprintf(pont,"average turnaround Time = %f \naverage Response Time = %f \naverage Waiting Time = %f \nCpu Usage = %f \nthroughput = %f \naverage Service Time = %f%c",data->turnaroundTime,data->averageResponseTime,data->averageWaitingTime,data->CpuUsage,data->throughput,data->averageServiceTime,'\n');
	fclose(pont);
}

void somar(Data *data1,Data *data2){
	data1->turnaroundTime += data2->turnaroundTime;
	data1->CpuUsage += data2->CpuUsage;
	data1->averageResponseTime += data2->averageResponseTime;
	data1->throughput += data2->throughput;
	data1->averageWaitingTime += data2->averageWaitingTime;
	data1->averageServiceTime += data2->averageServiceTime;
}

void zerar(Data *data){
	data->turnaroundTime=data->averageServiceTime=data->CpuUsage=data->averageResponseTime=data->throughput=data->averageWaitingTime=0;
}