/* LAYOUT
define constants, inital position
create map
begin loop
clear array used in displaying  
loop for all map elements, shift and rotate cooridinates
project map elements on display array
clear screen and print display array
controls for motion, rotation while detecting collision
option to print map and location, leave program

*/

#include<stdio.h>
#include<math.h>
#include <unistd.h>

#define mheight 21
#define mwidth 40
#define sheight 20
#define swidth 50
#define d 1   //depth of player head
#define h 50  //height proportionality const
#define w 40  //width proportionality const
#define PI 3.14159
#define step 1  //length of step
#define render 20//render dist

int main() 
   {
   
   float posx = 10.5;
   float posy = 15.5;
   float angle  = 0;
   float si=0;
   float co=1;
   
   
   
   //1 for null character
   char map[mheight][mwidth+1]= 
                    {"mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
                     "m                   m                  m",
                     "m                   m                  m",
                     "m                   m                  m",
                     "m                   m                  m",
                     "m                   m        mmm       m",
                     "m      mmmmmmmmmmmmmm        m         m",
                     "m      m                     m         m",
                     "m      m                     m         m",
                     "m      m                     m         m",
                     "m      m                     m         m",
                     "m      m            m        m         m",
                     "m      m            m        m         m",
                     "m      m            m        m         m",
                     "m      m            m        m         m",
                     "m                   m        m         m",
                     "m                   m                  m",
                     "m                   m                  m",
                     "m                   m                  m",
                     "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm",
                     "                                        ",};
                      
   
   
   
   
   
 char inp=' ';

  
     
     
     
 //read map
 
 int t=0; //limit of moves
while (t<10000) 
{
 t++;
 
 si= sin(angle);
 co= cos(angle);
 
  
  //clear display to blank
     char display[sheight][swidth+1];
     
    for(int i=0; i<=sheight-1; i++)
    {
       for(int j=0; j<=swidth; j++)
       {
	     display[i][j]=' ';
	   }
	
	}
 

 //loop checking all pixels 
  for(int i=0; i<=mheight-1; i++)                              
    {
       for(int j=0; j<=mwidth-1; j++)
       {
	     if ((map[i][j]=='m') && (i< posy+render) && (i> posy-render) && (j< posx+render) && (j> posy-render))  	       	       	      	        
	        {
	                
	        
	        
	        float shiftedx= j-posx;
	        float shiftedy= -(i-posy);   //because y axis is inverted
	        
	        float relx= shiftedy * si + shiftedx * co;
	        float rely= shiftedy * co - shiftedx * si;         //rotate
	        
	        float distToWall= sqrt(relx*relx+rely*rely);
	        
	        if(rely>0) 
	             {
	             int projx= (w*relx)/(d+rely) + (swidth-1)/2;      //x coord for display
	             int projy= (h)/(d+rely);                           //y height for display
	             
	             if(projx<=swidth-1 && projx>=0) 
	                {
	                for(int tempy= (sheight-1)/2 -projy; tempy<= (sheight-1)/2 +projy; tempy++)
	                   { if(tempy>=0 && tempy<=(sheight-1) ) 
	                       { if (distToWall<4) display[tempy][projx]='#';
	                         else if (distToWall<8 && (display[tempy][projx]!='#')) display[tempy][projx]='=';
	                         else if (distToWall<11 && (display[tempy][projx]=='.'|| display[tempy][projx]==' ')) display[tempy][projx]='-';
	                         else if (distToWall<14 && display[tempy][projx]==' ') display[tempy][projx]='.';
	                        
	                        //further items are darker. preventing overlap of closer items by further back items
	                       } 
	                       
	                       
	                       
	                       
	                       
	                                    	                        
	                   }
	           	             
	                }
	             }
	        	         
	     
	        
	        }     
	   }   
	 
	}
	
	system("clear");
	
	//display output screen                   
    for(int i=0; i<=sheight-1; i++)
    {
       for(int j=0; j<=swidth-1; j++)
       {
	     printf("%c",display[i][j]);
	   }
	   
	   printf("\n");
	
	}
   
	
	
	inp= getchar();
	
 // old controls
/*  if (inp=='a' || inp=='A') posx--;
  if (inp=='d' || inp=='D') posx++;
  if (inp=='w' || inp=='W') posy--;
  if (inp=='s' || inp=='S') posy++;   */     
  
  
    //y axis is inverted from usual cartesian plane
    //move in correct direction. If collision detected, revert back
  if (inp=='a' || inp=='A') { posy= posy+ step*si; posx= posx- step*co; if(map[(int)posy][(int)posx]=='m'){posy= posy- step*si; posx= posx+ step*co;}}  
  if (inp=='d' || inp=='D') { posy= posy- step*si; posx= posx+ step*co; if(map[(int)posy][(int)posx]=='m'){posy= posy+ step*si; posx= posx- step*co;}}
  if (inp=='w' || inp=='W') { posy= posy- step*co; posx= posx- step*si; if(map[(int)posy][(int)posx]=='m'){posy= posy+ step*co; posx= posx+ step*si;}}  
  if (inp=='s' || inp=='S') { posy= posy+ step*co; posx= posx+ step*si; if(map[(int)posy][(int)posx]=='m'){posy= posy- step*co; posx= posx- step*si;}}
  
  
  if (inp=='q' || inp=='Q') angle= angle + PI/8;
  if (inp=='e' || inp=='E') angle= angle - PI/8;
  
  
   //for printing map                 
  if (inp=='m' || inp=='M')                 
     { 
     system("clear");
     char tempstore = map[(int)posy][(int)posx];
     
     map[(int)posy][(int)posx]='P';
     
     for(int u=0; u<=mheight-1; u++)
       {
         for(int v=0; v<=mwidth-1; v++)
         {
	       printf("%c",map[u][v]);
	     }
	   
	     printf("\n");
	   }
	   
	   printf("%f, %f\n", posx,posy);
	   
	   sleep(3);
	   
	   map[(int)posy][(int)posx]= tempstore;
     }
   
  
  
  
  
  if (inp=='l' || inp=='L') break;
  inp=' ';
  
  
  
  
}
     
     
   return 0;
   
   }
