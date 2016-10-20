#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
typedef struct node_tag
{
	char employee_name[20],project_name[20],employee_address[50];
    int hrs,phone_no;
	node_tag *next; 
}node;
void initialize(node * head)
{
    head=NULL;
}
void sortedInsert(node** head_ref,node* new_node)
{
    node* current;
    if (*head_ref == NULL || strcmp((*head_ref)->employee_name, new_node->employee_name)>0||(strcmp((*head_ref)->employee_name,new_node->employee_name)==0&&strcmp((*head_ref)->project_name,new_node->project_name)>0))
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next!=NULL &&(strcmp(current->next->employee_name,new_node->employee_name)<0))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
node *makenode(node *head,node *tmp)
{
	node * new_node;
	new_node=(node *)malloc(sizeof(node));
    strcpy(new_node->project_name,tmp->project_name);
	strcpy(new_node->employee_name,tmp->employee_name);
    new_node->hrs=tmp->hrs;
	new_node->next=head;
	head=new_node;
	return head;	
}
node *insert(node * head,FILE *fp)
{
	node *tmp;
	node *new_node;
    int hours,flag;
	char name[20],pname[20];
    char ch1[80],ch2[30];
    int n;
	while(fscanf(fp,"%s",ch1)==1)
    {
    fscanf(fp,"%s%d",ch2,&n);
	flag=0;	
	tmp=head;
	
    while(tmp!=NULL&&flag==0)
	{
		if((strcmp(tmp->employee_name,ch1)==0)&&(strcmp(tmp->project_name,ch2)==0))
		{
			tmp->hrs=n;
			printf("\nupdated\n");
			printf("_______________________________________________________________________\n");
			flag=1;
		}
		tmp=tmp->next;
    }
    if(flag==0)		
	{
	        new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->employee_name,ch1);
            strcpy(new_node->project_name,ch2);
            new_node->hrs=n;
            new_node->next=NULL;
            sortedInsert(&head,new_node);
	        printf("\ninserted\n");
	        printf("_______________________________________________________________________\n");
	}
    }
    fclose(fp);
	return head;
}
node * deletenode(node * head)
{
	node * tmp,*prev;
	int data,flag;
	char pname[20],name[20];
	prev=tmp=head;
	printf("\nenter the employee name\n");
	scanf("%s",name);
	printf("\nenter the project name\n");
	scanf("%s",pname);
	flag=0;
	if ((strcmp(tmp->project_name,pname)==0)&&(strcmp(tmp->employee_name,name)==0))
	{
		head=tmp->next;
		free(tmp);
		printf("\ndeleted\n");
		printf("_______________________________________________________________________\n");
		flag=1;
	}
	else
	{
		tmp=tmp->next;
		while(tmp!=NULL&&flag==0)
		{
			if((strcmp(tmp->project_name,pname)==0)&&(strcmp(tmp->employee_name,name)==0))
			{
				prev->next=tmp->next;
				free(tmp);
				flag=1;
				printf("\ndeleted\n");
				printf("_______________________________________________________________________\n");
			}
		    tmp=tmp->next;
		    prev=prev->next;
		}
    }
    if(flag==0)
    {
    	printf("\nno such entry found\n");
    	printf("_______________________________________________________________________\n");
    }
    return head;
}
void * getnumrecords(node * head)
{
	node * ptr;
	ptr=head;
	int count=0;
	while(ptr!=NULL)
	{
		count++;
		ptr=ptr->next;
	}
	printf("\nno of active records is %d\n",count);
	printf("_______________________________________________________________________\n");
}


