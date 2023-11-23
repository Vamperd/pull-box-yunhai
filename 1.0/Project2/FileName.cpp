
int flag;
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<easyx.h>
#include<windows.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
//-----------------------------数据设计-----------------------------------------
struct Player // 用于记录玩家位置
{
    int i;
    int j;
};
Player player;//玩家全局变量
/*贴图
地图中各部分
各个页面
*/
IMAGE img[27];
int remake;//控制是否重置=0不重置 =1重置
/*地图设计
     map[[i][j]表示坐标
     int类型前两个数字表示字母  第三个数字为人    第四个判定箱子   第五个判定墙
     如03 0 1 0  03表示c 0表示不是人 1表示是箱子 0表示不是墙壁
     使用时设置当前地图mapnow，在第几关就把哪个map赋值给mapnpw
     */
const int init_map[5][14][14] = { {},
    {
       {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00000, 00000, 100, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00000, 00000, 15010, 00000, 00001, 00001, 00000, 00001, 00001, 00001},
   {00001, 00001, 00001, 16001, 18001, 00000, 13001, 00000, 00000, 5001, 00000, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00000, 00000, 00001, 00000, 00000, 19010, 00000, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00000, 9010, 00000, 00000, 00000, 00000, 00001, 00001, 00001},
   { 00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 00001, 00001, 00001 },
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   },
   {
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 16001, 00001, 00000, 00000, 00000, 100, 00001, 00001, 00001},
   {00001, 00001, 00001, 00000, 00001, 1001, 00000, 00000, 00001, 00001, 00000, 00001, 00001, 00001},
   {00001, 00001, 00000, 20010, 00000, 00000, 00000, 5010, 00000, 00000, 00000, 00001, 00001, 00001},
   {00001, 00001, 00000, 14010, 00000, 9001, 00000, 00000, 00000, 00000, 00001, 00001, 00001, 00001},
   { 00001, 00001, 00000, 5001, 00000, 5001, 18001, 7001, 00000, 20001, 9001, 3001, 00001, 00001 },
   { 00001, 00001, 00000, 00000, 00000, 00000, 00000, 00000, 14010, 00000, 00001, 00001, 00001, 00001 },
   {00001, 00001, 00001, 00001, 00001, 20001, 00000, 00001, 00000, 00000, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   },
   {
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 100, 00000, 00000, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00000, 00000, 5010, 21010, 00001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00000, 00000, 00000, 20010, 00001, 00000, 00000, 00000, 00000, 00000, 00000, 00001},
   {00001, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 16001, 00000, 19010, 00000, 00001},
   {00001, 00000, 00000, 6001, 00000, 00000, 14010, 00000, 00000, 00000, 00000, 00001, 00001, 00001},
   {00001, 00001, 00000, 15001, 00000, 00000, 00000, 00000, 00000, 18001, 00000, 00000, 00001, 00001},
   {00001, 19001, 00000, 18001, 5001, 00000, 21001, 15001, 00000, 00000, 00000, 00000, 00000, 00001},
   {00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 5001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 5001, 00000, 00000, 2010, 00000, 00001, 22001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 1001, 00000, 00000, 00000, 00000, 00001, 5001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 18001, 00001, 00001, 00001, 00001, 00001, 18001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 5001, 00001, 00001, 00001, 00001},
   {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
   },
};//多维数组存储地图

