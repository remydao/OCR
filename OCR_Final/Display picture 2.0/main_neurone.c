#include <stdio.h>
#include <stdlib.h>
#include "neurone.h"
#include <math.h>

void xor00()
{
  int x= 0;
  int y=0;
  printf("The value is: %f", xorn(x,y));
}

void xor01()
{
  int x= 0;
  int y=1;
  printf("The value is: %f", xorn(x,y));
}

void xor10()
{
  int x= 1;
  int y=0;
  printf("The value is: %f", xorn(x,y));
}

void xor11()
{
  int x= 1;
  int y= 1;
  printf("The value is: %f", xorn(x,y));
}


int main()
{
  printf(" ____________________________\n");
  printf("|                            |\n");
  printf("|    XOR  NEURAL  NETWORK    |\n");
  printf("|____________________________|\n");
  printf("|   |   |        |           |\n");
  printf("| x | y | output | expected  |\n");
  printf("|___|___|________|___________|\n");
  printf("|   |   |        |           |\n");
  printf("| 0 | 0 |%lf|     0     |\n",xorn(0,0));
  printf("|___|___|________|___________|\n");
  printf("|   |   |        |           |\n");
  printf("| 0 | 1 |%lf|     1     |\n",xorn(0,1));
  printf("|___|___|________|___________|\n");
  printf("|   |   |        |           |\n");
  printf("| 1 | 0 |%lf|     1     |\n",xorn(1,0));
  printf("|___|___|________|___________|\n");
  printf("|   |   |        |           |\n");
  printf("| 1 | 1 |%lf|     0     |\n",xorn(1,1));
  printf("|___|___|________|___________|\n");
  
  
  return 0;
}
