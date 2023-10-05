#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
void firstfront(){
	int i,x=0;
    setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(100,300,LIGHTGRAY);
	setbkcolor(LIGHTGRAY);
	setcolor(RED);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(100,300,"S");
	setcolor(YELLOW);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(170,300,"P");
	setcolor(GREEN);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(250,300,"R");
	setcolor(CYAN);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(325,300,"I");
	setcolor(MAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(400,300,"N");
	setcolor(BROWN);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(475,300,"G");
	setcolor(BLUE);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(550,300,"B");
	setcolor(LIGHTMAGENTA);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(630,300,"A");
	setcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(710,300,"L");
	setcolor(LIGHTRED);
	settextstyle(BOLD_FONT, HORIZ_DIR, 10);
	outtextxy(790,300,"L");
	setcolor(BLACK);
	settextstyle(BOLD_FONT, HORIZ_DIR, 4);
	delay(2000);
	outtextxy(400,500,"Loading");
	for(i=0;i<5;i++){
		circle(540+x,520,4);
		x=x+10;
		delay(600);
	}
}
void loading(){
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	outtextxy(400,235,"Loading....");
	int i=401,j=275,i1=402,j1=295,x=1,y=0;
	setcolor(BLACK);
	while (i<=647){
		delay(1);
		rectangle(i,j,i1,j1);
		i=i+x;
		j=j+y;
		i1=i1+x;
		j1=j1+y;
	}
	cleardevice();
}
void frontscreen(){
	char choice;
	cleardevice();
	readimagefile("image1.jpg",0,0,1000,800);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(BLACK);
	outtextxy(400,150, "Main Menu");
	outtextxy(450,250, "1.Start game");
	outtextxy(500,350, "2.View score");
	outtextxy(560,450, "3.Exit");
    choice=getch();
    cleardevice();
    readimagefile("image1.jpg",0,0,1000,800);
    switch (choice){
    	case '1':
    		loading();
    		setcolor(BLACK);
    		readimagefile("image1.jpg",0,0,1000,800);
    		outtextxy(380,200, "Press 'SPACE' to jump");
    		outtextxy(340,300, "Press 'ANY KEY' to start");
    		break;
    	case '2':
    		FILE *fp1;
    		int highsc;
    		char ch[5];
    		fp1=fopen("score.dat","r");
    		fscanf(fp1,"%d",&highsc);
    		sprintf(ch, "%d",highsc);
    		outtextxy(400,300, "High score =  ");
    		outtextxy(710,300,ch);
    		getch();
    		fclose(fp1);
    		frontscreen();
    		break;
    	case '3':
    		exit(0);
    	    break;
    	default:
    		frontscreen();
    	}          
    getch();
}
void star(){
	int x, y,i=0;
	while(i<500){
		x=rand()%1000;
		y=rand()%800;
		putpixel(x,y,WHITE);
		setcolor(rand());
		i++;
	}
}
void sor(int score){
	FILE *fp1;
	FILE *fp2;
	int high=0;
	fp1=fopen("score.dat","r");
	fp2=fopen("newscore.dat", "w");
	fscanf(fp1,"%d",&high);
	if(high<score){
		fprintf(fp2,"%d",score);
	}
	else{
		fprintf(fp2,"%d",high);
	}
	fclose(fp1);
	fclose(fp2);
	remove("score.dat");
	rename("newscore.dat", "score.dat");
}
int main (){
	int gd=DETECT, gm;
	initwindow(1000,800);
	firstfront();
	top:
	char ch;
	int obs=true;
	int flow=0, score=0;
	int x[4]={500,800,1100,1400};
	int h[4]={160,300,100, 400};
	int i=50, j=100, k=30;
	int i1=60, j1=100, k1=5;
	frontscreen();
	while(obs){
	        cleardevice();
		    setcolor(WHITE);
		    circle(i,j,k);
		    setfillstyle(SOLID_FILL, YELLOW);
		    floodfill(i,j, WHITE);
		    setcolor(RED);
	    	circle(i1,j1,k1);
	    	setfillstyle(SOLID_FILL, RED);
	    	floodfill(i1,j1, RED);
	    	j=j+15;
	    	j1=j1+15;
	    	for(int a=0; a<=3; a++){
	        	bar(x[a]+flow, 0, x[a]+60+flow, h[a] ); //generate upper bar
	        	bar (x[a]+flow, h[a]+250, x[a]+60+flow, getmaxy()); //generate lower bar
	    	    if (x[a]+150+flow<0){
	    	    	x[a]=getmaxx()-flow;
				}
	    		if (x[a]+10+flow<i && x[a]+25+flow>i){ //score increment
	    			score++;
				}
				if(x[a]+flow<i+30 && x[a]+flow+60>i+30 && 0<j-30 && h[a]>j-30){ //upper bar hit
					obs=false;
				} 
				if(x[a]+flow<i+30 && x[a]+flow+60>i+30 && h[a]+250<j+30 && getmaxy()>j+30){ //lower bar hit
					obs=false;
				} 
			}
			star();
			flow=flow-10;
	    	if (kbhit()){
	    		ch=getch();
	    		
				 if (ch==' '){
					j=j-70;
					j1=j1-70;
					
				}
			}
			if(j+30 >= getmaxy() || j <= 0){
				obs = false;
			}
    }
	if (obs==false){
				setcolor(RED);
				settextstyle(BOLD_FONT, HORIZ_DIR, 8);
				outtextxy(300,300,"GAME OVER!!!");
	}
	setcolor(BLACK);	
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    outtextxy(300,250,"Score:");
    char a[5];
	sprintf(a,"%d",score);
	outtextxy(450,250,a);
	getch();
	sor(score);
	cleardevice();
	goto top; //to go to main menu after game over
	closegraph();
	
	return 0;
}
