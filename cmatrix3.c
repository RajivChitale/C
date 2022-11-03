#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 24
#define WIDTH 80
#define STREAKODDS 30
#define BLANKSTREAKODDS 5
#define ALTERODDS 30
#define DISPLACEDSTREAKODDS 6
#define YES 1
#define NO 0
#define MESSAGELENGTH 21
#define REFRESHTIME 80000
#define GREEN  "\x1B[32m"
#define WHITE  "\x1B[37m"

/* 0 green, 1 white, 2 invisible*/


char randomchar()
{
 return (rand()%77) +48;
}


int oncein(int n)
{
  if ( ( rand()%n ) <1 ) return 1;
  else return 0;
}


void filldefault(char matrix[HEIGHT][WIDTH],  int colour[HEIGHT][WIDTH])
{
	for(int x=0; x<WIDTH; x++)
	{
		
		int darkheight= -1;
		if(oncein(DISPLACEDSTREAKODDS)) {darkheight= rand()%(HEIGHT-5); }

		
		
		for(int y=0; y<HEIGHT; y++)
		{
			matrix[y][x]=' ';
			colour[y][x]=0;
			if(y < darkheight) {colour[y][x]=2; matrix[y][x]= randomchar();}
			if(y == darkheight) {colour[y][x]=1; matrix[y][x]= randomchar();}
		}
		
	}
	
}

void refresh(char matrix[HEIGHT][WIDTH],  int colour[HEIGHT][WIDTH])
{	

  /* for y=0  case*/
	for(int x=0; x<WIDTH; x++)
		{
			/*starts new streak*/
			if(matrix[0][x]==' ' && oncein(STREAKODDS))
			{
				matrix[0][x]= randomchar();
				colour[0][x]=1;
			}
			
			/*starts new blank streak*/
			else if( (matrix[0][x]!=' ') && (matrix[2][x]!=' ') && oncein(BLANKSTREAKODDS) )
			{
				matrix[0][x]= ' ';
				colour[0][x]= 0;
			}
			
			/* alters */
			else if(matrix[0][x]!=' ' && oncein(ALTERODDS))
			{
				matrix[0][x]= randomchar();
				colour[0][x]=0;
			}
			
			else if(colour[0][x]== 1)
			{
				colour[0][x]= 0;
			}
		

		}

	
	/* loop through each column */
	for(int x=0; x<WIDTH; x++)
	{
		
		int inStreak=YES;
		if(	matrix[0][x] == ' ') {inStreak= NO;}
		
		 
		for(int y=1; y<HEIGHT; y++)
		{
						
			/* enter streak but delete top element */
			if ( (inStreak==NO) && (matrix[y][x]!=' ') )
			{matrix[y][x]=' '; inStreak=YES;}
		
			/*new white element at bottom*/
			else if( (inStreak==YES) && (matrix[y][x]==' ') )
			{
				matrix[y][x]= randomchar();
				colour[y][x]= 1;
				colour[y-1][x]= 0;
				inStreak=NO;
			}				
			
			/*alterations */
			else if( (inStreak==YES) && oncein(ALTERODDS) )
			{ matrix[y][x]= randomchar(); }
			
			
		}
		
	}

}



void display(char matrix[HEIGHT][WIDTH],  int colour[HEIGHT][WIDTH])
{
	system("clear");
	
	/*ignore last row */
	for(int y=0; y<HEIGHT-1; y++)
	{
		for(int x=0; x<WIDTH; x++)
		{
			
			if (colour[y][x]==0) 
				{ printf("%s%c", GREEN, matrix[y][x]); }
			else if (colour[y][x]==1) 
				{ printf("%s%c", WHITE, matrix[y][x]); }
			else if (colour[y][x]==2) 
				{ printf(" ");}
			
		}
		printf("\n");
		
	}
	
}

void rickroll(char matrix[HEIGHT][WIDTH],  int colour[HEIGHT][WIDTH], int length)
{
	/* int x= rand()%(WIDTH-1); hard to spot */
	int x=0;

	
	char str[]= "NeverGonnaGiveYouUp  "; /*len 21*/

	matrix[0][x]= str[0];
	colour[0][x]=1;
	
	for(int y=1; y<=length; y++)
		{
			matrix[y][x]= str[y];
			colour[y][x]=1;
			colour[y-1][x]=0;
		}
}



int main()
{
	
    
    char matrix[HEIGHT][WIDTH];
    int colour[HEIGHT][WIDTH];
    
    filldefault(matrix, colour);
   
    int timer=0;
	
	while(1)
	{
		
		usleep(REFRESHTIME);
		refresh(matrix, colour);		
		if (timer%80 <MESSAGELENGTH){rickroll(matrix, colour, timer%80);}
		display(matrix, colour);
		
		if (timer==30000) {break;}	
		timer++;
		
	
	}
    
    

    return 0;
}
