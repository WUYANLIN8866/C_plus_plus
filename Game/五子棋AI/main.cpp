#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#include<conio.h>
#define M 22
#define N  3 
int G[M][M]={0};
int pw,cw;
using namespace std;
void gotoxy(int xpos, int ypos)
{
	system("color a");
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn); 
} 
void SetColor(int f=7,int b=0)
{
    unsigned short ForeColor=f+16*b;
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,ForeColor);
}
void dir(int x,int y){
 
        gotoxy(x*2,y);
             if(G[x][y]==1)      {printf("●");}
        else if(G[x][y]==2)      {printf("○");}
        else {
             if(x==N   && y==N  ){printf("┌");}
        else if(x==N   && y==M-1){printf("└");}
        else if(x==M-1 && y==N  ){printf("┐");}
        else if(x==M-1 && y==M-1){printf("┘");}
        else if(x==N  )          {printf("├");}
        else if(x==M-1)          {printf("┤");}
        else if(y==N  )          {printf("┬");}
        else if(y==M-1)          {printf("┴");}
        else                     {printf("┼");}
             }
     return ;
}

int sc(int s,int x,int y){
        int i,j,l;
        int snc[6]={0,1,10,50,1000,10000};
        int n,ns,nn,t;
        n=0;
 
        for(j=1;j<=8;j++){
        for(l=-1;l<1;l++){
          ns=nn=1;
          for(i=l;i<l+5;i++)      
          {if(j==1)t=G[ x ][y-i]; 
           if(j==2)t=G[x+i][y-i]; 
           if(j==3)t=G[x+i][ y ];
           if(j==4)t=G[x+i][y+i]; 
           if(j==5)t=G[ x ][y+i];
           if(j==6)t=G[x-i][y+i]; 
           if(j==7)t=G[x-i][ y ]; 
           if(j==8)t=G[x-i][y-i]; 
 
           if     (t==s)nn++;
           else if(t!=0)ns=0;
 
          if(nn>5 && G[x][y]==s)
          {SetColor(0,8);
           dir(x,y);
           SetColor(15,0);
           gotoxy(56,5);
           if(s==1){printf("玩 家 獲勝!!");pw=pw+1;}
           if(s==2){printf("電 腦 獲勝!!");cw=cw+1;}
           n=-1;return n;}
 
          if(ns)n+=snc[nn];       }}}
       if(G[x][y])n=0;
       return n;
      }
 
 
 
// 判斷下棋點
int mg(int s){
    int i,j;
    int cM;     //玩家最大值+電腦最大值
    int cN,iN;  //電腦這位置的值+ 玩家的
    int cMx,cMy;//下棋點x+y
    int rrM;    //小隨機分配
 
    srand(time(NULL));
                                               //判斷電腦移動
    cM=0;
    for(i=N;i<M;i++)
    for(j=N;j<M;j++){
    cN=sc(2,i,j);iN=sc(1,i,j);                //求電腦與玩家的該空格分數
    if(iN>cN)cN=iN;                           //把較大者放到cN
    rrM=0;
    if(cN==cM)rrM=rand()%3-1;                //若相等則隨機
    if(cN>cM+rrM){cM=cN;cMx=i;cMy=j;}
    }
 
    G[cMx][cMy]=s;
    dir(cMx,cMy);
 
    return cMx*100+cMy;
 
}
 
 
int main(){
	system("title Artificial Intelligence ");
Start:
    gotoxy(56,5);
    printf("               ");
    int i,j,l;
    int cMg;
    int nt=1;
    
                  //畫棋盤
    for(i=N;i<M;i++)
    {
        for(j=N;j<M;j++)
        {
            G[i][j]=0;
            SetColor(0,15);
            dir(i,j);
        }
 
        SetColor(15,0);
        gotoxy(i*2,M);
        printf("%02d",i-N+1);
        gotoxy(M*2+1,i);
        printf("%c",'A'+i-N);
    }
 
    int key;
    int xi,yi;
    xi=yi=(M+N)/2;
 
    while(1)
    {
        
 
        if(nt>=((M-N)*(M-N))/2)
        {
           SetColor(15,0);
           gotoxy(56,5);
           printf("平  手 !!");
        }
 
        nt++;
 
        do{
 
            SetColor(0,8);dir(xi,yi);
            key=getch();
 
            SetColor(0,15);dir(xi,yi);
 
                    //輸入
            if(key==72){if(yi>N)yi--;   else yi=M-1; }   //上
            else if(key==80){if(yi<M-1)yi++; else yi=N;   }   //下
            else if(key==75){if(xi>N)xi--;   else xi=M-1; }   //左
            else if(key==77){if(xi<M-1)xi++; else xi=N;   }   //右
        }while(key!=13 || G[xi][yi]!=0); // 選擇移動 */
 
        SetColor(0,15);
        G[xi][yi]=1;
        dir(xi,yi);
 
        if(sc(1,xi,yi)<0)break;
 
        cMg=mg(2);
        if(sc(2,cMg/100,cMg%100)<0)break;
 
        Sleep(10);
    }//while(1)
 
    while(1)
    {
        SetColor(15,0);
        gotoxy(56,7);
        printf("是否繼續?!(Y/N)");
        key=getch();
        gotoxy(56,7);
        printf("               ");
        if(key=='n'){printf(" 玩家 vs 電腦 : %d  vs  %d",pw,cw);system("pause");break;}
        else if(key=='y')goto Start;
    }
    return 0;
}