int map[5][14][14] = { {},
{
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00000, 00000, 100, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00000, 00000, 15010, 00000, 00001, 00001, 00000, 00001, 00001, 00001},
    {00001, 00001, 00001, 16001, 18001, 00000, 13001, 00000, 00000, 5001, 00000, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00000, 00000, 00001, 00000, 00000, 19010, 00000, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00000, 9010, 00000, 00000, 00000, 00000, 00001, 00001, 00001},
    { 00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 00001, 00001, 00001 },
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    },
    {
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 16001, 00001, 00000, 00000, 00000, 100, 00001, 00001, 00001},
    {00001, 00001, 00001, 00000, 00001, 1001, 00000, 00000, 00001, 00001, 00000, 00001, 00001, 00001},
    {00001, 00001, 00000, 20010, 00000, 00000, 00000, 5010, 00000, 00000, 00000, 00001, 00001, 00001},
    {00001, 00001, 00000, 14010, 00000, 9001, 00000, 00000, 00000, 00000, 00001, 00001, 00001, 00001},
    { 00001, 00001, 00000, 5001, 00000, 5001, 18001, 7001, 00000, 20001, 9001, 3001, 00001, 00001 },
    { 00001, 00001, 00000, 00000, 00000, 00000, 00000, 00000, 14010, 00000, 00001, 00001, 00001, 00001 },
    {00001, 00001, 00001, 00001, 00001, 20001, 00000, 00001, 00000, 00000, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    },
    {
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 100, 00000, 00000, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00000, 00000, 5010, 21010, 00001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00000, 00000, 00000, 20010, 00001, 00000, 00000, 00000, 00000, 00000, 00000, 00001},
    {00001, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 00000, 16001, 00000, 19010, 00000, 00001},
    {00001, 00000, 00000, 6001, 00000, 00000, 14010, 00000, 00000, 00000, 00000, 00001, 00001, 00001},
    {00001, 00001, 00000, 15001, 00000, 00000, 00000, 00000, 00000, 18001, 00000, 00000, 00001, 00001},
    {00001, 19001, 00000, 18001, 5001, 00000, 21001, 15001, 00000, 00000, 00000, 00000, 00000, 00001},
    {00001, 00001, 00001, 00000, 00000, 00000, 00001, 00001, 00001, 5001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 5001, 00000, 00000, 2010, 00000, 00001, 22001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 1001, 00000, 00000, 00000, 00000, 00001, 5001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 18001, 00001, 00001, 00001, 00001, 00001, 18001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 5001, 00001, 00001, 00001, 00001},
    {00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001, 00001},
    },
};
//多维数组存储地图
//移动方向输入
//char dir
char dir;
//剩余步数
//int flag
int set = 1;
/*
  初始化地图 init1 init2 init3
  判断移动方向
  判断人物对应移动方向上地图物品
  若为墙壁，则移动无效
  若为空地，则人物前进
  若为箱子，则判断箱子前方物体
            若为箱子则移动无效
            若为墙壁则移动无效
            若为空地则人物，箱子共同前进
  判断移动完成后步数是否归零，判断移动完成后是否达成胜利条件
  归零则跳转失败界面 胜利条件达成则跳转下一关或通关界面
*/
//-----------------------------------------------------service---------------------------------------------------------------
/*
负责人
功能，依照对应的关卡，分别初始化对应的地图与步数限制
init1将set重置为1
init2将set重置为2
...............
参数 void
返回 void
*/
void init1();
void init2();
void init3();

/*
负责人
功能；判断步数是否用尽
 参数 int flag
 返回 int
 0跳转失败界面 1表示继续
*/
int islose(int flag);
/*
负责人
功能，依照当前关卡，判断是否胜利
参数；void
返回;int
0则继续 1则跳转胜利界面
若是iswin 3 判断为1 则跳转通关页面
每当iswin判定成功 则set+1
*/
int iswin1();
int iswin2();
int iswin3();
/*
负责人
功能；判断人物移动依据移动方向
  判断人物对应移动方向上地图物品
  若为墙壁，则移动无效
  若为空地，则人物前进
  若为箱子，则判断箱子前方物体
            若为箱子则移动无效
            若为墙壁则移动无效
            若为空地则人物，箱子共同前进
  参数 char
  返回 int
  0移动失败 1移动成功
*/
int palayermove(char dir);

