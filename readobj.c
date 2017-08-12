#include "header.h"

int main(int argc, char *argv[])
{
    int j,k;
    int num;    
    char *objfilename = "objfuncvalue.dat";
    int opt,sum;
    int noofPpl;
    int *a=NULL;
    double tempr;
    
    while ((opt = getopt(argc,argv,"i:")) != -1)
    {
        switch(opt){
            case 'i':
                objfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(objfilename,optarg);
                break;
            default:
                printf("Opening default file name");
                break;
        }
    }

    FILE* file = fopen(objfilename,"rb");
    if(!file)
    {
        printf("\n Cannot Open OBJ File for write \n");
        exit(0);
    }
   
	while(1)
    {
        if(feof(file))
            break;
	    fread(&k, sizeof(int),1,file);
	    fread(&sum, sizeof(int),1,file);
	    fread(&tempr, sizeof(double),1,file);
	    fread(&noofPpl, sizeof(int),1,file);
        if(!a)
            a = malloc(noofPpl*(sizeof(int)));
            
	    for (j = 0;j<noofPpl;j++)
        {
    	    fread(&num, sizeof(int),1,file);
            a[j] = num;
        }
        printf("\n Iterations = %d Sum = %d Cur Tempr = %lf No. of Persons = %d \n",k,sum,tempr,noofPpl);
        //print(noofPpl, a);
    }  
    return 0;
}
