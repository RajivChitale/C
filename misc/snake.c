#include <stdio.h>
#define W 24
#define H 18
#define A 225
#define DefaultLen 6

/*
M1 decay and store remaining time in each element of 2d array

M2 store reverse directions in a list

M3 store past coordinates of head in a list

This is M3

maintain head, length
maintain list of past positions of head
make display array and print

movement, change in length

*/


int displayer(int listx[], int listy[], int indextail, int len, int end)
{

	/*set screen elements to 0 1 2 3 */
	int screen[W][H];
	
	for(int y=0; y<H; y++)
	{
		for(int x=0; x<W; x++)
		{
		screen[x][y]=0;
		}
	}
	
	/* (indextail+i) % A)  goes through list from tail to just before head*/

	for(int i=1; i<len-1; i++)
	{
		screen[ listx[(indextail+i) % A] ] [ listy[(indextail+i) % A]	] = 1;
		
		if ( ( listx[(indextail+i) % A]== listx[(indextail+len-1)%A] ) && ( listy[(indextail+i) % A]== listy[(indextail+len-1)%A] ) )
		{end=1;}
	
	}
	
	screen[ listx[indextail%A] ] [ listy[indextail%A] ] =2;
	screen[ listx[(indextail+len-1)%A] ] [ listy[(indextail+len-1)%A] ] =3;

	
	
	system("clear");
	
	for(int x=0; x<W+2; x++) printf("#");
	printf("\n");
	
	for(int y=0; y<H; y++)
	{
		printf("#");
		
		for(int x=0; x<W; x++)
		{	
			if ( screen[x][y]==0 ) { printf(" "); }
			if ( screen[x][y]==1 ) { printf("S"); }
			if ( screen[x][y]==2 ) { printf("T"); }
			if ( screen[x][y]==3 ) 
				{ 
					if(end==1) printf("X"); 
					else printf("H"); 		
				}
		}
		
		printf("#\n");
	}
	
	for(int x=0; x<W+2; x++) printf("#");
	printf("\n");
	
	if(end==1)	{printf("Game over!\n"); return 1;}
	
	return 0;
}




int main()
{
	
	/* position of head*/
	int poshx=2;
	int poshy=2;
	char direction='s';
	
	int len= DefaultLen;
	int indextail=0;
	int indexhead=(indextail+len-1)%A;
	
	int listx[A];  /*head can't travel once all the area is covered */
	int listy[A];
	
	for(int i=0; i<A; i++)
	{
		listx[i]=0;
		listy[i]=0;
	}
		
	
	/*fill existing snake */
	for(int i=0; i<len; i++)
	{
		listx[i]=poshx;
		poshy++;
		listy[i]=poshy; /*according to direction*/
	}
	
	displayer(listx, listy, indextail, len, 0);
	
	char keypressed;
	

	while(1)
	{
	/*user input handling*/	
		scanf("%c", &keypressed);
		if (keypressed=='\n') { continue;}		
		if (keypressed=='q') { break;}
	
		if (keypressed=='e') 
			{	
				len=len+1; 
				indextail=indextail-1; /*tail remains unchanged*/ 
				keypressed=direction;
			}	
						
		if (keypressed=='n') {keypressed=direction;}
		/*continue with same direction	*/
	
		if (keypressed=='w') {direction='w'; poshy=poshy-1;}
		if (keypressed=='a') {direction='a'; poshx=poshx-1;}
		if (keypressed=='s') {direction='s'; poshy=poshy+1;}
		if (keypressed=='d') {direction='d'; poshx=poshx+1;}
		
		
	/*collision*/	
		if(poshx<0 || poshx>=W || poshy<0 || poshy>=H)
		{
			
			displayer(listx, listy, indextail, len, 1);
			break;
		}
				
		
		/*index for tail changes*/
		indextail=indextail+1; 
		indexhead=(indextail+len-1)%A;
		
		/*update list*/
		listx[indexhead]=poshx;
		listy[indexhead]=poshy;
			
		if( displayer(listx, listy, indextail, len, 0) ==1 ) {break;}
		printf("(%d,%d)\n",poshx,poshy);//
		
		
	}
	
	
	
	return 0;
}
