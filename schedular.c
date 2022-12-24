 #include <stdio.h>
void roundrobinWOH(int wt[],int rem_bt [], int qt , int bt [], int n);
void roundrobinOH(int wt[],int rem_bt [], int qt , int bt [], int n, int oh);
void shortestjobfirst(int bt [],int n);
float RR1awt, RR2awt, SJFawt;
float RR1atat, RR2atat, SJFatat;
int main() {
   
   /*
        n = number of processes
        i = looping
        qt = quantum time
        count = keep track of number of processes
        sq & temp = temporary variables
        bt = burst time
        wt = waiting time
        tat = turn around time
        rem_bt = remaining burst time
        awt = average waiting time
        atat = average turn around time
   */

   int n,i,qt;
   int count = 0;
   int temp, sq = 0;
   int bt[10],wt[10],tat[10],rem_bt[10];
   float awt = 0, atat = 0;
   int a = 0;
   int oh;

   
    // User Input for number of processes
   printf("Enter number of process:");
   scanf("%d", &n);

   // User Input for burst time of process
   printf("Enter burst time of process:");

    // if number of process are greater then 1 then a loop is required to assign each proccess along its burst time
   for(i=0; i<n; i++){
       scanf("%d", &bt[i]);
       rem_bt[i] = bt[i];
   }

   // User Input for quantum time 
   printf("Enter quantum time:");
   scanf("%d", &qt);

    // User Input for overhead
    printf("Enter overhead:");
    scanf("%d", &oh);
    roundrobinWOH(wt,rem_bt,qt,bt,n); //roundrobin without overhead
    printf("\n");
    roundrobinOH(wt,rem_bt,qt,bt,n, oh); //roundrobin with overhead
    printf("\n");
    shortestjobfirst(bt,n); // shortest job first
    printf("\n");

    // Compare the average waiting time
    if(RR1awt<RR2awt & RR1awt<SJFawt){
        printf("Round Robin without overhead has the best waiting time");
    }
    else if(RR2awt<RR1awt & RR2awt<SJFawt){
        printf("Round Robin with overhead has the best waiting time");
    }
    else if(SJFawt<RR1awt & SJFawt<RR1awt){
        printf("Shortest Job First has the best waiting time");
    }
    else{
        printf("Both algorithms have the best waiting time");
    }

    //Compare the average turnaround time
    printf("\n");
    // Compare the average waiting time
    if(RR1atat<RR2atat & RR1atat<SJFatat){
        printf("Round Robin without overhead has the best turnaround time");
    }
    else if(RR2atat<RR1atat & RR2atat<SJFatat){
        printf("Round Robin with overhead has the best turnaround time");
    }
    else if(SJFatat<RR1atat & SJFatat<RR1atat){
        printf("Shortest Job First has the best turnaround time");
    }
    else{
        printf("Both algorithms have the best turnaround time");
    }
    

}

void roundrobinWOH(int wt[],int rem_bt [], int qt , int bt [],int n){
  int WT[10];
  int REM_BT[10];
  int BT[10];

  for(int i=0; i<10;i++){
    WT[i]=wt[i];
    REM_BT[i]=rem_bt[i];
    BT[i]=bt[i];
  }

   int i;
   int count = 0;
   int tat[10];
   int temp, sq = 0;
   float awt = 0, atat = 0;
   int a = 0;
        printf("Round Robin Algorithm (Without Overhead)\n"); 
    // calculate the waiting time for each process
       for(i=0; i<n; i++){
           if (REM_BT[i]>qt)
           {    
               WT[i] = a;
               a+=qt;
           }
           else{
               WT[i] = a;
               a+=REM_BT[i];
           }   
       }

   /*
        to check each whether the process burst time is taking longer or not than the quantum time
   */
   while (1)
   {
       for(i=0, count=0; i<n; i++){
           temp = qt;
           if (REM_BT[i]==0)
           {
               count++;
               continue;
           }
           if (REM_BT[i]>qt)
           {    
               REM_BT[i] = REM_BT[i] - qt; 
           }
           else
               if(REM_BT[i]>0){
                   temp = REM_BT[i];
                   REM_BT[i] = 0;
               }
               sq = sq + temp;
               tat[i] = sq;         
       }

       //  if all n numbers of processess are executed
       if(n == count){
           break;
       }
   }




   printf("\nprocess\tburst time\tturnaround time\twaiting time\n");


   for(i=0; i<n; i++)
   {
       awt = awt + WT[i];
       atat = atat +  tat[i];
       printf("\n%d\t%d\t\t%d\t\t%d", i+1, BT[i], tat[i], WT[i]);
   }

    awt = awt/n;
    atat = atat/n;
    
    RR1awt = awt;
    RR1atat = atat;


    printf("\n");
    printf("Average waiting time=%f\n",awt);
    printf("Average turnarond time=%f\n",atat);
    
}

