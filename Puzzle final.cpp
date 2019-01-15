#include<iostream>
using namespace std;

struct node{
	int row,col;
	struct node *next;
};

/* THis Program takes inout from a file So take 
aaa---aa-a-aaa--a--aa---aaa--aa----aa-a-a-a-aaaa-aa-aa-a-aa--a--a-aa-aa-a
as the input and save it with name Puzzle.txt*/

int playerPoints=0;
void createNode(struct node**front,struct node **rear,int a,int b)
{
	struct node *trav=(*rear),*n;
	n=new node;
	n->row=a;
	n->col=b;
	n->next=NULL;
	if((*rear)==NULL)
	{
	   (*front)=n;
	   (*rear)=n;
	   trav=n;	
	}
	else
	{
		while(trav->next!=NULL)
		   trav=trav->next;
		trav->next=n;
		(*rear)=n;
	}
}

void dequeue(struct node** head)
{
	struct node* temp;
	if(*head==NULL)
	{
		cout<<"Queue Is Empty";
	}
	else
	{
		temp=(*head);
		*head=(*head)->next;
		delete(temp);
	}
}

void delAtEnd(struct node** base,struct node** top)
{
  struct node* head=(*base),*temp;
  if(*top==NULL)
   {
   	 cout<<"Underflow"<<endl;
   }
  else if((*base)->next==NULL)
  {
    delete((*base));
    (*base)=NULL;
  }
  else
  {
    while((*base)->next!=(*top))
    {
      *base=(*base)->next;
    }
    temp=(*base)->next;
    (*base)->next=NULL;
    (*top)=(*base);
    delete(temp);
    (*base)=head;
  }
  
}
void moveThePointer(struct node** base,struct node** top,char copyPuzzle[40][40],int i,int j)
{
	if(copyPuzzle[i][j]=='$')
  {
    copyPuzzle[(*top)->row][(*top)->col]=' ';
    delAtEnd(&(*base),&(*top));
    playerPoints--;
  }
  else
  {
    createNode(&(*base),&(*top),i,j);
	  copyPuzzle[(*top)->row][(*top)->col]='$';
    playerPoints++;
  }
}

