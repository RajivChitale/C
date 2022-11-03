/*new version. backtracking. Checking done for each new queen instead of whole board */


#include <stdio.h>
#define N 29
#define VALID 0
#define INVALID 1
#define QUEEN 1
#define BLANK 0
#define FALSE 0
#define TRUE 1

void initgrid(int grid[N][N])
{
	for(int y=0; y<N; y++)
	{
		for(int x=0; x<N; x++)
		{
			grid[y][x]=BLANK;
		}
	}
	return;
}

void display(int grid[N][N])
{
	
	static int count;
	count++;
	printf("\033[0;31mSolution %d:\n", count);  //count of cases
	

	for(int y=0; y<N; y++)
	{
		for(int x=0; x<N; x++)
		{
			//printf("%d ", grid[y][x]);
			if(grid[y][x]==QUEEN){printf("\033[0;37mQ "); }
			else if(grid[y][x]==BLANK && (x+y)%2==0 ){printf("\033[0;34m= ");}
			else if(grid[y][x]==BLANK && (x+y)%2==1 ){printf("\033[0;37m= ");}
		}
		printf("\n");
	}
	
	return;	

}

int checkdiag(int grid[N][N], int current, int x)
{
	int x1=x;
	int x2=x;				
	
	for(int y=current-1; y>=0; y--)
	{
		x1++;
		if(x1 >= 0 && x1 < N)
		{
			if (grid[y][x1] == QUEEN) {return INVALID;}
		}	
		
		x2--;  
		if(x2 >= 0 && x2 < N)
		{
			if (grid[y][x2] == QUEEN) {return INVALID;}
		}	
	}

	return VALID;
}


int addqueen(int current, int grid[N][N], int occupied[N])
{
	int retval=INVALID; //default
	for(int x=0; x<N; x++)
	{
	
		if(occupied[x]==TRUE){continue;}  //skip if column occupied. makes 8! instead of 8^8
	
		grid[current][x]=QUEEN;		//place queen
		occupied[x]=TRUE;			//set occupied
		
		if(checkdiag(grid, current, x)==VALID)
		{
			if(current==N-1)			//final row finished
			{
			 	display(grid);
			 	grid[current][x]=BLANK;		//remove queen
				occupied[x]=FALSE;			//set unoccupied
			 	return VALID;
			}
			else if(current<=N-1)		//if valid and more rows left, proceed
			{
				 if(addqueen(current+1, grid, occupied) == VALID) 
				 {
				 	retval= VALID;
				 	
				 	
					grid[current][x]=BLANK;		//remove queen
					occupied[x]=FALSE;			//set unoccupied				 		 	
				 	return VALID; 		//if just one solution is wanted   
				 	
				 } 
			}	
		}
		
		grid[current][x]=BLANK;		//remove queen
		occupied[x]=FALSE;			//set unoccupied	
			
	}	
	return retval;		
}

int main()
{
	int grid[N][N];  //[y][x]
	initgrid(grid);
	
	int occupied[N];
	for(int i=0; i<N; i++) {occupied[i]= FALSE;}
	
	addqueen(0, grid, occupied);
	
	return 0;
}
