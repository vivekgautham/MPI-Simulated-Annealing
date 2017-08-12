#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i=0,n=100;
    char *defaultfilename = "dislikes.dat";
    char *filename = NULL;
    int num;
    if(argc > 3)
    {
        printf("You have entered more than 2 options. Enter correct number of argument");
        return 0;
    }

    for (i=1; i<argc; i++)
    {
	    if(strcmp(argv[i],"-i") == 0)
        {
            if(++i < argc)
            { 
                filename = malloc(sizeof(char) * (strlen(argv[i])+1));
                strcpy(filename,argv[i]);
            }
            else
            {
                printf("Incomplete Option");
                return 0;
            }
        }
    
    }
    if(!filename)
    {
        filename = malloc(sizeof(char) * (strlen(defaultfilename)+1));
        strcpy(filename,defaultfilename);
    }
	
    FILE* file = fopen(filename,"rb");
    if(!file)
    {
        printf("Cannot Open File for read");
        exit(0);
    }
	fread(&n, sizeof(int),1,file);
    for (i = 0;i<n*n;i++)
    {
        if(i%n == 0)
            printf("\n");
        fread(&num, sizeof(int),1,file);
        printf("%d ",num);
    }
    fclose(file);
    printf("\n n = %d filename = %s \n",n,filename);
    free(filename);
    return 0;
}
