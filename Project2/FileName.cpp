
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
//-----------------------------�������-----------------------------------------
struct Player // ���ڼ�¼���λ��
{
    int i;
    int j;
};
Player player;//���ȫ�ֱ���
/*��ͼ
��ͼ�и�����
����ҳ��
*/
IMAGE img[27];
int remake;//�����Ƿ�����=0������ =1����
/*��ͼ���
     map[[i][j]��ʾ����
     int����ǰ�������ֱ�ʾ��ĸ  ����������Ϊ��    ���ĸ��ж�����   ������ж�ǽ
     ��03 0 1 0  03��ʾc 0��ʾ������ 1��ʾ������ 0��ʾ����ǽ��
     ʹ��ʱ���õ�ǰ��ͼmapnow���ڵڼ��ؾͰ��ĸ�map��ֵ��mapnpw
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
};//��ά����洢��ͼ

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
//��ά����洢��ͼ
//�ƶ���������
//char dir
char dir;
//ʣ�ಽ��
//int flag
int set = 1;
/*
  ��ʼ����ͼ init1 init2 init3
  �ж��ƶ�����
  �ж������Ӧ�ƶ������ϵ�ͼ��Ʒ
  ��Ϊǽ�ڣ����ƶ���Ч
  ��Ϊ�յأ�������ǰ��
  ��Ϊ���ӣ����ж�����ǰ������
            ��Ϊ�������ƶ���Ч
            ��Ϊǽ�����ƶ���Ч
            ��Ϊ�յ���������ӹ�ͬǰ��
  �ж��ƶ���ɺ����Ƿ���㣬�ж��ƶ���ɺ��Ƿ���ʤ������
  ��������תʧ�ܽ��� ʤ�������������ת��һ�ػ�ͨ�ؽ���
*/
//-----------------------------------------------------service---------------------------------------------------------------
/*
������
���ܣ����ն�Ӧ�Ĺؿ����ֱ��ʼ����Ӧ�ĵ�ͼ�벽������
init1��set����Ϊ1
init2��set����Ϊ2
...............
���� void
���� void
*/
void init1();
void init2();
void init3();

/*
������
���ܣ��жϲ����Ƿ��þ�
 ���� int flag
 ���� int
 0��תʧ�ܽ��� 1��ʾ����
*/
int islose(int flag);
/*
������
���ܣ����յ�ǰ�ؿ����ж��Ƿ�ʤ��
������void
����;int
0����� 1����תʤ������
����iswin 3 �ж�Ϊ1 ����תͨ��ҳ��
ÿ��iswin�ж��ɹ� ��set+1
*/
int iswin1();
int iswin2();
int iswin3();
/*
������
���ܣ��ж������ƶ������ƶ�����
  �ж������Ӧ�ƶ������ϵ�ͼ��Ʒ
  ��Ϊǽ�ڣ����ƶ���Ч
  ��Ϊ�յأ�������ǰ��
  ��Ϊ���ӣ����ж�����ǰ������
            ��Ϊ�������ƶ���Ч
            ��Ϊǽ�����ƶ���Ч
            ��Ϊ�յ���������ӹ�ͬǰ��
  ���� char
  ���� int
  0�ƶ�ʧ�� 1�ƶ��ɹ�
*/
int palayermove(char dir);

//------------------------------------------------------view---------------------------------------------------------------
/*
������
���ܣ�չʾѡ��
    ��ʼ��Ϸ�������һ�ص���gameview
    ���ã������ڴ�
    �淨���ܣ�methodview
    �����飻makerview
    �˳���Ϸ����exit(0)��
    �������ܣ� չʾ�������µ��� backview��easyx��
*/
void menuview();
/*
  ������
  ���� չʾ�淨��easyx��
  ���� void
  ���� void
*/
void methodview();
/*
 ������
 ���� չʾ���������� ��easyx��
 ����void
 ���� void
*/
void makerview();
/*
������
���� չʾ���±�����easyx��
����void
����void
*/
void backview();
void superiseviwe();
/*
������
���� ʧ��ҳ��
   ����menuview
   ��ص�gameview
����void
����void
*/
void defeatview();
/*
������
���ܣ�����map ��ӡ��ͼ��easyx��
       ��ӡflagʣ��
       ��ӡ��r����
���� void
���� void
*/
void gameviewshowmap();
/*
������
���� ʤ������
     ��һ��ѡ��(����ֱ��ǰ��gameview ��set��ɹؿ���ת)
     (winview3��Ҫ����һ�ظ�Ϊ������תpassview)
���� void
���� void
*/
void winview1();
void winview2();
void winview3();
/*
������
���� ��תͨ����ʵ�ҳ��
���� void
���� void
*/
void passview();
void image();
/*
������
��������
��set=1 ��ʼ�� ����init1
while(1){
��ӡ��Ϸҳ�� gameviewshowmap
���ܷ�������
������r��ת��gameview�������ã�
�����ƶ���playermove�����ƶ�ʧ�����¿�ʼѭ����
�ж�ʤ����iswin1��
����ʤ��������ѭ����
flag--
�ж�ʧ�� ����islose
set=2 ����init2............
set=3 ����init3............
*/
void gameview();
/*
������
��¼ҳ��
����ѡ�����ע���˺ź���
��ת��ע��ҳ��
��¼�ɹ�����ת����Ϸҳ��
*/
void enterview();
/*
������
ע��ҳ��
�����û���������
ע��ɹ���ص���¼ҳ��
*/
void registerview ();
int o = 2;

