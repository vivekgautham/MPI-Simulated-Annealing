#include "header.h"

int main(int argc, char *argv[])
{
    int j;
    int num;    
    char *opfilename = "roomassign.dat";
    int opt;
    int noofPpl;
    
    while ((opt = getopt(argc,argv,"i:")) != -1)
    {
        switch(opt){
            case 'i':
                opfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(opfilename,optarg);
                break;
            default:
                printf("Opening default file name");
                break;
        }
    }

    FILE* file = fopen(opfilename,"rb");
    if(!file)
    {
        printf("\n Cannot Open OBJ File for write \n");
        exit(0);
    }
   
	fread(&noofPpl, sizeof(int),1,file);
            
	for (j = 0;j<noofPpl;j++)
    {
        fread(&num, sizeof(int),1,file);
        //a[j] = num;
        printf("%d\t",num);
    }
        //print(noofPpl, a);
    return 0;
}