void getmaxnumhours(node * head)
{
	FILE *fp;
	node *temp,*tmp,*new_node=NULL;
	tmp=head;
	int max;
	char pname[20];
	printf("enter the project name\n");
	scanf("\n%s",pname);
    max=0;
    while(tmp!=NULL)
    {
    	if((strcmp(tmp->project_name,pname)==0))
        {
           	if(tmp->hrs>max)
        	{
        		max=tmp->hrs;
        		if(new_node!=NULL)
        		{
        			free(new_node);
        		}
        		new_node=makenode(new_node,tmp);
           	}
        	else if(tmp->hrs==max)
        	{
        		new_node=makenode(new_node,tmp);
        	}
        }
        tmp=tmp->next;
    }
    printf("\nmax no of hrs is %d",max);
    printf("\nemployees' working on the project\n");
	while(new_node!=NULL)
    {
    	printf("\n%s",new_node->employee_name);
    	new_node=new_node->next;
    }
	printf("\n_______________________________________________________________________\n");
}

void print(node * ptr)
{
	node * tmp;
	tmp=ptr;
	while(tmp!=NULL)
	{
	printf("\nemployee name-----%s",tmp->employee_name);
	printf("\nproject name-----%s",tmp->project_name);
	printf("\nnumber of hours-----%d\n",tmp->hrs);
	printf("_______________________________________________________________________\n");
	tmp=tmp->next;
	}
}

void removeduplicates()
{   
    node *ptr1, *ptr2, *dup;
	node *new_node,*head;
    FILE *fp;
    fp = fopen("db1.txt","r");
    char ch1[80],ch2[30];
    int n;
	while(fscanf(fp,"%s",ch1)==1)
    {
    fscanf(fp,"%s%d",ch2,&n);
    new_node=(node *)malloc(sizeof(node));
    strcpy(new_node->employee_name,ch1);
    strcpy(new_node->project_name,ch2);
    new_node->hrs=n;
    new_node->next=head;
    head=new_node;
    } 
    ptr1=head;
    while(ptr1 != NULL && ptr1->next != NULL)
    {
      ptr2 = ptr1;
      while(ptr2->next != NULL)
      {
         if(strcmp(ptr1->employee_name,ptr2->next->employee_name)==0&&strcmp(ptr1->project_name,ptr2->next->project_name)==0)
         {
            dup = ptr2->next;
            ptr2->next = ptr2->next->next;
            free(dup);
         }
         else
         {
            ptr2 = ptr2->next;
         }
      }
      ptr1 = ptr1->next;
    }
    print(head);
}

void list_union (node * head1,node * head2)
{
	node *new_node=NULL;
	node *head=NULL;
	while((head1!=NULL)&&(head2!=NULL))
	{
		if(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->project_name,head2->project_name)<0)
		{
		    new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
		    head1=head1->next;
		}
		else if(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->project_name,head2->project_name)>0)
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head2->project_name);
            strcpy(new_node->employee_name,head2->employee_name);
            new_node->hrs=head2->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head2=head2->next;
		}
		else if(strcmp(head1->employee_name,head2->employee_name)<0)
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
		}
		else if(strcmp(head1->employee_name,head2->employee_name)>0)
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head2->project_name);
            strcpy(new_node->employee_name,head2->employee_name);
            new_node->hrs=head2->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head2=head2->next;
		}
		else if(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->project_name,head2->project_name)==0)
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
			head2=head2->next;
		}
	}
	if(head1!=NULL)	
	{
	    while(head1!=NULL)
        {
            new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
        }
    }
    else if(head2!=NULL)
    {
        while(head2!=NULL)
        {
            new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head2->project_name);
            strcpy(new_node->employee_name,head2->employee_name);
            new_node->hrs=head2->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head2=head2->next;
        }
    }
	print(head);
}

void list_intersection (node *head1,node * head2)
{
	node * new_node=NULL;
	node *head=NULL;
    while((head1!=NULL)&&(head2!=NULL))
    {
    	if(strcmp(head1->employee_name,head2->employee_name)<0||(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->project_name,head2->project_name)<0))
    	{
    		head1=head1->next;
    	}
    	else if(strcmp(head1->employee_name,head2->employee_name)==0)
    	{
    		new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
    		head2=head2->next;
    	}
    	else
    	{
    		head2=head2->next;
    	}
    }
    print(head);
}