//------------------------------------------------------view---------------------------------------------------------------
/*
负责人
功能；展示选项
    开始游戏；进入第一关调用gameview
    设置；敬请期待
    玩法介绍；methodview
    制作组；makerview
    退出游戏；；exit(0)；
    背景介绍； 展示背景故事调用 backview（easyx）
*/
void menuview();
/*
  负责人
  功能 展示玩法（easyx）
  参数 void
  返回 void
*/
void methodview();
/*
 负责人
 功能 展示制作组名单 （easyx）
 参数void
 返回 void
*/
void makerview();
/*
负责人
功能 展示故事背景（easyx）
参数void
返回void
*/
void backview();
void superiseviwe();
/*
负责人
功能 失败页面
   返回menuview
   或回到gameview
参数void
返回void
*/
void defeatview();
/*
负责人
功能，根据map 打印地图（easyx）
       打印flag剩余
       打印按r重置
参数 void
返回 void
*/
void gameviewshowmap();
/*
负责人
功能 胜利界面
     下一关选项(可以直接前往gameview 用set完成关卡跳转)
     (winview3需要把下一关改为继续跳转passview)
参数 void
返回 void
*/
void winview1();
void winview2();
void winview3();
/*
负责人
功能 跳转通关与彩蛋页面
参数 void
返回 void
*/
void passview();
void image();
/*
负责人
功能整合
当set=1 初始化 调用init1
while(1){
打印游戏页面 gameviewshowmap
接受方向输入
若输入r跳转回gameview（即重置）
人物移动（playermove）（移动失败重新开始循环）
判断胜利（iswin1）
（若胜利，跳出循环）
flag--
判断失败 调用islose
set=2 调用init2............
set=3 调用init3............
*/
void gameview();
/*
负责人
登录页面
可以选择调用注册账号函数
跳转到注册页面
登录成功后跳转到游戏页面
*/
void enterview();
/*
负责人
注册页面
设置用户名和密码
注册成功后回到登录页面
*/
void registerview ();
int o = 2;

