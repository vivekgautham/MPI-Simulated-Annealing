#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>
#include "mpi.h"

#define MAX 1000007
#define K 10
#define J 7

extern int j;
extern int k;

extern int *lagTable;

int mod(int,int);

void print_graph(int n, int **am);

void read_graph(char *filename, int *n,int ***A);

void write_graph(char *filename, int n, int **A);

int getRandomStud(int noofPpl);

double getRandProb(void);

double getRandU(void);

int getRoomMate(int c1,int n,int *a);

void print(int n,int *a);

int compSum(int** disMat,int n,int* a);

void swap(int c1,int c2,int *a);

int laggedFibo(void);

void initlagTables(int rank,int size);

int getRandomStudParal(int noofPpl);

double getRandUParal(void);
#endif
