//MAIORIA DAS EXPLICACOES ESTAO EM CLOCK E ROUNDROBIN
#include "cabecalhos.h"

int main(int argc ,char **argv){
	srand(time(NULL));
	if(argc!=2){
		printf("usage: ./main instance(1-5)\n");
		return 1;
	}
	if(strcmp(argv[1],"instance")==0){
		printf("./main 1\n");
		return 1;
	}
	int instance = atoi(argv[1]),numberOfProcesses;
	char file[]="Cenários/cenarioN.txt";
	switch(instance){
		case 1:
			numberOfProcesses=1000;
			file[17]='1';
		break;
		case 2:
			numberOfProcesses=5000;
			file[17]='2';
		break;
		case 3:
			numberOfProcesses=10000;
			file[17]='3';
		break;
		case 4:
			numberOfProcesses=20000;	
			file[17]='4';
		break;
		case 5:
			numberOfProcesses=50000;
			file[17]='5';
		break;
	}
	
	int repeticoes=10;
	Circular *finished;
	Data *data = (Data*)malloc(sizeof(Data)), *averageData = (Data*)malloc(sizeof(Data));
	printf("RoundRobin:\n");	
	finished = RoundRobin(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
	measure(finished,numberOfProcesses,100,data);
	PrintData(data);
	SaveData(data,1,instance);
	printf("\n");
	FreeCircular(finished);
	printf("Loterry:\n");
	zerar(averageData);
	for(int i=0;i<repeticoes;i++){
		finished = Loterry(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
		measure(finished,numberOfProcesses,100,data);
		somar(averageData,data);
		FreeCircular(finished);
	}
	dividir(averageData, repeticoes);
	PrintData(averageData);
	SaveData(averageData,2,instance);
	printf("\n");
	printf("HRRN:\n");	
	finished = HRRN(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
	measure(finished,numberOfProcesses,100,data);
	PrintData(data);
	SaveData(data,3,instance);
	printf("\n");
	FreeCircular(finished);
	printf("PriorityRoundRobin:\n");	
	finished = PriorityRoundRobin(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
	measure(finished,numberOfProcesses,100,data);
	PrintData(data);
	SaveData(data,4,instance);
	printf("\n");
	FreeCircular(finished);
	printf("RatioRoundRobin:\n");	
	finished = RatioRoundRobin(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
	measure(finished,numberOfProcesses,100,data);
	PrintData(data);
	SaveData(data,5,instance);
	printf("\n");
	FreeCircular(finished);
	printf("1-Loterry:\n");
	zerar(averageData);
	for(int i=0;i<repeticoes;i++){
		finished = _1Loterry(numberOfProcesses,100,createPCBList(numberOfProcesses,file));
		measure(finished,numberOfProcesses,100,data);
		somar(averageData,data);
		FreeCircular(finished);
	}
	dividir(averageData, repeticoes);
	PrintData(averageData);
	SaveData(averageData,6,instance);
	printf("\n");
	printf("multi level feedback:\n");	
	finished = MultiLevelFeedback(numberOfProcesses,100,createPCBList(numberOfProcesses,file),4);
	measure(finished,numberOfProcesses,100,data);
	PrintData(data);
	SaveData(data,7,instance);
	printf("\n");
	FreeCircular(finished);
	return 0;
}

/*
Valores pra algorithm (segundo parametro de SaveData)
1 = RoundRobin
2 = Loterry
3 = HRRN
4 = PriorityRoundRobin
5 = RatioRoundRobin
*/
//terceiro parametro = numero do cenario