void chooseview()
{
    IMAGE img;
    loadimage(&img, "./选择.jpg", 21 * 60, 14 * 60);
    putimage(0, 0, &img);
    ExMessage msg;
    settextcolor(COLORREF(RGB(100, 120, 215)));
    settextstyle(40, 0, "黑体");
    cleardevice;
    outtextxy(600, 800, "返回");
    while (true)
    {
        if (peekmessage(&msg, EM_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x <= 600 && msg.y<= 400)
                {

                    o = 1;
                }

                else if (msg.x >= 700 && msg.y <= 400)
                {
                    o = 2;
                }
                else if(msg.y >= 400 && msg.y <= 700){
                     o = 0;
                }
                else {
                    menuview();
                }



                break;

            default:
                break;
            }
        }
        FlushBatchDraw();
    }
}
void BGM1()
{
    mciSendString("open 胜利.mp3 alias bgm1", NULL, 0, NULL);
    mciSendString("close bgm2", NULL, 0, NULL);
    mciSendString("close bgm3", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm1", NULL, 0, NULL);
}
void BGM2()
{
    mciSendString("open 失败.mp3 alias bgm2", NULL, 0, NULL);
    mciSendString("close bgm1", NULL, 0, NULL);
    mciSendString("close bgm3", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm2", NULL, 0, NULL);
}
void BGM3()
{
    mciSendString("open 蜜雪冰城.mp3 alias bgm3", NULL, 0, NULL);
    mciSendString("close bgm2", NULL, 0, NULL);
    mciSendString("close bgm1", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm3 repeat", NULL, 0, NULL);
}
void BGM4()
{
    mciSendString("open 游戏背景音乐.mp3 alias bgm4", NULL, 0, NULL);
    mciSendString("close bgm2", NULL, 0, NULL);
    mciSendString("close bgm3", NULL, 0, NULL);
    mciSendString("close bgm1", NULL, 0, NULL);
    mciSendString("play bgm4 repeat", NULL, 0, NULL);
}
int main() {
    BGM4();
    initgraph(1260, 840);
    
    set = 1;
    image();
    menuview();
    return 0;
}
void init1() {
    set = 1;
    flag = 30;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            map[set][i][j] = init_map[set][i][j];
    }
}
void init2() {
    set = 2;
    flag = 62;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            map[set][i][j] = init_map[set][i][j];
    }
}
void init3() {
    set = 3;
    flag = 100;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
            map[set][i][j] = init_map[set][i][j];
    }
}
int islose(int flag) {
    if (flag == 0)
    {
        return 0;
    }
    if (flag != 0)
        return 1;
}
int iswin1() {
    //fillcircle(50, 50, 500);
    //while (1);
    int ret;
    if (map[1][6][7] == 9010 && map[1][6][8] == 19010 && map[1][6][5] == 15010) {
        ret = 1;
        set++;
    }
    else {
        ret = 0;
    }
    return ret;
}
int iswin2() {
    int aet;
    if (map[2][7][4] == 14010 && map[2][8][5] == 14010 && map[2][5][5] == 20010 && map[2][7][8] == 5010) {
        aet = 1;
        set++;
    }
    else {
        aet = 0;
    }
    return aet;
}
int iswin3() {
    int bet;
    if (map[3][7][5] == 14010 && map[3][5][9] == 5010 && map[3][7][8] == 21010 && map[3][7][2] == 20010 && map[3][8][3] == 2010 && map[3][7][9] == 19010) {
        bet = 1;
        set++;
    }
    else {
        bet = 0;
    }

    return bet;
}
int palayermove(char dir) {
    int x = 0, y = 0, a=0, b=0;
    //for (; map[set][a][b] != 100; a++) {

    //    for (; map[set][a][b] != 100; b++) {}
    //}
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (map[set][i][j] == 100)
            {
                x = i;
                y = j;
                break;
            }
        }
    }

        switch (dir) {
        case 'd':if (map[set][x][y + 1] == 00000) {
            map[set][x][y + 1] = 100;
            map[set][x][y] = 00000;
            return 1;
        }
                if (map[set][x][y + 1]%10 == 00001)
                    return 0;

                if (map[set][x][y + 1] != 00001 && map[set][x][y + 1] != 00000)
                {
                    if (map[set][x][y + 2] == 00000) {
                        map[set][x][y + 2] = map[set][x][y + 1],
                            map[set][x][y + 1] = 100;
                            map[set][x][y] = 00000;
                        return 1;
                    }
                    if (map[set][x][y + 2] != 00000)
                        return 0;
                }
                break;
        case 'w':if (map[set][x - 1][y] == 00000) {
            map[set][x - 1][y] = 100;
            map[set][x][y] = 00000;
            return 1;
        }
                if (map[set][x - 1][y]%10 == 00001)
                    return 0;
                if (map[set][x - 1][y] != 00001 && map[set][x - 1][y] != 00000)
                {
                    if (map[set][x - 2][y] == 00000) {
                        map[set][x - 2][y] = map[set][x - 1][y],
                            map[set][x - 1][y] = 100;
                            map[set][x][y] = 00000;
                        return 1;
                    }
                    if (map[set][x - 1][y] != 00000)
                        return 0;
                }break;
        case 'a':
            if (map[set][x][y - 1] == 00000) 
            {
                map[set][x][y - 1] = 100;
                map[set][x][y] = 00000;
                //fillcircle(50, 50, 500);
                //while (1);
                return 1;
            }
            if (map[set][x][y - 1]%10 == 00001)
                return 0;
            if (map[set][x][y - 1] != 00001 && map[set][x][y - 1] != 00000)
            {
                if (map[set][x][y - 2] == 00000) {
                    map[set][x][y - 2] = map[set][x][y - 1],
                        map[set][x][y - 1] = 100;
                        map[set][x][y] = 00000;
                    return 1;
                }
                if (map[set][x][y - 1] != 00000)
                    return 0;
            }break;
        case 's':if (map[set][x + 1][y] == 00000) {
            map[set][x + 1][y] = 100,
                map[set][x][y] = 00000;
            return 1;
        }
            if (map[set][x + 1][y]%10 == 00001)
                return 0;
            if (map[set][x + 1][y] != 00001 && map[set][x + 1][y] != 00000)
            {
                if (map[set][x + 2][y] == 00000) {
                    map[set][x + 2][y] = map[set][x + 1][y],
                        map[set][x + 1][y] = 100,
                        map[set][x][y] = 00000;
                    return 1;
                }
                if (map[set][x + 1][y] != 00000)
                    return 0;
            }break;
        }
    
}
void menuview() {
    
    // int a = 1;
    IMAGE img;
    loadimage(&img, "./主页.png", 1260, 840);
    putimage(0, 0, &img);
    ExMessage m;        // 定义消息变量
    BeginBatchDraw();
    while (true)
    {
        // 获取一条鼠标或按键消息
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {
            /* case WM_MOUSEMOVE:
                 // 鼠标移动的时候画红色的小点
                 putpixel(m.x, m.y, RED);
                 printf("%d %d\n", m.x, m.y);
                 break;
                 */

        case WM_LBUTTONDOWN:

            if (m.x > 262 && m.x < 423 && m.y>343 && m.y < 381)
            {//开始游戏
               // printf("开始游戏\n");
                gameview();
            }

            if (m.x > 262 && m.x < 423 && m.y>480 && m.y < 522)
            {//登录，扩展内容
               // printf("登录\n");
            }

            if (m.x > 262 && m.x < 423 && m.y>635 && m.y < 672)
            {//玩法介绍
                //printf("玩法介绍\n");
                methodview();
            }

            if (m.x > 811 && m.x < 1024 && m.y>341 && m.y < 381)
            {//退出游戏
               // printf("退出游戏\n");
                exit(0);
            }

            if (m.x > 811 && m.x < 1024 && m.y>477 && m.y < 517)
            {//设置
                chooseview();

            }

            if (m.x > 811 && m.x < 1024 && m.y>635 && m.y < 676)
            {//步数排行榜
                //printf("排行榜\n");

            }

            if (m.x > 536 && m.x < 721 && m.y>759 && m.y < 815)
            {//制作组
               // printf("制作组\n");
                makerview();
            }

             if (m.x > 536 && m.x < 721 && m.y>635 && m.y < 672)
             {
                 backview();
             }
             

            break;
        }
        FlushBatchDraw();
    }
    // 关闭图形窗口
    //closegraph();

}
void methodview()
{
    //initgraph(21*60, 14*60);
    int a = 1;
    IMAGE img;
    ExMessage msg;
    loadimage(&img, "./bk3.png", 21*60, 14*60);
    putimage(0, 0, &img);
    while (1)
    {
        while (peekmessage(&msg))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >0 && msg.x < 21*60&& msg.y>0 && msg.y <14*60)
                {
                    menuview();

                }
                else {
                    break;
                }
            case WM_RBUTTONDOWN:
                break;
            }

        }
        FlushBatchDraw();

    }
    //closegraph();
}


