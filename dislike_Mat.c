#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i=0,j=0,n=100;
    char *defaultfilename = "dis.dat";
    char *filename = NULL;
    int num;

    if(argc > 9)
    {
        printf("You have entered more than 4 options. Enter correct number of argument");
        return 0;
    }

    for (i=1; i<argc; i++)
    {
	  if(strcmp(argv[i],"-o") == 0)
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
      else if(strcmp(argv[i],"-n" ) == 0)
      {
        if(++i < argc)
        { 
            n = atoi(argv[i]);
        }
        else
        {
            printf("Incomplete Option");
            return 0;
        }
	  }
      else
	  {    
	        printf("Invalid Option");
            return 0;
      }
    
    }
    if(!filename)
    {
        filename = malloc(sizeof(char) * (strlen(defaultfilename)+1));
        strcpy(filename,defaultfilename);
    }
    if(n==0)
    	n = 100;	
	
    FILE* file = fopen(filename,"wb");
    if(!file)
    {
        printf("\n Cannot Open File for write \n");
        exit(0);
    }
	fwrite(&n, sizeof(int),1,file);
    
    for (i = 0;i<n;i++)
    {
	    for (j = 0;j<n;j++)
        {
            num = rand()%11;
            if(i == j)
                num = 0;
    	    fwrite(&num, sizeof(int),1,file);
        }
    }
    fclose(file); 
    
/*    A = (int **) malloc(n*sizeof(int *));
    numStorage = (int *) malloc(n*n*sizeof(int));
    for(i=0;i<n;i++)
    {
        A[i] = &numStorage[i*n];
    }

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            num = rand()%11; 
            A[i][j] = num;
        }
    }

    write_graph(filename,n,A);
*/    
    printf("\n n = %d filename = %s\n",n,filename);
    free(filename);
    return 0;
}
