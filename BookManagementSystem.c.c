#include<stdio.h>
#include<stdlib.h>
#define MAX_CHARACTER 50
#define false 0
#define true 1


struct book
{
	int accessno;
	char author[MAX_CHARACTER];
	char title[MAX_CHARACTER];
	int price;
	
};
typedef struct book BOOK;

struct node
{
	BOOK info;
	int index;
	struct node *link;
};
typedef struct node NODE;

NODE *insert(NODE *);
NODE *sort(NODE *);
void search(NODE *);
void display(NODE *);
void displayAuthor(NODE *);
NODE *getnode(void);
NODE *update(NODE *);

int main()
{
	int choice,found=false,i,clear=0,enterChar=0;
	char username[30],password[30],user[30],pass[30],c;
	NODE *front,*temp;
	front = NULL;
	temp=NULL;


	system("clear");
	
	do
	{
	   printf("\n|------------WELCOME-------------------|\n");
	   printf("|1.Reset the user name and password    |\n");
	   printf("|2.Load into book maintainence software|\n");
	   printf("|--------------------------------------|\n");
	   printf("\nEnter your choice : ");
	   scanf("%d",&choice);
	   
	   switch(choice)
	   {
	       case 1:  while(getchar() != '\n'){}
	               printf("\nSet the username :");
	               scanf("%[^\n]s",username);
	               while(getchar() != '\n'){}
	               printf("\nSet the password:");
	               scanf("%[^\n]s",password);
	               while(getchar() != '\n'){}
	
	               printf("\nUsername and Password has been set\n");
	               found=true;
	               break;
	       case 2:
	           if(found == true)
	           {
                   do
                   {
                        i=0;
                        if(enterChar==0)while(getchar() != '\n'){}
                        printf("\nEnter the username : ");
                        scanf("%[^\n]s",user);
                        while(getchar() != '\n'){}
                        printf("\nEnter the password : ");
                        while((c=getch()))
                        {
                            if(c=='\r')
                                break;
                            pass[i]=c;
                            printf("*");
                            i++;
	                   
                        }
                        pass[i]='\0';
                  
                        if(strcmp(user,username) == 0 && strcmp(pass,password)== 0 )
                        {

                            clear=1;

                        }
                        else
                        {
                            printf("\n\nInvalid username or password please try once again\n\n");
                            enterChar=1;
                        }
                   }while(clear !=1);
                  }
	              else
	              {
	                   printf("\n\nPlease set the username and password\n\n");
	
	
                   }
	               break;
	       default:
	           printf("\nWRONG OPTION ENTERED\n");
	      }
	}while(clear!=1 || choice != 2 );
	do
	{
		printf("\n_____________________________________________________\n");
		printf("|                WELCOME TO SJCE BOOK DEPOT         |\n");
		printf("|------------------------MENU-----------------------|\n");
		printf("|1.Insert the book information       		    |\n");
		printf("|2.Sort the books by access number   		    |\n");
		printf("|3.Search for book by access number 		    |\n");
		printf("|4.Display all book information      		    |\n");
		printf("|5.Display all authors with their specific book     |\n");
		printf("|6.Update price information of all books with title |\n");
		printf("|7.Quit the program                                 |\n");
		printf("|___________________________________________________|\n");
		printf("\nEnter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				front = insert(front);
				break;
			
			case 2:
				front = sort(front);
				printf("\nSorted information of all books\n");
				display(front);
				break;

			case 3:
				front=sort(front);
				search(front);
				break;

			case 4:
				display(front);
				break;

			case 5:
				displayAuthor(front);
				break;
	
			case 6:
				front = update(front);
				break;
			
			case 7:
				printf("THANK YOU VISIT AGAIN\n");
				free(front);
				break;
			default:
				printf("Wrong option\n");


		}//end of switch statement

	}while(choice != 7);
}//end of main.


NODE *insert(NODE *front)
{
	NODE *newnode,*temp;

	newnode=getnode();
	
	printf("\nEnter the Book Access Number : ");
	scanf("%d",&newnode->info.accessno);
	while(getchar()!='\n'){}
	printf("\nEnter the Author of the book : ");
	scanf("%[^\n]s",newnode->info.author);
	while(getchar()!='\n'){}
	printf("\nEnter title of the book      : ");
	scanf("%[^\n]s",newnode->info.title);

	printf("\nEnter price of the book      : ");
	scanf("%d",&newnode->info.price);

	if(front == NULL)
		return(newnode);
	else
	{
		temp=front;
		while(temp->link != NULL)
			temp=temp->link;
		temp->link=newnode;
		return(front);
	}
}