void makerview() {
    //initgraph(1260, 840);
    IMAGE img_mm;
    loadimage(&img_mm, "./制作组.png",21*60,14*60);
    putimage(0, 0, &img_mm);
    ExMessage msg;
    while (1)
    {
        while (peekmessage(&msg))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x > 0 && msg.x < 21 * 60 && msg.y>0 && msg.y < 14 * 60)
                {
                    menuview();

                }
                else {
                    break;
                }
            case WM_RBUTTONDOWN:
                break;
            }

        }

        FlushBatchDraw();
    }
    //closegraph();

}
void backview() {
    //initgraph(21 * 60, 14 * 60);
    ExMessage msg;
    IMAGE img;
    loadimage(&img, "./背景.png", 21 * 60, 14 * 60);
    putimage(0, 0, &img);
    while (1)
    {
        while (peekmessage(&msg))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x > 0 && msg.x < 21*60 && msg.y>0 && msg.y < 14 * 60)
                {
                    menuview();

                }
                else {
                    break;
                }
            case WM_RBUTTONDOWN:
                break;
            }

        }
        FlushBatchDraw();


    }
    //closegraph();
}
bool button(int x, int y, int w, int h);
bool inarea(int mx, int my, int x, int y, int w, int h);
bool inarea(int mx, int my, int x, int y, int w, int h) {
    if (mx > x && mx<x + w && my>y && my < y + h) {
        return true;
    }
    return false;
}