void roundrobinOH(int wt[],int rem_bt [], int qt , int bt [],int n, int oh){
  int i;
  int WT[10];
  int REM_BT[10];
  int BT[10];

  for(int i=0; i<10;i++){
    WT[i]=wt[i];
    REM_BT[i]=rem_bt[i];
    BT[i]=bt[i];
  }

   int count = 0;
   int tat[10];
   int temp, sq = 0;
   float awt = 0, atat = 0;
   int a = 0;

   
   printf("Round Robin Algorithm (With Overhead)\n");

    // calculate the waiting time for each process
       for(i=0; i<n; i++){
           if (REM_BT[i]>qt)
           {    
               WT[i] = a;
               a+=qt+oh;
           }
           else{
               WT[i] = a;
               a+=REM_BT[i]+oh;
           }   
       }

   /*
        to check each whether the process burst time is taking longer or not than the quantum time
   */
   while (1)
   {
       for(i=0, count=0; i<n; i++){
           temp = qt;
           if (REM_BT[i]==0)
           {
               count++;
               continue;
           }
           if (REM_BT[i]>qt)
           {    
               REM_BT[i] = REM_BT[i] - qt; 
           }
           else
               if(REM_BT[i]>0){
                   temp = REM_BT[i];
                   REM_BT[i] = 0;
               }
               sq = sq + temp + oh;
               tat[i] = sq;
                 
       }

       //  if all n numbers of processess are executed
       if(n == count){
           break;
       }
   }

   for(i=0; i<n; i++){
       tat[i] = tat[i] - oh;
   }


   printf("\nprocess\tburst time\tturnaround time\twaiting time\n");


   for(i=0; i<n; i++)
   {
       awt = awt + WT[i];
       atat = atat +  tat[i];
       printf("\n%d\t%d\t\t%d\t\t%d", i+1, BT[i], tat[i], WT[i]);
   }

    awt = awt/n;
    atat = atat/n;

    RR2awt = awt;
    RR2atat = atat;

    printf("\n");
    printf("Average waiting time=%f\n",awt);
    printf("Average turnarond time=%f\n",atat);

}

void shortestjobfirst(int bt [],int n){
    int i, j, t, p[10], tat[10];
    float awt=0,atat=0;
    int BT[10], WT[10];

  for(int i=0; i<10;i++){
    BT[i]=bt[i];
  }
  printf("Shortest Job First\n");
   //applying bubble sort technique to sort according to their burst time  
  

  for(i=0;i<n;i++)
  {
      for(j=0;j<n-i-1;j++)
      {
          if(BT[j]>BT[j+1])
          {
              t=BT[j];
              BT[j]=BT[j+1];
              BT[j+1]=t;

              t=p[j];
              p[j]=p[j+1];
              p[j+1]=t;
          }
      }
  }

  printf("\nprocess\tburst time\tturnaround time\twaiting time\n");

  for(i=0;i<n;i++)
  {
      WT[i] = 0;
      tat[i] = 0;
      for (j=0; i < n; i++)
      {
          WT[i]=0;
          tat[i]=0;
          for(j=0;j<i;j++){
              WT[i] = WT[i] + BT[j];
          }
          tat[i] = WT[i] + BT[i];
          awt=awt+WT[i];
          atat=atat+tat[i];
          printf("\n%d\t%d\t\t%d\t\t%d", j+1, BT[i], tat[i] , WT[i]);
      }
      awt=awt/n;
      atat=atat/n;

      SJFawt = awt;
      SJFatat = atat;

      printf("\nAverage waiting time =%f\n",awt);
      printf("Average turn around time =%f", atat);
      

  }



 
}