#include<stdio.h>
#include<stdlib.h>
struct sjf{
    int arr,burst,firstt,i,status,burl,compt,wt,tat;
}*run=NULL;

int n,tq=10,px=0;
struct node
{
    struct sjf *q;
    struct node *next;
}*start=NULL,*last,*cn;

int main()
{
    int i=0 ;
	printf("\nThe Number of the process to be executed :");
    scanf("%d",&n);
    int pl=n;  																//sjf to be created
    struct sjf p[n];
    for(i=0;i<n;i++)
    {
        printf("\nGive Arrival and Burst Time of process %d ",i+1);
        printf("\n\tArrival Time : ");
        scanf("%d",&p[i].arr);
        printf("\tBurst Time : ");
        scanf("%d",&p[i].burst);
        p[i].burl=p[i].burst;
        p[i].i=i+1;
        p[i].status=0;
        p[i].firstt=-1;
        if(p[i].arr>3)
            px++;
    }    

    int time=4,y=1; //cpu idle for first 3 time units
    while(pl!=0)
    {
        if(px!=0)
        {
        for(i=0;i<n;i++)
        {
            if(p[i].arr>3 && p[i].arr<=time && p[i].status==0)           //inside of the queue
            {
                if(start==NULL)
                {
                    p[i].status=1;
                    cn=malloc(sizeof(struct sjf));
                    cn->q=&p[i];
                    cn->next=NULL;
                    last=cn;
                    start=cn;
                }
                else{
                    p[i].status=1;
                    cn=malloc(sizeof(struct sjf));
                    cn->q=&p[i];
                	struct node *x;
                    x=start;
                    if((start->q->burl)>(cn->q->burl))
                    {
                        cn->next=start;
                        start=cn;
                    }
                    else
                    {
                        while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                        {
                            x=x->next;
                        }
                        cn->next=x->next;
                        x->next=cn;
                    }
                }
                px--;
            }
        }
        }
        if(px==0 && y==1)
        {
        	int i;
            for(i=0;i<n;i++)
            {
                if(p[i].arr<=3 && p[i].status==0) 									//in the queue
                {
                    if(start==NULL)
                    {
                        p[i].status=1;
                        cn=malloc(sizeof(struct sjf));
                        cn->q=&p[i];
                        cn->next=NULL;
                        last=cn;
                        start=cn;
                    }
                    else{
                        p[i].status=1;
                        cn=malloc(sizeof(struct sjf));;
                        cn->q=&p[i];
                        struct node *x;
                        x=start;
                        if((start->q->burl)>(cn->q->burl))
                        {
                            cn->next=start;
                            start=cn;
                        }
                        else
                        {
                            while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                            {
                                x=x->next;
                            }
                            cn->next=x->next;
                            x->next=cn;
                        }
                    }
                }
            }
            y--;
        }
        if(run==NULL)   																//sjf execution
        {
            if(start!=NULL)
            {
                run=start->q;
                start=start->next;
                if(run->firstt==-1)
                {
                    run->firstt=time;
                }
                if(run->burl<=tq)
                {
                    printf("\nsjf P%d running from time= %d sec to time= %d sec.",run->i,time,time+run->burl);
                     
                    time=time+run->burl;
                    run->burl=0;
                    run->compt=time;
                    run->status=2;
                    pl--;
                }
                else if(run->burl>tq)
                {
                    printf("\nsjf P%d running from time= %d sec to time= %d sec.",run->i,time,time+tq);
                     
                    time=time+tq;
                    run->burl=run->burl-tq;
                    run->compt=time;
                    if(start==NULL)
                    {
                        cn=malloc(sizeof(struct sjf));
                        cn->q=run;
                        cn->next=NULL;
                        last=cn;
                        start=cn;
                    }
                    else
                    {
                        cn=malloc(sizeof(struct sjf));
                        cn->q=run;
                        struct node *x;
                        x=start;
                        if((start->q->burl)>(cn->q->burl))
                        {
                            cn->next=start;
                            start=cn;
                        }
                        else
                        {
                            while(x->next!=NULL && x->next->q->burl < cn->q->burl)
                            {
                                x=x->next;
                            }
                            cn->next=x->next;
                            x->next=cn;
                        }
                    }
                }
            }
            run=NULL;
        }
    }

    int awt=0,att=0;
    for(i=0;i<n;i++)
    {
        p[i].tat=((p[i].compt)-(p[i].arr));
        p[i].wt=((p[i].tat)-(p[i].burst));
        awt=awt+p[i].wt;
        att=att+p[i].tat;
    }
    awt=awt/n;
    att=att/n;
    printf("\n\n\nResult after scheduling  :");
    printf("\n================================================================\n");
    printf("\n\n\tProcess\tAT\tBT\tTAT\tWT\n\n");
    printf("\n================================================================\n");
    for(i=0;i<n;i++)
   {
        printf("\tP%d\t%d\t%d\t%d\t%d\n",p[i].i,p[i].arr,p[i].burst,p[i].tat,p[i].wt);
     	printf("\n");
    }
    printf("\nAverage  waiting time = %d ms ",awt);
     
    printf("\nAverage Turn Around Time = %d ms \n",att);
   void chart()       										//function to print Gantt chart of the problem 
{
    int i;
    printf("\n\nGANTT CHART");
    printf("\n================================================================\n");
    for(i=0;i<n;i++)
        printf("|\tP%d\t",p[i].i);
    printf("|\t\n");
    printf("\n================================================================\n");
    printf("\n");
    for(i=0;i<n;i++)
        printf("%d\t\t",p[i].wt);
    printf("%d",p[n].wt+p[n].burst);
    printf("\n");
 }
    chart();												//function call
}
