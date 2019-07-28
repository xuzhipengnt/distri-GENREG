#include "gendef.h"
#define NODENUMBER 400
static FILE *ergfile,*lstfile,*autfile;
static char erg[20],lst[20],aut[20];

static SCHAR n,k,t=3,mid_max=NOTSET,splitlevel=NOTSET;
static SCHAR storeall=0,printall=0,efile=0;
static SCHAR codestdout=0,asciistdout=0;
static ULONG tostore=0,toprint=0,count=0;
static unsigned long long anz=0;
static unsigned int  jobs=0,jobnr=1,jobend=0,jobstart;
clock_t start, finish;
double duration;
char  neu[20],rec[20];
 FILE  *recfile;
 ULONG newanz=0;
extern char opt_a[20],opt_d[20];
extern double start_t;
extern int Asort_a;
extern int Asort_d;
extern int Dsort_a;
extern int Dsort_d;
void generate()
{
#ifdef DOSTIME
 clock_t start,stop;
 start=clock();
#endif
#ifdef UNIXTIME
 UINT stop;
 struct tms TMS;
#endif

 if(mid_max==NOTSET)
    mid_max=default_mid_max(n,k,t);

 if(splitlevel==NOTSET&&jobs>0)
    splitlevel=default_splitlevel(n,k,t);

 //fprintf(ergfile,"\n          GENREG - Generator fuer regulaere Graphen\n");
// fprintf(ergfile,"          %d Knoten, Grad %d, ",n,k);
 // fprintf(ergfile,"Taillenweite mind. %d\n",t);
 //if(jobs)
 //   fprintf(ergfile,"          Erzeugung Teil %d von %d gestartet...\n",jobnr,jobs);
 //else
 //   fprintf(ergfile,"          Erzeugung gestartet...\n");
 //fflush(ergfile);

 ordstart(n,k,t,mid_max,
	  splitlevel,jobs,jobnr-1,
	  lstfile,autfile,ergfile,
	  tostore,toprint,count,
	  storeall,printall,&anz);

// fprintf(ergfile,"          %ld Graphen erzeugt.\n",anz);

#ifdef DOSTIME
 stop=clock()-start;
#endif
#ifdef UNIXTIME
 if(times(&TMS)==-1);
 stop=(UINT)TMS.tms_utime; 
#endif
#ifdef time_factor
 fprintf(ergfile,"          Laufzeit:%.1fs  ",(float)stop/time_factor);
 if(stop>time_factor)
    fprintf(ergfile,"%.1f Repr./s",(float)anz/((float)stop/time_factor));
 fprintf(ergfile,"\n");
#endif
}

SCHAR inputerror()
{
 SCHAR error=1;

 if(n>MAXN)
    fprintf(stdout,"maximal %d Knoten\n",MAXN);
 else
 if(n<MINN)
    fprintf(stdout,"mindestens %d Knoten\n",MINN);
 else
 if(k>MAXK)
    fprintf(stdout,"Grad maximal %d\n",MAXK);
 else
 if(k<MINK)
    fprintf(stdout,"Grad mindestens %d\n",MINK);
 else
 if(t>MAXT)
    fprintf(stdout,"Taillenweite maximal %d\n",MAXT);
 else
 if(t<MINT)
    fprintf(stdout,"Taillenweite mindestens %d\n",MINT);
 else
    error=0;

 return error;
}

void openfiles()
{
    if(codestdout)
       lstfile=stdout;
    else
    if(storeall==1||tostore>0)
      {
       sprintf(lst,"%d%d_%d_%d-%d.%s",n/10,n%10,k,t,jobnr,APP);
       lstfile=fopen(lst,"wb");
      }

    if(asciistdout)
       autfile=stdout;
    else
    if(printall==1||toprint>0)
      {
       sprintf(aut,"%d%d_%d_%d-%d.asc",n/10,n%10,k,t,jobnr);
       autfile=fopen(aut,"w");
      }
}

