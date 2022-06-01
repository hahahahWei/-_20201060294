

#include<windows.h>
#include<math.h>
#include<gl/glut.h>
#include<GL/gl.h>
#include<stdlib.h>
#include<iostream>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include <iostream>
#include <windows.h>
#include <gl/glut.h>

#include<windows.h>
#include<math.h>
#include<gl/glut.h>
#include<GL/gl.h>
#include<stdlib.h>
#include<iostream>
#include<gl/glut.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include <iostream>
#include <windows.h>
#include <gl/glut.h>

//#include "stdafx.h"

#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
#include<vector>

using namespace std;



//此处定义出了边框的边界

#define XL 100

#define XR 400

#define YL 100

#define YR 400





//定义点结构

struct Points

{

float x;

float y;

};



//定义边框

struct Border

{

float xl;

float xr;

float yl;

float yr;

};



//多边形的几个顶点

vector<Points> p = { {200,450},{450,300},{300,50},{50,200} };

Border rectangles = { XL,XR,YL,YR };



//画直线

void LineGL(Points &p1, Points &p2) {

glBegin(GL_LINES);

glColor3f(0.0f, 1.0f, 0.0f);

glVertex2f(p1.x, p1.y);

glColor3f(0.0f, 1.0f, 0.0f);

glVertex2f(p2.x, p2.y);

glEnd();

}

//计算线与边界x的交点坐标

Points interactionx(float &borde,Points &x,Points &y) {

float k, b;

Points result;

k = (y.y - x.y) / (y.x - x.x);

b = (y.x*x.y - x.x*y.y) / (y.x - x.x);

float yy = k * borde + b;

result.x = borde;

result.y = yy;



return result;

}

//计算线与边界y的交点坐标

Points interactiony(float &borde, Points &x, Points &y) {

float k, b;

Points result;

k = (y.y - x.y) / (y.x - x.x);

b = (y.x*x.y - x.x*y.y) / (y.x - x.x);

float xx = (borde - b) / k;

result.y = borde;

result.x = xx;



return result;

}



//核心算法 每条边按照一定的顺序进行相应的判断，然后更新这个新的含points的表，将最后的表再进行画出来

