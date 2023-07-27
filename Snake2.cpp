#include <iostream>
#include <conio.h>
#include <windows.h> //system clear 
#include <winuser.h>
#include <cstdlib>
#include <stdlib.h> 
#include <mmsystem.h> //sound library
#define KEY_DOWN 80
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_LEFT 75
using namespace std;
int prevMax=0,maximum=0;
const int width = 40;		
const int height = 20;
char direction;
char prevDir = ' ';
void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void initialSettings(bool *gameOver,int *x, int *y, int *fruitX, int *fruitY){
	PlaySound(NULL, 0, 0);
   *gameOver = false;
   direction = 's';
   *x = width/2-1;
   *y = height/2-1;
   *fruitX = rand()%width;
   *fruitY = rand()%height;
}
void drawItems(int *x,int *y, int *score,int *fruitX, int *fruitY,int *numberOfTails, int *tailXFirst, int *tailYFirst){
   system("cls");
   for(int i = 0; i<width+1; i++)
        cout<<"1";
        cout<<endl;
    for(int i = 0; i<height; i++){
       for(int j = 0; j<width; j++){
           if(j==0 || j == width-1)
                cout<<"1";
           if(i==*y &&j==*x) cout<<"O";
           
           else if(i==*fruitY&&j==*fruitX) cout<<"*";
           
           else{
           	 	bool print = true;
           	    for(int k = 0; k<*numberOfTails;k++){
           	    	if(*(tailXFirst+k)==j&&*(tailYFirst+k)==i){
           	    		print = false;
						cout<<"o";
				    }
				}
				if(print)cout<<" ";
		   	}
       }
       cout<<endl;
   }
   
   for(int i = 0; i<width+1; i++)
       cout<<"1";
       cout<<endl;
    cout<<"Score is "<<*score<<endl;
    cout<<"Current number of tails is "<<*numberOfTails<<endl;
    if(*score>prevMax){
			prevMax=*score;
		}
	if(prevMax>maximum){
		maximum = prevMax;
	}
	cout<<"Highest score is "<<maximum;
}
void interaction(bool *gameOver){
    if(kbhit()== true){
    	switch(getch()){
            case KEY_LEFT:
                if(prevDir != 'r'){
                    direction = 'l';
                    prevDir = direction;
                }
                break;
            case 'a':
                if(prevDir != 'r'){
                    direction = 'l'; 
                    prevDir = direction;
                }
                break;
            case 'A':
                if(prevDir != 'r'){
                    direction = 'l'; 
                    prevDir = direction;
                }
                break;
            case KEY_RIGHT:
                if(prevDir != 'l'){
                    direction = 'r';
                    prevDir = direction;
                }
                break;
            case 'd':
                if(prevDir != 'l'){
                    direction = 'r';
                    prevDir = direction;
                }
                break;
            case 'D':
                if(prevDir != 'l'){
                    direction = 'r';
                    prevDir = direction;
                }
                break;
            case KEY_DOWN:
                if(prevDir != 'u'){
                    direction = 'd';
                    prevDir = direction;
                }
                break;
            case 's':
                if(prevDir != 'u'){
                    direction = 'd';
                    prevDir = direction;
                }
                break;
             case 'S':
                if(prevDir != 'u'){
                    direction = 'd';
                    prevDir = direction;
                }
                break;
            case KEY_UP:
                if(prevDir != 'd'){
                    direction = 'u';
                    prevDir = direction;
                }
                break;
            case 'w':
                if(prevDir != 'd'){
                    direction = 'u';
                    prevDir = direction;
                }
                break;
            case 'W':
                if(prevDir != 'd'){
                    direction = 'u';
                    prevDir = direction;
                }
                break;
            case 't':
                *gameOver = true;
                break;
            case 'T':
                *gameOver = true;
                break;
        }
	}
}
void gameLogicMode1(bool *gameOver, int *x, int *y ,int *fruitX,int *fruitY,int *score,int *tailXFirst,int *tailYFirst,int *numberOfTails){
	int prevX = *(tailXFirst+0);
	int prevY = *(tailYFirst+0);
	int prevX2,prevY2;
	*(tailXFirst+0) = *x;
	*(tailYFirst+0) = *y;
	for(int i = 1;i<*numberOfTails; i++){
		prevX2 = *(tailXFirst+i);
		prevY2 = *(tailYFirst+i);
		*(tailXFirst+i)=prevX;
		*(tailYFirst+i)=prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
	switch(direction){
		case 'l':
			(*x)--;
			break;
		case 'r':
			(*x)++;
			break;
		case 'u':
		    (*y)--;
		    break;
		case 'd':
			(*y)++;
			break;	
	}
	  if(*x > width-2 || *x<0 ||*y>height-1 || *y<0) *gameOver = true; //if touches the border end game
	  
	  /*if(*x>=width-1) *x = 0;
	  else if(*x<0) *x = width-2;
	  
	  if(*y>=height) *y = 0;
	  else if(*y<0) *y = height-1;
      */
	for(int i = 0; i<*numberOfTails; i++){
		if(*(tailXFirst+i)== *x && *(tailYFirst+i)== *y) *gameOver = true;
	}
	if (*x == *fruitX && *y == *fruitY){
		(*numberOfTails)++;
	    *fruitX = rand()%width;
        *fruitY = rand()%height;
        if(*fruitX >= width-2 || *fruitX<=0 ||*fruitY>=height-1 || *fruitY<=0){
        	while(*fruitX > width-2 || *fruitX<0 ||*fruitY>height-1 || *fruitY<0){
        		*fruitX = rand()%width;
        		*fruitY = rand()%height;
        		if(*fruitX < width-2 && *fruitX>0 &&*fruitY<height-1 && *fruitY>0) break;
			}
		}
        PlaySound(TEXT("CoinEat.wav"), NULL,  SND_ASYNC);
        if((*numberOfTails)%10==0)*score+=25;
        else *score+=5;
	}
}
void gameLogicMode2(bool *gameOver, int *x, int *y ,int *fruitX,int *fruitY,int *score,int *tailXFirst,int *tailYFirst,int *numberOfTails){
	int prevX = *(tailXFirst+0);
	int prevY = *(tailYFirst+0);
	int prevX2,prevY2;
	*(tailXFirst+0) = *x;
	*(tailYFirst+0) = *y;
	for(int i = 1;i<*numberOfTails; i++){
		prevX2 = *(tailXFirst+i);
		prevY2 = *(tailYFirst+i);
		*(tailXFirst+i)=prevX;
		*(tailYFirst+i)=prevY;
		prevX = prevX2;
		prevY = prevY2;
	}
	switch(direction){
		case 'l':
			(*x)--;
			break;
		case 'r':
			(*x)++;
			break;
		case 'u':
		    (*y)--;
		    break;
		case 'd':
			(*y)++;
			break;	
	}
	  //if(*x > width-2 || *x<0 ||*y>height-1 || *y<0) *gameOver = true; //if touches the border end game
	  if(*x>=width-1) *x = 0;
	  else if(*x<0) *x = width-2;
	  
	  if(*y>=height) *y = 0;
	  else if(*y<0) *y = height-1;
	for(int i = 0; i<*numberOfTails; i++){
		if(*(tailXFirst+i)== *x && *(tailYFirst+i)== *y) *gameOver = true;
	}
	if (*x == *fruitX && *y == *fruitY){
		(*numberOfTails)++;
	    *fruitX = rand()%width;
        *fruitY = rand()%height;
        if(*fruitX >= width-2 || *fruitX<=0 ||*fruitY>=height-1 || *fruitY<=0){
        	while(*fruitX > width-2 || *fruitX<0 ||*fruitY>height-1 || *fruitY<0){
        		*fruitX = rand()%width;
        		*fruitY = rand()%height;
        		if(*fruitX < width-2 && *fruitX>0 &&*fruitY<height-1 && *fruitY>0) break;
			}
		}
        PlaySound(TEXT("CoinEat.wav"), NULL,  SND_ASYNC);
        if((*numberOfTails)%10==0)*score+=25;
        else *score+=5;
	}
}
void gameStarted(){
	PlaySound(TEXT("BlackPink.wav"), NULL,  SND_ASYNC);
	ShowConsoleCursor(false);
	bool gameOver;
	maximum = 0;
	int x,y,fruitX,fruitY,score = 0,speed,tailX[100],tailY[100],numberOfTails=0;
	int difficult=4,gameMode = 3;
	for(int i = 0; i<88; i++){
		cout<<"#";
	}
	cout<<endl;
	cout<<"Game Snake list of rules:"<<endl;
	cout<<"1. You can control your snake 2 ways: WASD or by using arrows.It is better to use WASD."<<endl;
	cout<<"2. '*' represents sweetness for each of them you get your snake bigger by 1 and 5 points."<<endl;
	cout<<"3. You can also complete the game regardless of whether you lost or not. Use 't' button."<<endl;
	cout<<"4. For each 10th tail you will be given 25 points."<<endl;
	for(int i = 0; i<88; i++){
		cout<<"#";
	}
	cout<<endl;
	cout<<"Select the game mode:"<<endl;
	cout<<"1.If you touch the border you lose"<<endl;
	cout<<"2.If you touch the border you'll appear from another side"<<endl;
	while(gameMode!=1&&gameMode!=2){
		cin>>gameMode;
		if(gameMode<0||gameMode>2) cout<<"Please choose correct gameMode:"<<endl;
	}
	cout<<"Select the difficult(number): 1.beginner, 2.medium, 3.expert"<<endl;
	while(difficult!=1&&difficult!=2&&difficult!=3){a
		cin>>difficult;
		if(difficult<0||difficult>3) cout<<"Please choose correct difficult:"<<endl;
	}
	switch(difficult){
		case 1:
			speed = 40;
			break;
		case 2:
			speed = 20;
			break;
		case 3:
			speed = 0;
			break;
	}
    initialSettings(&gameOver,&x,&y,&fruitX,&fruitY);
    		while(gameOver==false){
    			drawItems(&x,&y,&score,&fruitX,&fruitY,&numberOfTails,tailX,tailY);
        		interaction(&gameOver);
        		if(gameMode==1) gameLogicMode1(&gameOver,&x,&y,&fruitX,&fruitY,&score,tailX,tailY,&numberOfTails);
        		else gameLogicMode2(&gameOver,&x,&y,&fruitX,&fruitY,&score,tailX,tailY,&numberOfTails);
        		Sleep(speed);
	    	}
	PlaySound(TEXT("Gameover.wav"), NULL,  SND_ASYNC);
	cout<<endl;
	cout<<"Game is over do you want to restart y/n?";
	char a = getch();
	if(a=='y'){
		system("cls");
		gameStarted();
	}
	return;
}
int main(){
	gameStarted();
	PlaySound(TEXT("END.wav"), NULL,  SND_ASYNC);
	Sleep(1300);
	return 0;
}