void goBack(struct node** base,struct node** top,char puzzle[40][40])
{
	int m=1;
	while(m!=5&&(*base)->next!=NULL)
	{
		puzzle[(*top)->row][(*top)->col]=' ';
		delAtEnd(&(*base),&(*top));
		m++;
	}
	
}
void printPuzzle(char puzzle[40][40],int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			cout<<puzzle[i][j]<<" ";
		}
		cout<<endl;
	}
}
void printBoundary(char copyPuzzle[40][40],int n,int m)
{
	for(int i=0;i<n;i++)
	{
		copyPuzzle[i][0]='.';
		copyPuzzle[i][m-1]='.';
	}
	for(int i=0;i<m;i++)
	{
		copyPuzzle[0][i]='.';
		copyPuzzle[n-1][i]='.';
	}
}
void reachTheDestination(char copyPuzzle[40][40],char puzzle[40][40],int n,int m,int srow,int scol,int drow,int dcol)
{
	char ch;
	int chance=3;
  int i=srow,j=scol;
	struct node *stackBase=NULL,*stackTop=NULL,*tempTop=NULL,*tempBase=NULL;
	createNode(&stackBase,&stackTop,srow,scol);
  moveThePointer(&stackBase,&stackTop,copyPuzzle,i,j);
	do
	{
		printPuzzle(copyPuzzle,n,m);
		cout<<"\nPlayer Points :"<<playerPoints<<endl;
		if(!chance)
		{
		 	cout<<"Game Over\n";
		 	break;
		}  
		if(i==drow&&j==dcol)	
		{
		    cout<<"Destination Reached with Points :"<<playerPoints<<endl;
			break; 
		}
		cin>>ch;
		switch(ch)
		{
			
			case 'a':
				if(puzzle[i][j-1]=='*'&&j!=1)
				{
                    moveThePointer(&stackBase,&stackTop,copyPuzzle,i,j-1);
				}	
				else
				{
					cout<<"Its An Obstacle\n";
					cout<<"You have " <<chance-1<<" chances left\n";
				 	if(chance)
                    {
                        goBack(&stackBase,&stackTop,copyPuzzle);
                        chance--;
                        playerPoints=0;
                    }
				}	
				break;
			case 'd':
				if(puzzle[i][j+1]=='*'&&j+1!=m-1)
				{
					moveThePointer(&stackBase,&stackTop,copyPuzzle,i,j+1);
				}   
				else
				{
				  	cout<<"Its An Obstacle\n";
				  	cout<<"You have " <<chance-1<<" chances left\n";
				 	if(chance)
                    {
                        goBack(&stackBase,&stackTop,copyPuzzle);
                        chance--;
                        playerPoints=0;
                    }
				} 
				break;
			case 'w':
				if(puzzle[i-1][j]=='*'&&i!=1)
				{
					moveThePointer(&stackBase,&stackTop,copyPuzzle,i-1,j);
				}   
				else
				{
					cout<<"Its An Obstacle\n";
					cout<<"You have " <<chance-1<<" chances left\n";
				 	if(chance)
                    {
                        goBack(&stackBase,&stackTop,copyPuzzle);
                        chance--;
                        playerPoints=0;
                    }
				}  
				break;
		    case 's':
				if(puzzle[i+1][j]=='*'&&i+1!=n-1)
				{
					moveThePointer(&stackBase,&stackTop,copyPuzzle,i+1,j);
				}   
				else
				{
				 	cout<<"Its An Obstacle\n";
				 	cout<<"You have " <<chance-1<<" chances left\n";
				 	if(chance)
                    {
                        goBack(&stackBase,&stackTop,copyPuzzle);
                        chance--;
                        playerPoints=0;
                    }
				}  
		}
		i=stackTop->row;
		j=stackTop->col;
	}while(1);
	
}
int printThePath(char puzzle[40][40],int n,int m,int srow,int scol,int drow,int dcol)
{
	struct node *front=NULL,*rear=NULL;
	
	int i,j;
	createNode(&front,&rear,srow,scol);
	while(front!=NULL)
	{
		i=front->row;
		j=front->col;
		if(i==drow&&j==dcol)
		{
      puzzle[i][j]='*';
			cout<<"("<<i<<j<<") Found\n";
			return 1;
			break;
		}
		if(j!=0&&puzzle[i][j-1]==' ')
		{
			createNode(&front,&rear,i,j-1);
		}
		if(j!=m-1&&puzzle[i][j+1]==' ')
		{
			createNode(&front,&rear,i,j+1);
		}
		if(i!=n-1&&puzzle[i+1][j]==' ')
		{
			createNode(&front,&rear,i+1,j);
		}
		if(i!=0&&puzzle[i-1][j]==' ')
		{
			createNode(&front,&rear,i-1,j);
		}
		puzzle[i][j]='*';	
		dequeue(&front);
	}
	return 0;
}
int main()
{
	char puzzle[40][40],copyPuzzle[40][40];
	int i,j,n=10,m=11;
	int srow,scol,drow,dcol;
	FILE *fp=fopen("Puzzle.txt","r");
	for(i=1;i<n-1;i++)
	{
		for(j=1;j<m-1;j++)
		{
			puzzle[i][j]=getc(fp);
            if(puzzle[i][j]=='a')
                puzzle[i][j]=' ';
			copyPuzzle[i][j]=puzzle[i][j];
		}
	}
	printBoundary(copyPuzzle,n,m);
	printPuzzle(copyPuzzle,n,m);
	cout<<"Enter Source\n";
	cin>>srow>>scol;
	
	cout<<"Enter Destination\n";
	cin>>drow>>dcol;
	if (printThePath(puzzle,n,m,srow,scol,drow,dcol))
	   reachTheDestination(copyPuzzle,puzzle,n,m,srow,scol,drow,dcol);
	else 
	   cout<<"Destination Cant be reached"<<endl;
	
	return 0;
}
