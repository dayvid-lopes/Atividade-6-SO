#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Inicio da declaração das structs

    typedef struct data{
        double turnaroundTime;
        double averageServiceTime;
        double CpuUsage;
        double averageResponseTime;
        double throughput;
        double averageWaitingTime;
    }Data;

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
    
    typedef struct circular{
        PCB *head;
        PCB *tail;
    }Circular;

//Fim da declaração das structs

//Inicio da declaração das variáveis globais

    int globalTime;

//Fim da declaração das variáveis globais

//Inicio da declaração de funcões

    //Controle.c
        void CheckNew(Circular *,Circular *,int *,int *,int ,int *);
        void CheckReady(Circular *,Circular *,int *,int *);
        int  Clock(Circular **,Circular *,Circular *,Circular *,Circular *,PCB *,int *,int *,int *,int );
        void IncrementBlockedTime(Circular *);
        void IncrementeTotalTime(Circular *);
        void IncrementWaitingTime(Circular *);

    //Data.c
        void dividir(Data *,float );
        void measure(Circular *,int ,int ,Data *);
        void PrintData(Data *);
        void SaveData(Data *,int ,int );
        void somar(Data *,Data *);
        void zerar(Data *);

    //Filas.c
        void FreeCircular(Circular *);
        void insertCircular(Circular *,PCB *);
        void PrintCircular(Circular *);
        void removeCircular(Circular *,PCB *);

    //HRRN.c
        PCB      *GetHighestRatio(Circular *);
        Circular *HRRN(int , int ,PCB **);

    //Loterry.c
        PCB      *Bet(Circular *,int );
        Circular *Loterry(int , int ,PCB **);
        int       UpdateTotalOdds(Circular *);

    //1-Loterry.c
        PCB      *_1Bet(Circular *,int );
        Circular *_1Loterry(int , int ,PCB **);
        int       _1UpdateTotalOdds(Circular *,int );
        int        distance(Process *, Process *);

    //Multilevel_Feedback.c
        void      CheckReadyMultilevel(Circular *,Circular **,int *,int *);
        Circular *MultiLevelFeedback(int , int ,PCB **, int );

    //Processos.c
        PCB     **createPCBList(int ,char *);
        int       comparadorSubmissionTime(const void **, const void **);
        void      PrintInfo(Process *);
        Process **ReadProcesses(int ,char *);

    //Round-robins.c
        Circular *PriorityRoundRobin(int , int ,PCB **);
        Circular *RatioRoundRobin(int , int ,PCB **);
        Circular *RoundRobin(int ,int ,PCB **);

//Fim da declaração de funcões
