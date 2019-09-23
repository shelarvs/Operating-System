#include<stdio.h>
void accept();

void del();
void search();

struct database
{
    char nm[20],city[20],city1[20];
    int uid;
}d[10];

int main()
{
    int n,x;
    do
    {
        printf("\n1.Accept\n2.Search.\n3.Delete.");
        printf("\n\tEnter your choice.:");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                printf("\nEnter the no.of persons in a database:");
                scanf("%d",&n);
                accept(n);
                break;
           
            case 2:
                search();
                break;
           
            case 3:
                del();
                break;
            default:
                printf("Invalid entry");

        }
    }while(x>0&&x<=3);
    return 0;
}

void accept(int n)
{
    int i,j;
    FILE *fp;
    fp=fopen("database.txt","w");
    if(fp==NULL)
    {
        printf("\nFile not created.");
    }
    else
    {
        for(i=0;i<n;i++)
        {
            printf("\nEnter the Name of person %d:",i+1);
            scanf("%s",d[i].nm);
            printf("\nEnter the birth place of person %d:",i+1);
            scanf("%s",d[i].city);
            printf("\nEnter the current city of person %d:",i+1);
            scanf("%s",d[i].city1);
            printf("\nEnter unique id of person %d:",i+1);
            scanf("%d",&d[i].uid);
            for(j=0;j<i;j++)
            {
                if(d[i].uid==d[j].uid)
                {
                    printf("\nDuplicate entry not allowed.");
                    i--;
                    break;
                }
            }
        }
        for(i=0;i<n;i++)
        fprintf(fp,"\n%s\t%s\t\t%s\t\t%d",d[i].nm,d[i].city,d[i].city1,d[i].uid);
    }
    fclose(fp);
 }



void search()
{
    FILE *fp;
	int i=0,m,flag=0;
	fp=fopen("database.txt","r");
	if(fp==NULL)
    {
        printf("\nFile not created.");
    }
    else
    {
        printf("Enter the unique id. to be searched:");
        scanf("%d",&m);
        while(!feof(fp))
        {
            fscanf(fp,"\n%s\t%s\t\t%s\t\t%d",d[i].nm,d[i].city,d[i].city1,&d[i].uid);
            if(m==d[i].uid)
			{
				printf("\nName: %s",d[i].nm);
				printf("\nBirth place: %s",d[i].city);
				printf("\nCurrent city: %s",d[i].city1);
				printf("\nUnique id.: %d",d[i].uid);
				flag=1;
			}
			i++;
        }
    }
	fclose(fp);
	if(flag!=1)
        printf("Record not found.");
}



void del()
{
    FILE *fp;
	int i=0,m,temp,flag=0;
	printf("\nEnter the Unique id. to be deleted : ");
	scanf("%d",&m);
	fp=fopen("database.txt","r");
	if(fp==NULL)
	{
		printf("\nFile not created.");
	}
	else
	{
		while(!feof(fp))
		{
			fscanf(fp,"\n%s\t%s\t\t%s\t\t%d",d[i].nm,d[i].city,d[i].city1,&d[i].uid);
			i++;
			temp=i;
		}
	}
	fclose(fp);
	fp=fopen("database.txt","w");
	for(i=0;i<temp;i++)
	{
		if(m==d[i].uid)
		{
			flag=1;
		}
		else
		{
			fprintf(fp,"\n%s\t%s\t\t%s\t\t%d",d[i].nm,d[i].city,d[i].city1,d[i].uid);
		}
	}
	fclose(fp);
	if(flag!=1)
	{
		printf("\nEntry not found.");
	}
	else
	{
		printf("\nEntry deleted successfully!!!");
	}
}


