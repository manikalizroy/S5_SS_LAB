#include <stdio.h>
#include <stdlib.h>
int n,r[25],temp[25],initial,size;
void fcfs()
{
    printf("FCFS\n");
    int i,current=initial,seek=0;
    for(i=0;i<n;i++)
    {
        printf("%d -> ",current);
        seek+=abs(r[i]-current);
        current=r[i];
    }
    printf("%d",current);
    printf("\nTotal head movement(seek time) : %d\n",seek);
}
void scan()
{
    printf("SCAN\n");
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        printf("%d -> ",current);
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    printf("%d ->",current);
    seek+=abs(size-1-current);
    current=size-1;
    for(i=index-1;i>=0;i--)
    {
        printf("%d -> ",current);
        seek+=abs(current-temp[i]);
        current=temp[i];
    }
    printf("%d",current);
    printf("\nTotal head movement(seek time) : %d\n",seek);
}
void cscan()
{
    printf("CSCAN\n");
    int i,j,temp_v,current=initial,seek=0,index;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(temp[j] > temp[j+1])
            {
                temp_v=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=temp_v;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        if(current < temp[i])
        {
            index=i;
            break;
        }
    }
    for(i=index;i<n;i++)
    {
        printf("%d -> ",current);
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    printf("%d ->",current);
    seek+=abs(size-1-current);
    current=size-1;
    printf("%d -> ",current);
    seek+=current;
    current=0;
    for(i=0;i<index;i++)
    {
        printf("%d -> ",current);
        seek+=abs(temp[i]-current);
        current=temp[i];
    }
    printf("%d",current);
    printf("\nTotal head movement(seek time) : %d\n",seek);
}

int main()
{
    int i;
    printf("How many requests ? : ");
    scanf("%d",&n);
    printf("Enter the request sequence : ");
    for(i=0;i<n;i++)
        scanf("%d",&r[i]);
    for(i=0;i<n;i++)
        temp[i]=r[i];
    printf("Enter the total disk size : ");
    scanf("%d",&size);
    printf("Enter the initial head position : ");
    scanf("%d",&initial);
    fcfs();
    scan();
    cscan();
}