vector<Points> SutherlandHodgman(Border &border, vector<Points> &pp) {//输入边界和要剪切的图形

vector<Points> r1, r;

//判断 从最左边的XL开始

for (int i = 0; i < pp.size(); i++) {

//判断 由于一条线段是由两个点组成，所以相邻的两个点自发形成一条线段，最后的一个点与第一个点形成线段

if (i == pp.size() - 1) {//最后一个点与第一个点形成一条线段，单独先处理出来

int x1 = pp[i].x - border.xl;

int x2 = pp[0].x - border.xl;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

Points poin;

if (x2 == 0) {

r1.push_back(pp[0]);

}

else {

Points px = interactionx(border.xl, pp[i], pp[0]);

r1.push_back(px);

r1.push_back(pp[0]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(pp[i]);

}

else

{

Points px = interactionx(border.xl, pp[i], pp[0]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(pp[0]);

}

}

else {//其余的线段正常处理

int x1 = pp[i].x - border.xl;

int x2 = pp[i+1].x - border.xl;

//处理四种情况

//第一种情况：两个点都在边界之外

if (x1 < 0 && x2 < 0) {



}

//第二种情况：第一个点在边界外，第二个点在边界内或边界上

else if (x1 < 0 && x2 >= 0) {

if (x2 == 0) {

r1.push_back(pp[i + 1]);

}

else {

Points px = interactionx(border.xl, pp[i], pp[i + 1]);

r1.push_back(px);

r1.push_back(pp[i + 1]);

}

}

//第三种情况：第一个点在边界上或边界内，第二个点在边界外

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(pp[i]);

}

else

{

Points px = interactionx(border.xl, pp[i], pp[i + 1]);

r1.push_back(px);

}

}

//第四种情况：两个点都在边界内或者边界上

else if(x1>=0 && x2>=0)

{

r1.push_back(pp[i + 1]);

}

}

}

r.assign(r1.begin(), r1.end());

r1.clear();



//最上边yr

for (int i = 0; i < r.size(); i++) {

if (i == r.size() - 1) {

int x1 = border.yr - r[i].y;

int x2 = border.yr - r[0].y;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

if (x2 == 0) {

r1.push_back(r[0]);

}

else {

Points px = interactiony(border.yr, r[i], r[0]);

r1.push_back(px);

r1.push_back(r[0]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactiony(border.yr, r[i], r[0]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[0]);

}

}

else {

int x1 = border.yr - r[i].y;

int x2 = border.yr - r[i+1].y;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

Points poin;

if (x2 == 0) {

r1.push_back(r[i + 1]);

}

else {

Points px = interactiony(border.yr, r[i], r[i + 1]);

r1.push_back(px);

r1.push_back(r[i + 1]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactiony(border.yr, r[i], r[i + 1]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[i + 1]);

}

}

}

r.clear();

r.assign(r1.begin(), r1.end());

r1.clear();





//最右边xr

for (int i = 0; i < r.size(); i++) {

if (i == r.size() - 1) {

int x1 = border.xr - r[i].x;

int x2 = border.xr - r[0].x;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

Points poin;

if (x2 == 0) {

r1.push_back(r[0]);

}

else {

Points px = interactionx(border.xr, r[i], r[0]);

r1.push_back(px);

r1.push_back(r[0]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactionx(border.xr, r[i], r[0]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[0]);

}

}

else {

int x1 = border.xr - r[i].x;

int x2 = border.xr - r[i + 1].x;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

if (x2 == 0) {

r1.push_back(r[i + 1]);

}

else {

Points px = interactionx(border.xr, r[i], r[i + 1]);

r1.push_back(px);

r1.push_back(r[i + 1]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactionx(border.xr, r[i], r[i + 1]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[i + 1]);

}

}

}

r.clear();

r.assign(r1.begin(), r1.end());

r1.clear();



//最下边yl

for (int i = 0; i < r.size(); i++) {

if (i == r.size() - 1) {

int x1 = r[i].y - border.yl;

int x2 = r[0].y - border.yl;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

Points poin;

if (x2 == 0) {

r1.push_back(r[0]);

}

else {

Points px = interactiony(border.yl, r[i], r[0]);

r1.push_back(px);

r1.push_back(r[0]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactiony(border.yl, r[i], r[0]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[0]);

}

}

else {

int x1 = r[i].y - border.yl;

int x2 = r[i+1].y - border.yl;

if (x1 < 0 && x2 < 0) {



}

else if (x1 < 0 && x2 >= 0) {

Points poin;

if (x2 == 0) {

r1.push_back(r[i + 1]);

}

else {

Points px = interactiony(border.yl, r[i], r[i + 1]);

r1.push_back(px);

r1.push_back(r[i + 1]);

}

}

else if (x1 >= 0 && x2 < 0) {

if (x1 == 0) {

r1.push_back(r[i]);

}

else

{

Points px = interactiony(border.yl, r[i], r[i + 1]);

r1.push_back(px);

}

}

else if (x1 >= 0 && x2 >= 0)

{

r1.push_back(r[i + 1]);

}

}

}

r.clear();

r.assign(r1.begin(), r1.end());

return r;

}









//初始化整个界面

void Init() {

glClearColor(0.0, 0.0, 0.0, 0.0);

glShadeModel(GL_FLAT);

//按下c键会进行剪裁，按下r键会复原，按下x键会退出窗口

printf("Press key 'c' to Clip!\nPress key 'r' to Recover\nPress key 'x' to Exit\n");

}



//窗口大小的改变函数

void Reshape(int w, int h) {

glViewport(0, 0, (GLsizei)w, (GLsizei)h);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);

}



//未剪裁前的显示

void display() {

glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0f, 0.0f, 0.0f);

glPointSize(2);

//画矩形 使用的是红色

glBegin(GL_LINE_LOOP);

glVertex2f(XL, YL);

glVertex2f(XR, YL);

glVertex2f(XR, YR);

glVertex2f(XL, YR);

glEnd();



//画出最先开始的直线，没有经过任何修改

for (int i = 0; i < p.size(); i++) {

if (i == p.size() - 1) {

LineGL(p[p.size() - 1], p[0]);

}

else {

LineGL(p[i], p[i + 1]);

}

}

glFlush();

}



//键盘监听事件

void keyboard(unsigned char key, int x, int y) {

switch (key) {

case 'c':

//按下c键以后，会进行裁剪工作

p = SutherlandHodgman(rectangles, p);//调用函数得到最新的点

glutPostRedisplay();//当前窗口重新绘制

break;

case 'r':

//按下r键以后，原来的直线恢复，出现原本的线

p = { {200,450},{450,300},{300,50},{50,200} };

Init();

glutPostRedisplay();

break;

case 'x'://退出

exit(0);

break;

default:

break;

}

}





int main(int argc, char* argv[])

{

glutInit(&argc, argv);//从main函数传递参数

//设置显示模式，单缓冲，RGB

glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

glutInitWindowPosition(400, 200);//窗口位置

glutInitWindowSize(500, 500);//窗口大小

glutCreateWindow("Sutherland_Hodgman");//窗口标题



Init();//初始化



glutDisplayFunc(&display);//渲染函数

glutReshapeFunc(Reshape); //窗口函数发生改变时调用函数

glutKeyboardFunc(&keyboard);//调用键盘监听事件

glutMainLoop();//循环消息机制



return 0;

}