NODE *sort(NODE *front)
{
	NODE *temp,*pn,*nn;
	int i,j,count=0;	
	
	temp=front;
	if(front == NULL)
	{
		//printf("Sorting is not possible as no books are present in the list\n");
		return(NULL);
	}
	while(temp!=NULL)
	{
		count++;
		temp=temp->link;
	}	
	
	for(i=0;i<count;i++)
	{
		pn=NULL;
		temp=front;
		for(j=0;j<count-i-1;j++)
		{
			//printf("hi\n\n");
			if(temp->info.accessno > temp->link->info.accessno)
			{
				if(pn==NULL)
				{
					nn=temp->link;
					temp->link=nn->link;
					nn->link=temp;
					front=nn;
					pn=nn;
					
				}
				else
				{
					nn=temp->link;
					temp->link=nn->link;
					nn->link=temp;
					pn->link=nn;
					pn=nn;
				}
        	}
			else
			{
				pn=temp;
				temp=temp->link;
				if(temp == NULL)break;
			}
		}
	}
	
	return(front);

}

void search(NODE *front)
{

	NODE *h,*l,*mid,*temp;
	int midvalue,value,accno,flag=0;

	
	if(front == NULL)
		printf("Searching is not possible as no books are present in depot\n");
	else
	{
		
		printf("Enter the access no of the book to be searched : ");
		scanf("%d",&accno);
		value=0;
		temp=front;
		while(temp != NULL)
		{
			temp->index=value++;
			temp=temp->link;
		}

		l=front;
		temp=front;
		while(temp->link != NULL)
			temp=temp->link;
		h=temp;
		mid=NULL;
		//printf("HI\n");
		do
		{
			midvalue=((h->index)+(l->index))/2;

			if(l->index != 0)
			{
				temp=mid;	
				mid=l;
			}
			else
			{
				temp=NULL;
				mid=l;
			}
			while(mid->index != midvalue)
			{
				temp=mid;
				mid=mid->link;
			}	
			
			if(mid->info.accessno == accno)
			{
				printf("\nSearch is Successful\n");
				flag=1;
				break;
			}
			else if(h==l)
				break;
			if(accno > mid->info.accessno)
			{
				l=mid->link;
				if(l==NULL)break;
			}			
			else
			{
				h=temp;
				if(h==NULL)break;
			}
		}while(l->index <= h->index);
		
		if(flag==0)
			printf("Unsuccessful search\n");


	}



}

void display(NODE *front)
{
	NODE *temp;
	
	if(front == NULL)
	{
		printf("No books are present in the depot\n");
	}
	else
	{
		temp=front;
		printf("________________________________________________________________________\n");
		printf("|                                                                      |\n");
		printf("|---------INFORMATION OF ALL THE BOOKS PRESENT IN THE DEPOT------------|\n");
		printf("|______________________________________________________________________|\n");
		printf("| BOOK ACCESS No. |       AUTHOR       |        TITLE       |  PRICE   |\n");
		printf("|_________________|____________________|____________________|__________|\n");    	
		while(temp != NULL)
		{
			printf("|%-17d|%-20s|%-20s|%-10d|\n",temp->info.accessno,temp->info.author,temp->info.title,temp->info.price);
			temp=temp->link;

		}
		printf("|_________________|____________________|____________________|__________|\n");
	}
}

void displayAuthor(NODE *front)
{

	NODE *temp;
	
	if(front == NULL)
		printf("No books are present in the depot\n");
	else
	{
		temp=front;
		
		printf("__________________________________________________\n");
		printf("|                                                |\n");
		printf("|INFORMATION ALL AUTHORS WITH THEIR SPECIFIC BOOK|\n");
		printf("|________________________________________________|\n");
		printf("|       AUTHOR           |           TITLE       |\n");
		printf("|________________________|_______________________|\n");
		while(temp != NULL)
		{
			printf("|%-24s|%-23s|\n",temp->info.author,temp->info.title);
			temp=temp->link;

		}
		printf("|________________________|_______________________|\n");

	}





}

NODE *getnode(void)
{

	NODE *newnode;
	newnode=(NODE *)malloc(sizeof(NODE));
	newnode->link=NULL;
	return(newnode);
}

NODE *update(NODE *front)
{
	NODE *temp;
	int value;

	if(front == NULL)
	{
		printf("No books are present in the depot for update\n");
		return(NULL);
	}	
	else
	{
		temp=front;
		while(temp != NULL)
		{
			printf("For book titled ---> %s\n",temp->info.title);
			printf("Enter 0 or 1 (0-->Price decrement and 1-->price Increment)\n");
			scanf("%d",&value);
			
			if(value == 0)
			{
				printf("Enter the value to decremented : ");
				scanf("%d",&value);					
				temp->info.price=temp->info.price-value;
				
			}
			else 
			{
				printf("Enter the value to Incremented : ");
				scanf("%d",&value);
			
				temp->info.price=temp->info.price-value;
				
			}
			temp=temp->link;
		}
	
		return(front);
	}
	
}