void list_difference(node *head1,node *head2) 
{
	node * new_node=NULL;
	node *head=NULL;
	while((head1!=NULL)&&(head2!=NULL))
	{
		if(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->employee_name,head2->employee_name)==0)
		{
			head1=head1->next;
			head2=head2->next;
		}
		else
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
		}
	}
	if(head1!=NULL)	
	{
	    while(head1!=NULL)
        {
            new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
        }
    }
	print(head);
}

void list_symmetric_difference(node *head1,node *head2)
{
	node * new_node=NULL;
	node *head=NULL;
	while((head1!=NULL)&&(head2!=NULL))
	{
		if(strcmp(head1->employee_name,head2->employee_name)==0&&strcmp(head1->employee_name,head2->employee_name)==0)
		{
			head1=head1->next;
			head2=head2->next;
		}
		else
		{
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head2->project_name);
            strcpy(new_node->employee_name,head2->employee_name);
            new_node->hrs=head2->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
			head2=head2->next;
		}
	}
	if(head1!=NULL)	
	{
	    while(head1!=NULL)
        {
            new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head1=head1->next;
        }
    }
	else if(head2!=NULL)
    {
        while(head2!=NULL)
        {
            new_node=(node *)malloc(sizeof(node));
            strcpy(new_node->project_name,head1->project_name);
            strcpy(new_node->employee_name,head1->employee_name);
            new_node->hrs=head1->hrs;
            new_node->next=NULL;
            sortedInsert(&head, new_node);
			head2=head2->next;
        }
    }
	print(head);
}

main()
{
	int n,a;
	node * ptr;
	node *head1,*head2;
	head1=NULL;
	head2=NULL;
	do
	{
	printf("enter\n1.for insertion\n2.for printing\n3.for deleting\n4.to get number of active records\n5.to get max number of hours\n6.list union\n7.lsit intersection\n8.list difference\n9.list symmetric difference\n10.list unique\n");
	scanf("\n%d",&n);
	printf("______________________________________________________________");
	switch(n)
	{
		case 1:
			{
				int i;
				FILE *fp;
                printf("\nwhich database you want to enter 1 or 2");
				scanf("\n%d",&i);
				if(i==1)
				{
					fp = fopen("db1.txt","r");
				    head1=insert(head1,fp);
			    }
			    else
			    {
			    	fp = fopen("db2.txt","r");
			    	head2=insert(head2,fp);
			    }
			}
			break;
	    case 2:
	        {
	        	int i;
				printf("\nwhich database you want to print 1 or 2");
				scanf("\n%d",&i);
				if(i==1)
				{
	                print(head1); 
	            }
			    else
			    {
			    	print(head2);
			    }
		    }
		    break;
		case 3:
			{
				int i;
				printf("\nwhich database you want to delete 1 or 2");
				scanf("\n%d",&i);
				if(i==1)
				{
				    head1=deletenode(head1);
				}
			    else
			    {
			    	head2=deletenode(head2);
			    }
			}
			break;
		case 4:
			{
				int i;
				printf("\nwhich database you want to get record 1 or 2");
				scanf("\n%d",&i);
				if(i==1)
				{
				    getnumrecords(head1);
				}
			    else
			    {
			    	getnumrecords(head2);
			    }
			}
			break;
		case 5:
			{
				int i;
				printf("\nwhich database you want to get record 1 or 2");
				scanf("\n%d",&i);
				if(i==1)
				{
				    getmaxnumhours(head1);
				}
			    else
			    {
			    	getmaxnumhours(head2);
			    }
			}
			break;
		case 6:
			{
				list_union(head1,head2);
			}
			break;
		case 7:
			{
				list_intersection(head1,head2);
			}
			break;
		case 8:
			{
				list_difference(head1,head2);
			}
			break;
		case 9:
			
			{
				list_symmetric_difference(head1,head2);
			}
			break;
		case 10:
			{
				removeduplicates();
			}
			break;
    
	}
    printf("\nenter 1 if you want to continue\n");
    scanf("%d",&a);
    }
	while(a==1);
	getch();	
}