void chooseview()
{
    IMAGE img;
    loadimage(&img, "./ѡ��.jpg", 21 * 60, 14 * 60);
    putimage(0, 0, &img);
    ExMessage msg;
    settextcolor(COLORREF(RGB(100, 120, 215)));
    settextstyle(40, 0, "����");
    cleardevice;
    outtextxy(600, 800, "����");
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
    mciSendString("open ʤ��.mp3 alias bgm1", NULL, 0, NULL);
    mciSendString("close bgm2", NULL, 0, NULL);
    mciSendString("close bgm3", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm1", NULL, 0, NULL);
}
void BGM2()
{
    mciSendString("open ʧ��.mp3 alias bgm2", NULL, 0, NULL);
    mciSendString("close bgm1", NULL, 0, NULL);
    mciSendString("close bgm3", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm2", NULL, 0, NULL);
}
void BGM3()
{
    mciSendString("open ��ѩ����.mp3 alias bgm3", NULL, 0, NULL);
    mciSendString("close bgm2", NULL, 0, NULL);
    mciSendString("close bgm1", NULL, 0, NULL);
    mciSendString("close bgm4", NULL, 0, NULL);
    mciSendString("play bgm3 repeat", NULL, 0, NULL);
}
void BGM4()
{
    mciSendString("open ��Ϸ��������.mp3 alias bgm4", NULL, 0, NULL);
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
    loadimage(&img, "./��ҳ.png", 1260, 840);
    putimage(0, 0, &img);
    ExMessage m;        // ������Ϣ����
    BeginBatchDraw();
    while (true)
    {
        // ��ȡһ�����򰴼���Ϣ
        m = getmessage(EX_MOUSE | EX_KEY);

        switch (m.message)
        {
            /* case WM_MOUSEMOVE:
                 // ����ƶ���ʱ�򻭺�ɫ��С��
                 putpixel(m.x, m.y, RED);
                 printf("%d %d\n", m.x, m.y);
                 break;
                 */

        case WM_LBUTTONDOWN:

            if (m.x > 262 && m.x < 423 && m.y>343 && m.y < 381)
            {//��ʼ��Ϸ
               // printf("��ʼ��Ϸ\n");
                gameview();
            }

            if (m.x > 262 && m.x < 423 && m.y>480 && m.y < 522)
            {//��¼����չ����
               // printf("��¼\n");
            }

            if (m.x > 262 && m.x < 423 && m.y>635 && m.y < 672)
            {//�淨����
                //printf("�淨����\n");
                methodview();
            }

            if (m.x > 811 && m.x < 1024 && m.y>341 && m.y < 381)
            {//�˳���Ϸ
               // printf("�˳���Ϸ\n");
                exit(0);
            }

            if (m.x > 811 && m.x < 1024 && m.y>477 && m.y < 517)
            {//����
                chooseview();

            }

            if (m.x > 811 && m.x < 1024 && m.y>635 && m.y < 676)
            {//�������а�
                //printf("���а�\n");

            }

            if (m.x > 536 && m.x < 721 && m.y>759 && m.y < 815)
            {//������
               // printf("������\n");
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
    // �ر�ͼ�δ���
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
    loadimage(&img_mm, "./������.png",21*60,14*60);
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
    loadimage(&img, "./����.png", 21 * 60, 14 * 60);
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
        settextstyle(900, 300, "΢���ź�");
        settextcolor(RGB(129, 179, 55));
        outtextxy(330, 0, "��");
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
    settextstyle(40, 0, "����");
    char s[5];
    sprintf(s, "%d", flag);
    outtextxy(900, 100, "ʣ�ಽ����");
    outtextxy(1090, 100, s);
    wchar_t num[20];
    _itow_s(flag, num, 10);
    outtextxy(1090, 100,num[20]);
    outtextxy(900, 350, "�ؿ���");
    char k[5];
    sprintf(k, "%d", set);
    outtextxy(1000, 350, k);
   /* wchar_t s[20];
    _itow_s(set, s, 10);*/
    outtextxy(1000, 350, s[20]);
    outtextxy(900, 600, "��r����");
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
������
��������
��set=1 ��ʼ�� ����init1
while(1){
��ӡ��Ϸҳ�� gameviewshowmap
���ܷ�������
������r��ת��gameview�������ã�
�����ƶ���playermove�����ƶ�ʧ�����¿�ʼѭ����
�ж�ʤ����iswin1��
����ʤ��������ѭ����
flag--
�ж�ʧ�� ����islose
set=2 ����init2............
set=3 ����init3............
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
            //loadimage(&img[1], "./ǽ��.png", 60, 60);
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
    loadimage(&img[0], "./�յ�.png", 60, 60);
    loadimage(&img[1], "./ǽ��.png", 60, 60);
    
        loadimage(&img[2], "./����.jpg", 60, 60);
    
    
        loadimage(&img[25], "./����3.jpg",60, 60);
    
    
        loadimage(&img[26], "./����2.jpg", 60, 60);
    
    loadimage(&img[3], "./a).png", 60, 60);
    loadimage(&img[4], "./c).png", 60, 60);
    loadimage(&img[5], "./e).png", 60, 60);
    loadimage(&img[6], "./f).png", 60, 60);
    loadimage(&img[7], "./g).png", 60, 60);
    loadimage(&img[8], "./i).png", 60, 60);
    loadimage(&img[9], "./m��.png", 60, 60);
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