bool button(int x, int y, int w, int h)
{
    ExMessage msg = { 0 };
    if (msg.message == WM_LBUTTONDOWN && inarea(msg.x, msg.y, x, y, w, h)) {
        return true;
    }
    return false;
}
void defeatview() {
    ExMessage msg = { 0 };
    BGM2();
    //initgraph(21 * 60, 14 * 60);
        setbkcolor(RGB(204, 247, 131));
        cleardevice();
        settextstyle(900, 300, "微软雅黑");
        settextcolor(RGB(129, 179, 55));
        outtextxy(330, 0, "菜");
        IMAGE img_pic2;
        IMAGE img_pic3;
        loadimage(&img_pic2, "./pic2.png", 100, 300);
        loadimage(&img_pic3, "./pic3.png", 100, 300);
        putimage(100, 500, &img_pic2);
        putimage(1050, 500, &img_pic3);
        ExMessage m;
        while (1)
        {
            m = getmessage(EX_MOUSE | EX_KEY);
            switch (m.message)
            {
            case WM_LBUTTONDOWN:
                if (m.x > 1000 && m.x < 1200)
                {
                    gameview();
                }
                else
                {
                    menuview();
                }
            case WM_RBUTTONDOWN:
                break;
            }
            FlushBatchDraw();
        }
        //closegraph();

}
void gameviewshowmap() {
    cleardevice();
    loadimage(0, "./bk4.png", 21 * 60, 14 * 60);

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            switch (map[set][i][j]) {
            case 00000:putimage(j * 60, i * 60, &img[0]);
                break;
            case 00001:putimage(j * 60, i * 60, &img[1]);
                break;
            case 100:
                putimage(j * 60, i * 60, &img[2]);
            
                    if (o == 1) {
                        putimage(j * 60, i * 60, &img[25]);
                    }
                    if (o == 0) {
                        putimage(j * 60, i * 60, &img[26]);
                    }
                break;
            case 1001:putimage(j * 60, i * 60, &img[3]);
                break;
            case 3001:putimage(j * 60, i * 60, &img[4]);
                break;
            case 5001:putimage(j * 60, i * 60, &img[5]);
                break;
            case 6001:putimage(j * 60, i * 60, &img[6]);
                break;
            case 7001:putimage(j * 60, i * 60, &img[7]);
                break;
            case 9001:putimage(j * 60, i * 60, &img[8]);
                break;
            case 13001:putimage(j * 60, i * 60, &img[9]);
                break;
            case 15001:putimage(j * 60, i * 60, &img[10]);
                break;
            case 16001:putimage(j * 60, i * 60, &img[11]);
                break;
            case 18001:putimage(j * 60, i * 60, &img[12]);
                break;
            case 19001:putimage(j * 60, i * 60, &img[13]);
                break;
            case 20001:putimage(j * 60, i * 60, &img[14]);
                break;
            case 21001:putimage(j * 60, i * 60, &img[15]);
                break;
            case 22001:putimage(j * 60, i * 60, &img[16]);
                break;
            case 2010:putimage(j * 60, i * 60, &img[17]);
                break;
            case 5010:putimage(j * 60, i * 60, &img[18]);
                break;
            case 9010:putimage(j * 60, i * 60, &img[19]);
                break;
            case 14010:putimage(j * 60, i * 60, &img[20]);
                break;
            case 15010:putimage(j * 60, i * 60, &img[21]);
                break;
            case 19010:putimage(j * 60, i * 60, &img[22]);
                break;
            case 20010:putimage(j * 60, i * 60, &img[23]);
                break;
            case 21010:putimage(j * 60, i * 60, &img[24]);
                break;
            default:
                break;
            }
        }
    }       
    setbkmode(TRANSPARENT);
    //FlushBatchDraw();
    settextcolor(COLORREF(RGB(0, 120, 215)));
    settextstyle(40, 0, "黑体");
    char s[5];
    sprintf(s, "%d", flag);
    outtextxy(900, 100, "剩余步数：");
    outtextxy(1090, 100, s);
    wchar_t num[20];
    _itow_s(flag, num, 10);
    outtextxy(1090, 100,num[20]);
    outtextxy(900, 350, "关卡：");
    char k[5];
    sprintf(k, "%d", set);
    outtextxy(1000, 350, k);
   /* wchar_t s[20];
    _itow_s(set, s, 10);*/
    outtextxy(1000, 350, s[20]);
    outtextxy(900, 600, "按r重置");
    FlushBatchDraw();
}

