#include "header.h"

int main(int argc, char *argv[])
{
    int j,k,i;
    char *ipfilename = "dislikes.dat";
    char *objfilename = "obj.dat";
    char *opfilename = "out.dat";
    //extern char *optarg;
    int opt,sum,num,delta;
    int **disMat;
    double t1,t2,t3,t4,prob;
    int c1,c2,c3,c4;
    int rank,size; 
    int initTemp=2,noofPpl=20,iters=1000;
    int *a = NULL, *finalAsign = NULL;
    double tempr;
    int localRes[2];
    int globalRes[2];
    int successsolutionCount = 0; 
    int totalSolntried = 0;

 
    MPI_Init (&argc, &argv);
    /* get current MPI task number */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    /* get number of MPI tasks */
    MPI_Comm_size (MPI_COMM_WORLD, &size);
   
    MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime(); 
    
    while ((opt = getopt(argc,argv,"i:I:t:n:o:d:")) != -1)
    {
        switch(opt){
            case 'I':
                iters = atoi(optarg);
                break;
            case 'i':
                ipfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(ipfilename,optarg);
                break;
            case 't':
                initTemp = atoi(optarg);
                break;
            case 'n':
                noofPpl = atoi(optarg);
                break;
            case 'o':
                objfilename = malloc(sizeof(char)*(strlen(optarg)+3));
                sprintf(objfilename,"%d",rank);
                strcat(objfilename,optarg);
                break;
            case 'd':
                opfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(opfilename,optarg);
                break;
            default:
                printf("\nWrong Arguments!\n");
        } 
    }    
 
    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime(); 
    
    read_graph(ipfilename,&noofPpl,&disMat);
    //print_graph(noofPpl,disMat);

    a = malloc(noofPpl*(sizeof(int)));
    finalAsign = malloc(noofPpl*(sizeof(int)));
    sum = 0;
    FILE* file = fopen(objfilename,"wb");
    if(!file)
    {
        printf("\n Cannot Open OBJ File for write \n");
        exit(0);
    }
    
    for(i=0;i<noofPpl/2;i++) 
    {
        a[i] = i;
        a[i+noofPpl/2] = i;
    }
 
    sum = compSum(disMat,noofPpl,a);
    //printf("\nRank = %d SUM = %d \n",rank, sum); 
    tempr = initTemp;
    i = 0;
    k = 0;
    initlagTables(rank,size);
    //printf("Rank = %d , rnd = %lf",rank,getRandUParal());
   
    while(i<iters)
    {
        do
        {
           c1 = getRandomStudParal(noofPpl);
           c2 = getRandomStudParal(noofPpl);
        }while(a[c1] == a[c2]);
        
        c3 = getRoomMate(c1,noofPpl,a);
        c4 = getRoomMate(c2,noofPpl,a);
        
        delta = (disMat[c1][c4]+disMat[c2][c3] - disMat[c1][c3]+disMat[c2][c4]);
        prob = getRandUParal();
        //printf("Rank = %d , rnd = %lf",rank,prob);
        
        if( delta < 0 || exp(-delta/tempr) >= prob)
        {
            successsolutionCount++; 
            swap(c1,c2,a);
            sum = compSum(disMat,noofPpl,a);
            i = 0;
        }
        else
        {
            i += 1;
        }
        if (rank == 4)
      //      printf("%d\t%d\n",k,sum);
        tempr = 0.999 * tempr;
        k++;
        
        /*Writing Objective function file for every iter for restoration purpose*/
	    fwrite(&k, sizeof(int),1,file);
	    fwrite(&sum, sizeof(int),1,file);
	    fwrite(&tempr, sizeof(double),1,file);
	    fwrite(&noofPpl, sizeof(int),1,file);
	    for (j = 0;j<noofPpl;j++)
        {
            num = a[j];
    	    fwrite(&num, sizeof(int),1,file);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    t3 = MPI_Wtime(); 
    
    printf("\nRank = %d SUM = %d k = %d\n",rank, sum, k); 

    localRes[0] = sum;
    localRes[1] = rank;

    MPI_Allreduce(localRes,globalRes,1,MPI_2INT,MPI_MINLOC,MPI_COMM_WORLD);
    MPI_Allreduce(&k,&totalSolntried,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);

    if (rank == globalRes[1])
    {
        FILE* file1 = fopen(opfilename,"wb");
        if(!file)
        {
            printf("\n Cannot Open OUT File for write \n");
            exit(0);
        }
        printf("\n Rank %d has the solution nearest to Optimal \n",rank);
        print(noofPpl,a);
	    fwrite(&noofPpl, sizeof(int),1,file1);
	    for (j = 0;j<noofPpl;j++)
        {
            num = a[j];
            fwrite(&num, sizeof(int),1,file1);
        }
        fclose(file1);
    }   

    MPI_Bcast(finalAsign,noofPpl,MPI_INT,globalRes[1],MPI_COMM_WORLD);
 
    MPI_Barrier(MPI_COMM_WORLD);
    t4 = MPI_Wtime(); 
  
    if (rank == 0) 
        printf("\n Program Time = %lf  Roommate Assignment = %lf No of Solutions tried per sec = %lf\n",(t4-t1),(t3-t2),(double)totalSolntried/(t3-t2));
    
    fclose(file);

    MPI_Finalize();

    free(lagTable);
    free(a); 
    free(finalAsign); 

    return 0;
}
