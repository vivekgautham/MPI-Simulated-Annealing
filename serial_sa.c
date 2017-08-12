#include "header.h"

int main(int argc, char *argv[])
{
    int j,k,i;
    int num;    
    char *ipfilename = "dislikes.dat";
    char *objfilename = "obj.dat";
    char *opfilename = "out.dat";
    //extern char *optarg;
    int opt,sum,delta;
    int **disMat;
    double t1,t2,t3,t4,prob;
    int c1,c2,c3,c4;
    int rank,size; 
    int initTemp=2,noofPpl=20,iters=1000;
    int *a;
    double tempr;
    int associatedDislik;     

    MPI_Init (&argc, &argv);
    /* get current MPI task number */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    /* get number of MPI tasks */
    MPI_Comm_size (MPI_COMM_WORLD, &size);
   
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
                objfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(objfilename,optarg);
                break;
            case 'd':
                opfilename = malloc(sizeof(char)*(strlen(optarg)+1));
                strcpy(opfilename,optarg);
                break;
            default:
                printf("\nWrong Arguments!\n");
        } 
    }    

    if (mod(noofPpl,2))
    {
        printf("Odd number of People\n");
        exit(0);
    }
    t2 = MPI_Wtime(); 
    
    read_graph(ipfilename,&noofPpl,&disMat);
    a = malloc(noofPpl*(sizeof(int)));
    FILE* file = fopen(objfilename,"wb");
    if(!file)
    {
        printf("\n Cannot Open OBJ File for write \n");
        exit(0);
    }
    FILE* file1 = fopen(opfilename,"wb");
    if(!file)
    {
        printf("\n Cannot Open OUT File for write \n");
        exit(0);
    }
    sum = 0;
    for(i=0;i<noofPpl/2;i++) 
    {
        a[i] = i;
        a[i+noofPpl/2] = i;
    }
    sum = compSum(disMat,noofPpl,a);

    printf("\nSUM = %d \n",sum); 
    tempr = initTemp;
    i = 0;
    k = 0;
    
    while(i<iters)
    {
        do
        {
        //   c1 = getRandomStud(noofPpl);
        //   c2 = getRandomStud(noofPpl); 
             c1 = getRandU() * noofPpl;
             c2 = getRandU() * noofPpl;
        }while(a[c1] == a[c2]);
        c3 = getRoomMate(c1,noofPpl,a);
        c4 = getRoomMate(c2,noofPpl,a);

        delta = (disMat[c1][c4]+disMat[c2][c3] - disMat[c1][c3]+disMat[c2][c4]);
        prob = getRandU();
        if( delta < 0 || exp(-delta/tempr) >= prob)
        {
            swap(c1,c2,a);
            sum = compSum(disMat,noofPpl,a);
            //printf("\nSUM = %d \n",sum); 
            i = 0;
        }
        else
        {
            i += 1;
        }
        //printf("\n k = %d  tempr = %lf sum = %d \n",k,tempr,sum);
        //printf("%d\t%d\n",k,sum);
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

    t3 = MPI_Wtime(); 
  
	fwrite(&noofPpl, sizeof(int),1,file1);
	for (j = 0;j<noofPpl;j++)
    {
       num = a[j];
       fwrite(&num, sizeof(int),1,file1);
    }

    //print(noofPpl,a);
    for (i = 0; i < noofPpl/2; i++)
    {
        associatedDislik = disMat[a[i]][getRoomMate(a[i],noofPpl,a)] + disMat[getRoomMate(a[i],noofPpl,a)][a[i]];
        printf("\n ROOM = %d Ocuupants = %d\t%d Associated Dislike for pairing = %d ",i,a[i],getRoomMate(a[i],noofPpl,a),associatedDislik);
    }
    printf("\nSUM = %d \n",sum); 
    printf("\n Total Iterations = %d  \n",k);
    fclose(file);
    fclose(file1);
    t4 = MPI_Wtime(); 
    
    printf("\n Program Time = %lf  Roommate Assignment = %lf No.of Solution tried per sec = %lf\n",(t4-t1),(t3-t2),(double)k/(t3-t2));
    MPI_Finalize();
    
    return 0;
}