void winview1() {
    /*closegraph();
    initgraph(21 * 60, 40 * 60);*/
    BGM1();
    IMAGE img;
    loadimage(&img, "./win1.png", 1260, 840);
    putimage(0, 0, &img);
    ExMessage m;
    m = getmessage(EX_MOUSE | EX_KEY);
    while (1)
    {
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {

        case WM_LBUTTONDOWN:
            /*fillcircle(50, 50, 500);
            while (1);*/
            //if (m.x > 262 && m.x < 423 && m.y>343 && m.y < 381)
            //{
                gameview();
            //}
            break;
        }
        FlushBatchDraw();
    }
    //closegraph();

}
void winview2() {
    //initgraph(21 * 60, 40 * 60);
    BGM1();
    //IMAGE img;
    //loadimage(&img, "./win2.png", 1260, 840);
    //putimage(0, 0, &img);
    IMAGE img;
    loadimage(&img, "./win2.png", 1260, 840);
    putimage(0, 0, &img);
    ExMessage m;
    m = getmessage(EX_MOUSE | EX_KEY);
    while (1)
    {
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {

        case WM_LBUTTONDOWN:


                gameview();

            break;
        }
        FlushBatchDraw();
    }
    //closegraph();

}
void winview3() {
    //initgraph(21 * 60, 40 * 60);
    BGM1();
    set = 1;
    IMAGE img;
    loadimage(&img, "./win3.png", 1260, 840);
    putimage(0, 0, &img);
    ExMessage m;
    m = getmessage(EX_MOUSE | EX_KEY);
    while (1)
    {
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {

        case WM_LBUTTONDOWN:

            if (m.x > 0 && m.x < 21 * 60 && m.y>0 && m.y < 14 * 60)
            {
                passview();
            }
            break;
        }
        FlushBatchDraw();
    }
    //closegraph();

}
void surpriseview()
{
    BGM4();
    //initgraph(1260, 840);
    IMAGE image1;
    ExMessage n;
    loadimage(&image1, "./superise.png", 1260, 840);
    putimage(0, 0, &image1);
    while (1)
    {
        n = getmessage(EX_MOUSE | EX_KEY);
        switch (n.message)
        {
        case WM_LBUTTONDOWN:
            menuview();
        case WM_RBUTTONDOWN:
            break;
        }
        FlushBatchDraw();
    }
    //closegraph();

}
void passview() {
    //initgraph(1260, 840);
    IMAGE image;
    BGM3();
    ExMessage m;
    loadimage(&image, "./pass.png", 1260, 840);
    putimage(0, 0, &image);
    while (1)
    {
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message)
        {
        case WM_LBUTTONDOWN:
            if (m.x > 0 && m.x < 600)
            {
                surpriseview();
            }
            else
            {
                menuview();
            }
        case WM_RBUTTONDOWN:
            break;
        }
        FlushBatchDraw();
    }
    set = 1;
    //closegraph();

}

