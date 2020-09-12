//
//  main.c
//  Procesos
//
//  Created by MacBook Pro on 10/09/20.
//  Copyright © 2020 Naji M A Saadat A01025599. All rights reserved.
// ** Basado en su Codigo Creando_Procesos 2015 **

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

// Child struct
typedef struct {
  pid_t pid;
  int Average;
}
Child;
void NumHistogramPrint(int HistoNumPrint);
void PrintDetails(Child * ChildProcess, int Num, int HighestAverageMax, int AsteriscHisto);

int main(int argc, char *
  const * argv) {
  Child * ChildProcess, * IndexLast = NULL  , * Aux;
  int AsteriscHisto = 0, HighestAverageMax = 0, ChildrenProNum = 0, option = 0;
  char * NChildrenOpt;
  printf("\n\t\t  *Processes* \n");
    
  while ((option = getopt(argc, argv, "n:")) != -1)
    switch (option) {
    case 'n':
      NChildrenOpt = optarg;
      if (atoi(NChildrenOpt) <= 0) {
        printf("Invalid Input, Try Again! Must be a number above 0 \n");
        return 0;
      } else {
        printf("\n\t\t**Valid Input**\n");
        ChildrenProNum = atoi(NChildrenOpt);
      }
      break;
    }
  ChildProcess = malloc(ChildrenProNum * sizeof(Child));
  Aux = ChildProcess;
  int Average;
  pid_t pid;
  printf("\n \t ***Creating %d Children ***\n\n", ChildrenProNum);
  int i = 0;
  while (i < ChildrenProNum) {
    pid = fork();
    if (pid == -1) {
      printf("Failed Process\n");
      exit(0);
    }
    if (pid == 0) {
      float Child=getpid(), parent=getppid();
      Average = round((Child + parent)/ 2);
      printf("*Child PID: %d \t *Average: %d \t *Father PID: %d \t **Created Succesfully**\n", getpid(), Average, getppid());
      return Average;
    } else {
      Aux -> pid = pid;
      Aux++;
      sleep(1);
    }
    i++;
    IndexLast = ChildProcess + ChildrenProNum;
  }
  printf("\n");
    int state = 0;
  for (Aux = ChildProcess; IndexLast > Aux; Aux++) {
    if (waitpid(Aux -> pid, & state, 0) != -1) {
      printf("\n***FINISHING PROCCES %d ***", Aux -> pid);
      printf("\n");
      printf("*Child PID: %d  \t *Average:  %d \t **Finished** \n", Aux -> pid, WEXITSTATUS(state));
      printf("\n");
      Aux -> Average = Aux -> Average + WEXITSTATUS(state);
      HighestAverageMax = Aux -> Average;
      printf("**Adding Details of Child %d to table", Aux -> pid);
      PrintDetails(ChildProcess, ChildrenProNum, HighestAverageMax, AsteriscHisto);
    }
  }
  printf("\n \t ****** Final Version Table ******");
  PrintDetails(ChildProcess, ChildrenProNum, HighestAverageMax, AsteriscHisto);
  free(ChildProcess);
  exit(0);
}

void NumHistogramPrint(int HistoNumPrint) {
  for (int i = 0; i < HistoNumPrint; i++)
    printf("*");
}

void PrintDetails(Child * ChildProcess, int Num, int HighestAverageMax, int AsteriscHisto) {
  int counter = 1;
  printf("\nPID Child \t Average \t Histogram \n\n");
  for (Child * Aux = ChildProcess; ChildProcess + Num > Aux; Aux++) {
    printf("%d \t\t %d \t\t", Aux -> pid, Aux -> Average);
    AsteriscHisto = (Aux -> Average / 10) + counter;
    counter++;
    if (Aux -> Average != 0) {
      NumHistogramPrint(AsteriscHisto);
      printf("   **Children Details Generated** \n ");
    }
    printf("\n");
  }
}
