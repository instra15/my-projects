#include<iostream>
#include<vector>
#include<conio.h>
#include<windows.h>
#include<ctime>  
#include<sstream>
using namespace std;

const int LENGTH = 100;
const int HEIGHT = 45;

const char SNAKE_HEAD='@';
const char SNAKE_BODY='o';
const char FOOD='*';
const char WALL='#';
const char EMPTY=' ';

vector<vector<int>> Map(HEIGHT,vector<int>(LENGTH,0));
//1:snakeBody  2:snakeHead  3:Food
int dirX=1,dirY=0;
int snakeLength;
int headx,heady;
int foodx,foody;
int score=0;
bool gameover;
bool isPause=true;
bool isExit=false;
bool restart=false;
vector<pair<int,int>> SnakePart;

void draw()
{
    stringstream ss;
    bool isSnakePart=false;
    bool isSnakeHead=false;
    bool isFood=false;
    for(int i=0;i<LENGTH+2;i++)
    {
        ss<<WALL;
    }
    ss<<endl;
 
    for(int i=0;i<HEIGHT;i++)
    {
        ss<<WALL;
        for(int j=0;j<LENGTH;j++)
        {
            bool isSnakePart=false;
            bool isSnakeHead=false;
            bool isFood=false;
            if(Map[i][j]==1)
            {
                isSnakePart=true;
            }
            else if(Map[i][j]==2)
            {
                isSnakeHead=true;
            }
            else if(Map[i][j]==3)
            {
                isFood=true;
            }

            if(isSnakePart)
            {
                ss<<SNAKE_BODY;
            }
            else if(isSnakeHead)
            {
                ss<<SNAKE_HEAD;
            }
            else if(isFood)
            {
                ss<<FOOD;
            }
            else
            {
                ss<<EMPTY;
            }
        }
        ss<<WALL<<endl;
    }

    for(int i=0;i<LENGTH+2;i++)
    {
        ss<<WALL;
    }
    ss<<endl;
    ss<<"score: "<<score<<endl;
    system("cls");
    cout<<ss.str();
}
void Setup()
{
    gameover=false;
    restart=false;
    isPause=true;
    //地图清空
    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<LENGTH;j++)
        {
            Map[i][j]=0;
        }
    }

    //蛇身初始化1
    SnakePart.clear();
    snakeLength=3;
    
    //蛇头初始化
    headx=LENGTH/2;
    heady=HEIGHT/2;
    Map[heady][headx]=2;
    SnakePart.push_back({heady,headx});

    //蛇身初始化2
    for(int i=1;i<snakeLength;i++)
    {
        int bodyx=headx-i;
        int bodyy=heady;
        SnakePart.push_back({bodyy,bodyx});
        Map[bodyy][bodyx]=1;
    }

    //食物初始化
    foodx=rand()%LENGTH;
    foody=rand()%HEIGHT;
    Map[foody][foodx]=3;
}
void Input()
{
    if(_kbhit())
    {
        char key=_getch();
        switch(key)
        {
            case 'w':
                if(dirY!=1)
                {
                    dirX=0;
                    dirY=-1;
                }
                break;
            case 'a':
                if(dirX!=1)
                {
                    dirX=-1;
                    dirY=0;
                }     
                break;
            case 'd':
                if(dirX!=-1)
                {
                    dirX=1;
                    dirY=0;
                }    
                break;
            case 's':
                if(dirY!=-1)
                {
                    dirX=0;
                    dirY=1;
                }    
                break;
            case 'p':
                gameover=true;break;
            case ' ':
                if(!gameover)
                {
                    isPause = !isPause;break;
                }
                else
                {
                    isExit=true;
                }
                break;
            case 'h':
                restart=true;
            
        }
    }
}
void Move()
{
    //蛇头移动
    int newheadx=headx+dirX;
    int newheady=heady+dirY;

    //撞墙检测
    if(newheadx < 0 || newheadx >= LENGTH || newheady < 0 || newheady >= HEIGHT)
    {
        gameover=true;
        return;
    }

    // 撞自己检测
    for(int i=1;i<SnakePart.size();i++)
    {
        if(newheadx==SnakePart[i].second&&newheady==SnakePart[i].first)
        {
            gameover=true;
            return ;
        }
    }

    //吃食物检测
    bool eatFood=false;
    if(newheadx==foodx && newheady==foody)
    {
        eatFood=true;
        score+=1;
        snakeLength++;
        while(Map[foody][foodx]!=0)
        {
            foodx=rand()%LENGTH;
            foody=rand()%HEIGHT;
        }
        Map[foody][foodx]=3;
    }

    //蛇身移动
    if(!eatFood)
    {
        int y=SnakePart.back().first;
        int x=SnakePart.back().second;
        Map[y][x]=0;
        SnakePart.pop_back();
    }
    SnakePart.insert(SnakePart.begin(),{newheady,newheadx});
    for(int i=0;i<SnakePart.size();i++)
    {
        int y=SnakePart[i].first;
        int x=SnakePart[i].second;
        if(i==0)
        {
            Map[y][x]=2;
        }
        else
        {
            Map[y][x]=1;
        }
    }
    headx=newheadx;
    heady=newheady;
}
int main()
{
    srand(time(0));
    Setup();
    while(!gameover)
    {
        draw();
        if(isPause)
        {
            cout << "Game Paused. Press SPACE to continue." << endl;
        }
        Input();
        if(!isPause)
        {
            Move();
        }
        Sleep(5);
    }
    cout<<"You Lose. Press SPACE to Exit or Press H to restart.."<<endl;
    return 0;
}