void closefiles()
{
    if((storeall==1||tostore>anz)&&!codestdout)
      {
       fclose(lstfile);
       if(anz==0)remove(lst);
      }

    if((printall==1||toprint>anz)&&!asciistdout)
      {
       fclose(autfile);
       if(anz==0)remove(aut);
      }
}

void movefiles()
{
    char neu[20];

    if((storeall==1||tostore>=anz)&&anz>0&&!codestdout)
      {
       sprintf(neu,"%d%d_%d_%d#%d.%s",n/10,n%10,k,t,jobnr,APP);
       remove(neu);
       rename(lst,neu);
      }

    if((printall==1||toprint>=anz)&&anz>0&&!asciistdout)
      {
       sprintf(neu,"%d%d_%d_%d#%d.asc",n/10,n%10,k,t,jobnr);
       remove(neu);
       rename(aut,neu);
      }
}

void run()
{
	/********** -m Modus **********/
 if(jobs==0||jobnr==0||jobnr>jobs)
	    {
	     fprintf(stdout,"%d %d : keine erlaubten Werte fuer Option -m\n",jobnr,jobs);
	     return ;
	    }
 if(jobs>0)
   {
    openfiles();

    if(!efile)
       ergfile=stdout;
    else
      {
       sprintf(erg,"%d%d_%d_%d-%d.erg",n/10,n%10,k,t,jobnr);
       ergfile=fopen(erg,"w");
      }

    generate();

    closefiles(anz);

    movefiles(anz);

    if(efile)
      {
       fclose(ergfile);
       sprintf(neu,"%d%d_%d_%d#%d.erg",n/10,n%10,k,t,jobnr);
       remove(neu);
       rename(erg,neu);
      }
   }
 else
//start = clock();

/********** Normalmodus **********/

   {
    if(codestdout)
       lstfile=stdout;
    else
    if(storeall==1||tostore>0)
      {
       sprintf(lst,"%d%d_%d_%d-U.%s",n/10,n%10,k,t,APP);
       lstfile=fopen(lst,"wb");
      }

    if(asciistdout)
       autfile=stdout;
    else
    if(printall==1||toprint>0)
      {
       sprintf(aut,"%d%d_%d_%d-U.asc",n/10,n%10,k,t);
       autfile=fopen(aut,"w");
      }

    if(!efile)
       ergfile=stdout;
    else
      {
       sprintf(erg,"%d%d_%d_%d-U.erg",n/10,n%10,k,t);
       ergfile=fopen(erg,"w");
      }

    generate();

    if((storeall==1||tostore>anz)&&!codestdout)
      {
       fclose(lstfile);
       if(anz==0)remove(lst);
      }

    if((printall==1||toprint>anz)&&!asciistdout)
      {
       fclose(autfile);
       if(anz==0)remove(aut);
      }

    if(efile)
      {
       fclose(ergfile);
       sprintf(neu,"%d%d_%d_%d.erg",n/10,n%10,k,t);
       remove(neu);
       rename(erg,neu);
      }

    if((storeall==1||tostore>=anz)&&anz>0&&!codestdout)
      {
       sprintf(neu,"%d%d_%d_%d.%s",n/10,n%10,k,t,APP);
       remove(neu);
       rename(lst,neu);
      }

    if((printall==1||toprint>=anz)&&anz>0&&!asciistdout)
      {
       sprintf(neu,"%d%d_%d_%d.asc",n/10,n%10,k,t);
       remove(neu);
       rename(aut,neu);
      }
   }
}
void delay(int n)
{
	int i,j,k,t;
	t=0;
	for(j=0;j<n;j++)
	  {
		  for(i=0;i<7000;i++)
		  {
          //   for (k=0;k<10000;k++)
		//	 {
                  t++;
		//	 }
		  }
	  }

}
void main(argc,argv) int argc;
char *argv[];
{
 
double nm1;
MPI_Status Stat;
  int rc;
  int mpi_size, mpi_rank;
  MPI_Init(&argc,&argv);      
  MPI_Comm_size(MPI_COMM_WORLD,&mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD,&mpi_rank);
/***********Init Dsort_A,Dsort_d,A....******/
  Asort_a=AMIN;
 Asort_d=INF;
Dsort_a=INF;
 Dsort_d=INF;
/*********** Parameter erkennen **********/

 if(argc<3)
   {
    fprintf(stdout,"zu wenige Parameter\n");
    return ;
   }

 n=(SCHAR)atoi(*++argv);
 k=(SCHAR)atoi(*++argv);
 argc-=2;

 if(argc>1&&(t=atoi(*(argv+1)))>0)
   {
    argv++;argc--;
   }
 else
    t=3;

 if(inputerror())return ;


/********** Optionen erkennen **********/

 while(--argc>0)
      {
       ++argv;
       if(!strcmp(*argv,"-e"))
	  efile=1;
       else
       if(!strcmp(*argv,"-c"))
	 {
          if(argc>1)
	     count=atoi(*(argv+1));
	  if(count>0)
	    {
	     argv++;
	     argc--;
	    }
	  else count=COUNTSTEP;
	 }
       else
       if(!strcmp(*argv,"-max"))
	 { 
          if(argc>1)
	     mid_max=atoi(*++argv);argc--;
	  if(mid_max==0)
	    {
	     fprintf(stdout,"%s : kein erlaubter Wert fuer Option -max\n",*argv);
	     return;
	    }
	 }
       else
       if(!strcmp(*argv,"-split"))
	 {
          if(argc>1)
	     splitlevel=atoi(*++argv);argc--;
	  if(splitlevel==0)
	    {
	     fprintf(stdout,"%s : kein erlaubter Wert fuer Option -split\n",*argv);
	     return;
	    }
	 }
       else
       if(!strcmp(*argv,"-s"))
	 {
	  if(argc>1)
            {
             if(!strcmp(*(argv+1),"stdout"))
	        codestdout=storeall=1;
	     else
	        tostore=atoi(*(argv+1));
            }
	  if(tostore>0||codestdout)
	    {
	     argv++;
	     argc--;
	    }
	  else storeall=1;
	 }
       else
       if(!strcmp(*argv,"-a"))
	 {
          if(argc>1)
            {  
             if(!strcmp(*(argv+1),"stdout"))
	        asciistdout=printall=1;
	     else
	        toprint=atoi(*(argv+1));
            }
	  if(toprint>0||asciistdout)
	    {
	     argv++;
	     argc--;
	    }
	  else printall=1;
	 }
       else
       if(!strcmp(*argv,"-m"))
	 {
          if(argc>1)
            {
	     jobstart=atoi(*++argv);
	    // jobnr=1;

             argc--;
            }
          if(argc>1)
            {
	     jobend=atoi(*++argv);
	     argc--;
            }
          if(argc>1)
            {
	     jobs=atoi(*++argv);
	     argc--;
            }
	 
	 }
       else
	 {
	  fprintf(stdout,"%s : keine erlaubte Option\n",*argv);
	  return ;
	 }
      }
 // ---Generate filename from mpi rank id-----
 /****************************Slaver Node ****************/
    if (mpi_rank) 
    {    
	  int r[100];
	  int jk=0;
	  FILE *fp;
	 // delay(mpi_rank);
	  char wname[50];
	  printf("Hi,I am slaver thread at cpu%d, I am waiting for task...\n",mpi_rank); 
         //fflush();
         sprintf(wname,"N%d_%d_%d_%d_NODE.txt",n,jobstart,jobend,jobs);
	 r[0]=mpi_rank;
	 //delay(mpi_rank);
	// FILE *fp;
     // if (mpi_rank>4000) delay(3*mpi_rank);
     r[1]=1; //Report status
	  //printf("Hi,I am slaver thread at cpu%d, I am waiting for task...\n",mpi_rank);
      //rc=MPI_Isend (&r,2,MPI_INT,0,98,MPI_COMM_WORLD,&Stat);
	  while(1)
	  { 
		  
	   // FILE *fp;
		r[0]=mpi_rank; //Send mpi_rank;
		rc=MPI_Isend (&r,1,MPI_INT,0,99,MPI_COMM_WORLD,&Stat);//Request task
            rc=MPI_Recv (&r,1, MPI_INT, 0, 100, MPI_COMM_WORLD,&Stat);//Receive task
        jobnr=r[0]; //Get block number
    //    fp = fopen(wname,"a");
		//fprintf(fp,"%d %d\n",mpi_rank,jobnr);
	//	fclose(fp);

        if (jobnr)
        {
	//		 printf("Calculate at block_number %d\n",jobnr);
        /**************Start to calculate*************/
	    start = clock();
	    anz=0;
        minnum=0;
        start_t=MPI_Wtime();
        run();
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        nm1=(n*(n-1))/2;
		fp = fopen(wname,"a");
        fprintf(fp,"NODE,%f,%d,%f,%llu,%d,%d,%d\n",(double)Asort_a/nm1,Asort_d,duration,anz,jobnr,mpi_rank,minnum);
	    fclose(fp);
		}
	    else  // Exit thread
	     {
			// print("Finish task");
			 break;
		 }
	
      }
      MPI_Finalize();
      return;
   }
 /****************************Manager Node ******************/
     else
     { 
	   int tasklist[50000][2]={0};
	   int ready_sum=0;
	   int node_s[10000];
	   int k1=1;
	   int taskfinish=0;
	   int tasknum=jobend-jobstart+1;
	   for (k1=0;k1<tasknum;k1++)
	   {
		   tasklist[k1][0]=jobstart;
		   tasklist[k1][1]=0;
		 //   printf("%d %d\n", tasklist[k1][0],tasklist[k1][1]);
		   	jobstart++;
	   }

	   printf("Start from %d to %d\n",jobstart,jobend); 
	   //printf("Hi,I am master thread at cpu%d, I am waitting report form each core...\n",mpi_rank); printf("Hi,I am master thread at cpu%d, I am waitting report form each core...\n",mpi_rank); 
	  /*
	   while(1)
	   {
	      rc = MPI_Recv(&node_s, 2, MPI_INT, MPI_ANY_SOURCE,98, MPI_COMM_WORLD,&Stat);
	      ready_sum=ready_sum+node_s[1];
	      printf("Report ready from core%d\n",node_s[0]);
	      if (ready_sum==mpi_size-1) break;
       }
	  */
   /*    
       printf("Hi,I am master thread at cpu%d, %d cores said that they are ready...\n",mpi_rank,mpi_size-1); 
       printf("Hi,I am master thread at cpu%d, I will arrange task...\n",mpi_rank);
  */     
       while(1)
       { 
		  int source;
		  rc = MPI_Recv(&node_s, 1, MPI_INT, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD,&Stat);
                  source=node_s[0];
		  node_s[0]=tasklist[taskfinish][0];
		  printf("Finshed %d blocks, will arrange task %d to core %d\n",taskfinish,node_s[0],source);
		  tasklist[taskfinish][1]=1;
		  taskfinish++;
		  rc=MPI_Send(&node_s,1,MPI_INT,source,100,MPI_COMM_WORLD);//Send task
         // printf("%d-------------%d\n",taskfinish,tasknum);
		  if (taskfinish==tasknum)
		  {  //if task finish,exit
			  
			  int k1=0;
			  while(1)
			  {
				  rc = MPI_Recv(&node_s, 1, MPI_INT, MPI_ANY_SOURCE, 99, MPI_COMM_WORLD,&Stat);
				  source=node_s[0];
				  node_s[0]=0;		  
				  rc=MPI_Isend(&node_s,1,MPI_INT,source,100,MPI_COMM_WORLD,&Stat);//Send 
				  k1++;
				  
				  if (k1==(mpi_size-1)) break;
			  }
			  break;
			// MPI_Art();
		  }
	   }
	   MPI_Finalize();
	   return;
	 }
 //---------------------

   
 


MPI_Finalize();
 return;
}