/*
负责人
功能整合
当set=1 初始化 调用init1
while(1){
打印游戏页面 gameviewshowmap
接受方向输入
若输入r跳转回gameview（即重置）
人物移动（playermove）（移动失败重新开始循环）
判断胜利（iswin1）
（若胜利，跳出循环）
flag--
判断失败 调用islose
set=2 调用init2............
set=3 调用init3............
*/
void gameview() {
    ExMessage m;
    BGM3();
    //BeginBatchDraw();
    if (set == 1) {
    began1:
        init1();
        while (1) {
            m = getmessage(EX_MOUSE | EX_KEY);
            //loadimage(&img[1], "./墙壁.png", 60, 60);
            //putimage(0, 0, &img[1]);
            //FlushBatchDraw();
            gameviewshowmap();
            //fillcircle(50, 50, 500);
           
            dir = _getch();
            if (dir == 'r') {
                goto began1;
            }
            if (dir != 'r') {
                //palayermove(dir);
                int curflag = palayermove(dir);
                if ( curflag== 0) {
                    continue;
                }
                else if (curflag == 1) {
                    if (iswin1()) {
                        winview1();
                        break;
                    }
                    else {
                        flag--;
                        //fillcircle(50, 50, 500);
                        //while (1);
                        islose(flag);
                        if (islose(flag)) {

                            continue;

                        }
                        else {
                            defeatview();
                            break;
                        }
                    }

                }


            }
            
            //FlushBatchDraw();
        }
    }
    if (set == 2) {
    began2:
        init2();
        while (1) {
            m = getmessage(EX_MOUSE | EX_KEY);
            gameviewshowmap();
            dir = _getch();
            if (dir == 'r') {
                goto began2;
            }
            if (dir != 'r') {
                //palayermove(dir);
                int curflag = palayermove(dir);
                if (curflag == 0) {
                    continue;
                }
                else if (curflag == 1) {
                    if (iswin2()) {
                        winview2();
                        break;
                    }
                    else {
                        flag--;
                        //fillcircle(50, 50, 500);
                        //while (1);
                        islose(flag);
                        if (islose(flag)) {

                            continue;

                        }
                        else {
                            defeatview();
                            break;
                        }
                    }

                }


            }

            //FlushBatchDraw();
        }
    }
    if (set == 3) {
    began3:
        init3();
        while (1) {
            m = getmessage(EX_MOUSE | EX_KEY);
            gameviewshowmap();
            dir = _getch();
            if (dir == 'r') {
                goto began3;
            }
            if (dir != 'r') {
                //palayermove(dir);
                int curflag = palayermove(dir);
                if (curflag == 0) {
                    continue;
                }
                else if (curflag == 1) {
                    if (iswin3()) {
                        winview3();
                        break;
                    }
                    else {
                        flag--;
                        //fillcircle(50, 50, 500);
                        //while (1);
                        islose(flag);
                        if (islose(flag)) {

                            continue;

                        }
                        else {
                            defeatview();
                            break;
                        }
                    }

                }


            }

            FlushBatchDraw();
        }
    }
}
    void enterview() {

    }


void registerview() {

}

void image() {
    //initgraph(21 * 60, 14 * 60);
    loadimage(&img[0], "./空地.png", 60, 60);
    loadimage(&img[1], "./墙壁.png", 60, 60);
    
        loadimage(&img[2], "./人物.jpg", 60, 60);
    
    
        loadimage(&img[25], "./人物3.jpg",60, 60);
    
    
        loadimage(&img[26], "./人物2.jpg", 60, 60);
    
    loadimage(&img[3], "./a).png", 60, 60);
    loadimage(&img[4], "./c).png", 60, 60);
    loadimage(&img[5], "./e).png", 60, 60);
    loadimage(&img[6], "./f).png", 60, 60);
    loadimage(&img[7], "./g).png", 60, 60);
    loadimage(&img[8], "./i).png", 60, 60);
    loadimage(&img[9], "./m）.png", 60, 60);
    loadimage(&img[10],"./o).png", 60, 60);
    loadimage(&img[11],"./p).png", 60, 60);
    loadimage(&img[12],"./r).png", 60, 60);
    loadimage(&img[13], "./s).png", 60, 60);
    loadimage(&img[14], "./t).png", 60, 60);
    loadimage(&img[15], "./u).png", 60, 60);
    loadimage(&img[16], "./v).png", 60, 60);
    loadimage(&img[17], "./b.png", 60, 60);
    loadimage(&img[18], "./e.png", 60, 60);
    loadimage(&img[19], "./i.png", 60, 60);
    loadimage(&img[20], "./n.png", 60, 60);
    loadimage(&img[21], "./o.png", 60, 60);
    loadimage(&img[22], "./s.png", 60, 60);
    loadimage(&img[23], "./t.png", 60, 60);
    loadimage(&img[24], "./u.png", 60, 60);
}
