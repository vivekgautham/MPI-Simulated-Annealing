#include "header.h"

int j = J-1;
int k = K-1;

int *lagTable = NULL;

int min(int a, int b)
{
    if(a > b || a == -1)
        return b;
    return a;
}
void print_graph(int n, int **am)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",am[i][j]);
        }
        printf("\n");
    } 
}

void write_graph(char *filename, int n, int **A)
{
    int i;
    FILE* file = fopen(filename,"wb");
    if(!file)
    {
        printf("Cannot Open File for write");
        exit(0);
    }
	fwrite(&n, sizeof(int),1,file);
    for (i = 0;i<n;i++)
    {
    	fwrite(A[i], sizeof(int),n,file);
        
    }
    fclose(file);
}

void read_graph(char *filename, int *n,int ***A)
{
    int i,dim;
    int *numStorage;
    FILE* file = fopen(filename,"rb");
    if(!file)
    {
        printf("Cannot Open File for read");
        exit(0);
    }
    fread(&dim,sizeof(int),1,file); 
    dim = *n; // dim is total matrix size , *n is user specified  
    *A = (int **) malloc(dim*sizeof(int *));
    numStorage = (int *) malloc(dim*dim*sizeof(int));
    for (i=0;i<dim;i++)
    {
        (*A)[i] = &numStorage[i*dim];
	    fread((*A)[i], sizeof(int),dim,file);
    }
    fclose(file);
}

int getRandomStud(int noofPpl)
{
    return (rand() % noofPpl);
}

double getRandU(void)
{
    return (double)rand()/(double)RAND_MAX;
}

int getRoomMate(int c1,int n,int *a)
{
   int i;
   for (i=0; i<n; i++) 
   {
       if (a[i] == a[c1] && i != c1)
           return i;
   }
   return -1;
}

void print(int n,int *a)
{
    int i;
    for (i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
} 

int compSum(int** disMat,int n,int* a)
{
    int i,j,sum = 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(a[i] == a[j])
            {
                sum += disMat[i][j];
            }
        }
    } 
    return sum;
}

void swap(int c1,int c2,int *a)
{
    int tem;
    tem = a[c1];
    a[c1] = a[c2];
    a[c2] = tem; 
}

void initlagTables(int rank,int size)
{
    lagTable = malloc(sizeof(int)*K);
   /* Using Leap Frog Method to set up initial Lag Table*/
    srand(rank);
    int i=0,k=0;
    while(1)
    {
        if((i%size) == rank)
        {
            lagTable[k] = rand()%MAX;
            k++;
            if(k == K)
                break;
        }
        else
        {
            rand();
            i++;
        }
    }
}

int laggedFibo()
{
    int x = 0;
    x = (lagTable[j] + lagTable[k]);
    x = mod(x,MAX);
    lagTable[j] = x;
    j = mod(j-1,K);
    k = mod(k-1,K);
    //printf("\n j = %d k = %d \n", j,k);
    return x;
}

int mod(int a,int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

int getRandomStudParal(int noofPpl)
{
    return (laggedFibo() % noofPpl);
}

double getRandUParal(void)
{
    return (double)laggedFibo()/(double)MAX;
}


