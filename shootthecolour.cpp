#include<iostream.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>

int arrow(int color);
void targets();
void mission();
int arrow_move(int,int,int,int,int,int);

void homepage()     //Funcion to draw the homepage
{
cleardevice();
char op='\0';
settextstyle(1,0,4);
int mx=getmaxx(),my=getmaxy();
rectangle(mx/4-10,my/5-10,mx/4+330,my/5+50);
outtextxy(mx/4,my/5,"S");
outtextxy(mx/4+20,my/5,"H");
outtextxy(mx/4+40,my/5,"O");
outtextxy(mx/4+60,my/5,"O");
outtextxy(mx/4+80,my/5,"T");
outtextxy(mx/4+130,my/5,"T");
outtextxy(mx/4+150,my/5,"H");
outtextxy(mx/4+170,my/5,"E");
setcolor(1);
outtextxy(mx/4+220,my/5,"C");
setcolor(2);
outtextxy(mx/4+240,my/5,"O");
setcolor(3);
outtextxy(mx/4+260,my/5,"L");
setcolor(4);
outtextxy(mx/4+280,my/5,"O");
setcolor(5);
outtextxy(mx/4+300,my/5,"R");

settextstyle(0,0,1);
setcolor(15);
outtextxy(mx/4,my/2,"Use SPACE to shoot.");
outtextxy(mx/4,my/2+20,"Shoot according to the color of the arrow.");

settextstyle(0,0,2);
outtextxy(mx/4,my/2+170,"PRESS SPACE TO CONTINUE");

op=getch();
if(op==' ')
{
cleardevice();
targets();
mission();
}
setcolor(WHITE);
settextstyle(0,0,1);
outtextxy(mx/4,mx/4,"CONTINUE PLAYING ? Y/N");
op=getch();

if(op=='y')
homepage();
}


void targets()    //Function to draw the targets
{
int mx=getmaxx()-5;
int my=getmaxy()/8;

setlinestyle(SOLID_LINE,1,3);

setcolor(BLUE);
line(mx,0,mx,my);
setcolor(GREEN);
line(mx,my,mx,my*2);
setcolor(CYAN);
line(mx,my*2,mx,my*3);
setcolor(RED);
line(mx,my*3,mx,my*4);
setcolor(BLUE);
line(mx,my*4,mx,my*5);
setcolor(GREEN);
line(mx,my*5,mx,my*6);
setcolor(CYAN);
line(mx,my*6,mx,my*7);
setcolor(RED);
line(mx,my*7,mx,my*8);
}


int arrow_move(int x1,int y1,int x2,int y2,int l,int color)  //Function to move arrow
{
float a1=x1,b1=y1,a2=x2,b2=y2,c=b1;
float m=(b2-b1)/(a2-a1);
int maxx=getmaxx(),maxy=getmaxy(),speed=1;   //Speed of arrow
while(b2>0&&b2<maxy&&a2<maxx-5)
{
setcolor(BLACK);
line(a1,b1,a2,b2);
a1+=0.5;
a2+=0.5;
b1=a1*m+c;               //line function y=mx+c
b2=a2*m+c;
setcolor(color);
line(a1,b1,a2,b2);
delay(speed);
}
if(a2>=getmaxx()-5)     //returns the position of the arrow where it hit
return (int)b2;
else
return 1000;
}


void mission()
{
randomize();
int task[10],mx=150,my=5,ry;
for(int i=0;i<10;i++)
task[i]=(int)(random(16)/4)+1;      //Randomly selects colors for the user

for(i=0;i<10;i++)
{
setcolor(task[i]);
rectangle(mx,my,mx+20,my+20);    //Draws the color combination above
mx=mx+20;
}
mx=150;
for(i=0;i<10;i++)    //condition to check if the arrow hit the right color
{
ry=arrow(task[i]);
if(ry>(task[i]-1)*60&&ry<(task[i]*60)||ry>((task[i]-1)*60)+240&&ry<(task[i]*60)+240)
{
	line(mx+i*20,my,mx+(i*20)+20,my+20);   //If the arrow hit the target mark X
	line(mx+(i*20)+20,my,mx+i*20,my+20);
}
}
}


int arrow(int color)   //Function to create and adjust direction of arrow
{
int x1=0,y1=200,x2=50,y2=200,l=50,c=color,flag=0;

setcolor(color);
line(x1,y1,x2,y2);

char op='\0';

while(!kbhit())
{

delay(20);

setcolor(BLACK);
line(x1,y1,x2,y2);

setcolor(color);
	if(y2>=180&&flag!=0)
{
		y2--;
		x2=sqrt(l*l-(y2-y1)*(y2-y1))+x1;    //Upward arrow movement
		line(x1,y1,x2,y2);
}
	else if(y2<=220&&flag==0)
{
		y2++;
		x2=sqrt(l*l-(y2-y1)*(y2-y1))+x1;    //Downward arrow movement
		line(x1,y1,x2,y2);
}
	if(y2==180)
		flag=0;
	else if(y2==220)
		flag=1;
}
op=getch();
return arrow_move(x1,y1,x2,y2,l,c);  //Function call to move arrow
}


void main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
homepage();
closegraph();
}