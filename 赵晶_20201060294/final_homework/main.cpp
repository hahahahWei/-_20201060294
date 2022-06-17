#include<windows.h>//放在程序第一行
#include<math.h>
#include<gl/glut.h>
#include<GL/gl.h>
#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define stripeImageWidth 32
float fTranslate;
float fRotate;
float fScale = 1.0f;
float color_b = 1.0f;

bool bPersp = false;//透视模式
bool bAnim = false;//场景自转
bool bWire = false;//边缘填充
bool isWhite = true;

int wHeight = 0;
int wWidth = 0;

GLfloat color[] = {1.0, 0.0, 0, 1}; // 定义颜色

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

GLfloat spotangle = 10.0f; //角度

//环境光位置
GLfloat light_x = 0.0f;
GLfloat light_y = 1.0f;
GLfloat light_z = 0.0f;

//聚光灯方向
GLfloat dir_x = 0.0f;
GLfloat dir_y = 0.0f;
GLfloat dir_z = 0.0f;
GLubyte stripeImage[8 * stripeImageWidth];

//设置茶壶的纹理颜色
void makeStripeImage(void)
{
    int j;
    for (j = 0; j < stripeImageWidth; j++)
    {

        stripeImage[ 8* j + 0] = (GLubyte)((j < 4) ? 10 : -10);
         stripeImage[ 8* j + 1] = (GLubyte)((j < 8) ? 100 : -100);
        stripeImage[8 * j + 2] = (GLubyte)((j < 16) ? 200 : -200);
         stripeImage[ 8* j + 3] = (GLubyte)((j <= 30) ? 500 : -300);
        stripeImage[8 * j + 4] = (GLubyte)-10;
        stripeImage[8 * j + 5] = (GLubyte)-100;
        stripeImage[8 * j + 6] = (GLubyte)-200;
        stripeImage[8 * j + 7] = (GLubyte)500;
    }
}

static GLfloat xequalzero[] = { 0.0, 1.0, 1.0, 0.0 };
static GLfloat slanted[] = { 0.0, 0.0, 1.0, 0.0 };
static GLfloat *currentCoeff;
static GLenum currentPlane;
static GLint currentGenMode;
static float roangles;
//初始化窗口
void init(void)
{
   // glClearColor(1.0, 1.0, 1.0, 1.0);//设定颜色
    glEnable(GL_DEPTH_TEST);//开启更新深度缓冲区的功能
    glShadeModel(GL_SMOOTH);
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage1D(GL_TEXTURE_1D, 0, 3, stripeImageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    /*设置纹理和物体表面颜色处理方式*/
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//和物体表面颜色做与运算
    /*设置自动生成纹理坐标的计算方式*/
    currentCoeff = xequalzero;
    currentGenMode = GL_OBJECT_LINEAR;
    currentPlane = GL_OBJECT_PLANE;
    //一维纹理，只有S坐标
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整形形式
    glTexGenfv(GL_S, currentPlane, currentCoeff);//向量形式
    glEnable(GL_TEXTURE_GEN_S);//激活s坐标的纹理坐标生成
    glEnable(GL_TEXTURE_1D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
    //roangles = 45.0f;
}

//展示要显示的物体（此处是3个茶壶）
void display(void) {
     GLfloat mat_diffuse0[] = {1, 10, 8, 1.000000};
	GLfloat mat_specular[] = {0.296648, 5, 0.296648, 0.922000};
//GLfloat mat_shininess[] = {100}; //材质RGBA镜面指数，数值在0～128范围内
	GLfloat mat_diffuse1[] = {100, 0.606480, 0.226480, 1.000000};
	GLfloat mat_diffuse2[] = {0, 0.8, 0.8, 1};
//画中间的茶壶
glPushMatrix();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    //glRotatef(2, 0.0, 0.0, 1.0);
    glRotatef(1, 0, 90, 0);//绕x轴旋转
    glutSolidTeapot(8);
 glPopMatrix();
//    glFlush();

    //画最外面的茶壶

	glPushMatrix();//把当前的状态做成一个副本放入栈
	//glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT ); //S 方向重复
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);//T方向重复
glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT ); //S 方向重复
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);//T方向重复


        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse1);// 设置多边形正面的镜面反射属性
	/*定义平移矩阵，相对于当前所在的屏幕位置移动
	参数分别表示x,y,z分别指定沿x,y,z轴方向的平移分量*/
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);


	glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);// 设置多边形正面的镜面反射属性
	/*指定用于光照计算的当前材质属性
	参数：1.指出材质属性将用于物体的哪一面
	2.指出要设置哪种材质的属性GL_SPECULAR：材质的镜面反射颜色*/
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS,40);// 指定镜面指数
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse0); //设置多边形正面漫反射属性
	/*定义平移矩阵，相对于当前所在的屏幕位置移动
	参数分别表示x,y,z分别指定沿x,y,z轴方向的平移分量*/
	glTranslatef(0, 0, 1);
	/*参数：angle：为旋转的角度，单位为度。
     x,y,z：为对应xyz轴的布尔值变量。表示绕哪个坐标轴旋转，谁为1绕谁转*/
	glRotatef(90, 1,0, 0);//绕x轴旋转
	glutSolidTeapot(16);//实心茶壶，参数表示大小
	glPopMatrix();//恢复刚才一系列的变换，出栈

//画最小的茶壶

	glPushMatrix();//入栈
	/*指定用于光照计算的当前材质属性
	参数：1.指出材质属性将用于物体的哪一面
	2.指出要设置哪种材质的属性GL_SPECULAR：材质的镜面反射颜色*/
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diffuse2);// 设置多边形正面的镜面反射属性
	/*定义平移矩阵，相对于当前所在的屏幕位置移动
	参数分别表示x,y,z分别指定沿x,y,z轴方向的平移分量*/
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);//设置多边形正面漫反射属性

	glTranslatef(0, 0, 1);
	//Draw_Leg();
	/*glScalef是模型缩放函数，参数x,y,z分别为模型在x,y,z轴方向的缩放比*/
	glScalef(1, 1, 1);
glRotatef(90, 1,0, 0);//绕x轴旋转
	glutSolidTeapot(2);
	//glTranslatef(-1.5, -1, -1.5);
	glPopMatrix();//出栈

	// glEnable(GL_DEPTH_TEST);
//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 清除屏幕
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置视角
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//恢复初始坐标系（类似复位操作时图像位于窗口中心）
	gluPerspective(75, 1, 1, 4000);//透视投影
	glMatrixMode(GL_MODELVIEW);//告诉计算机接下来要做什么，此处时模型视图
	glLoadIdentity();
glFlush();
};

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4, 4, -4*(GLfloat)h / (GLfloat)w, 4*(GLfloat)h / (GLfloat)w, -4, 4);
    else
        glOrtho(-4*(GLfloat)w / (GLfloat)h, 4*(GLfloat)w / (GLfloat)h, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-4, 0,700, 0, 0, 0, 0, 0, 1);

glFlush();

	glEnd();
}

void idle()
{
    roangles += 0.05f;
     /*标记当前窗口需要重新绘制。通过glutMainLoop下一次循环时，
    窗口显示将被回调以重新显示窗口的正常面板。多次调用glutPostRedisplay，
    在下一个显示回调只产生单一的重新显示回调。*/
    glutPostRedisplay();
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//实现双缓存技术，但是图片会闪烁
}

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': //退出
	    exit(0);
	    break;
    case 'w': //整体上移
    case 'W':
        eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	case 'e': //整体下移
    case 'E':
        eye[1] += 0.2f;
		center[1] += 0.2f;

		break;
	case 'r': //整体左移
    case 'R':
		eye[0] += 0.2;
		center[0] += 0.2;
		break;
	case 't': //整体右移
    case 'T':
		eye[0] -= 0.2;
		center[0] -= 0.2;
		break;

    case 'y'://开启或关闭场景自转
    case 'Y':
	    bAnim = !bAnim;
	    break;
  case 'u'://纹理转换
   case 'U':
        currentGenMode = GL_EYE_LINEAR;//视觉坐标系中计算纹理坐标
        currentPlane = GL_EYE_PLANE;//向量形式
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);
        glTexGenfv(GL_S, currentPlane, currentCoeff);
        glutPostRedisplay();
        break;
    case 'i'://纹理转换
    case 'I':
        currentGenMode = GL_OBJECT_LINEAR;//模型坐标系中计算纹理坐标
        currentPlane = GL_OBJECT_PLANE;
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, currentGenMode);//整数形式
        glTexGenfv(GL_S, currentPlane, currentCoeff);//模型坐标系中计算，计算系数由currentCoeff向量指定
        glutPostRedisplay();
        break;
	case 'o': //实心<——>线性
    case 'O':
	    bWire = !bWire;
	    break;

    case 'p':
    case 'P'://环境光上移
		light_y = light_y + 1;
		break;
	case 'a': //环境光下移
    case 'A':
		light_y = light_y - 1;
		break;
    case 's': //环境光左移
    case 'S':
		light_x = light_x - 1;
		break;
	case 'd': //环境光右移
    case 'D':
		light_x = light_x + 1;
		break;
    case 'f': //环境光前移
    case 'F':
		light_z = light_z + 1;
		break;
	case 'g': //环境光后移
    case 'G':
		light_z = light_z - 1;
		break;
	case 'h': //环境光颜色切换
    case 'H':
		isWhite = !isWhite;
		break;

	case 'j'://聚光灯上移
    case 'J':
		dir_y = dir_y + 1;
		break;
	case 'k'://聚光灯下移
    case 'K':
		dir_y = dir_y - 1;
		break;
    case 'l': //聚光灯左移
    case 'L':
		dir_x = dir_x - 1;
		break;
    case 'z': //聚光灯右移
    case 'Z':
		dir_x = dir_x + 1;
		break;
	case 'x': //聚光灯前移
    case 'X':
		dir_z = dir_z + 1;
		break;
	case 'c': //聚光灯后移
    case 'C':
		dir_z = dir_z - 1;
		break;
	case 'v':  //聚光灯角度变大
    case 'V':
		if (spotangle <= 89.0f) {
			spotangle = spotangle + 0.2f;
		}
		break;
	case 'b':
    case 'B'://聚光灯角度变小
		if (spotangle >= 1.0f)
			spotangle = spotangle - 0.2f;

		break;



    case '1':
        eye[2]=0.92;
		break;
    case '2':
		eye[2]=2;
		break;
    case '3':
		eye[2]=3;
		break;
    case '4':
		eye[2]=4;
		break;
    case '5':
		eye[2]=5;
		break;break;
    case '6':
		eye[2]=6;
		break;break;
    case '7':
		eye[2]=7;
		break;break;
    case '8':
		eye[2]=8;
		break;break;
    case '9':
		eye[2]=9;
		break;break;
    case '0':
		eye[2]=11;
		break;
	}

	//updateView(wHeight, wWidth);
}

void redraw()
{

   glClearColor (1.0, 0.9, 1.0, 1.0);//设置清除颜色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除颜色缓存和深度缓存
	glLoadIdentity(); //初始化矩阵为单位矩阵
    // 场景（0，0，0）的视点中心 (0,5,50)，Y轴向上
	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);//保证茶壶正放

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//设置多边形绘制模式：正反面，线型
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//设置多边形绘制模式：正反面，填充
	}

	glEnable(GL_DEPTH_TEST);//开启深度测试
	glEnable(GL_LIGHTING);  //开启光照模式

	//GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_pos[] = {5.0f + light_x ,5.0f + light_y,5.0f + light_z,1}; //定义环境光位置
	GLfloat light_pos1[] = { 0.0f, 0.3f, 0.0f, 1.0f }; //定义聚光灯位置
	GLfloat lightDir[] = { 0.0f + dir_x ,-1.0f + dir_y ,0.0f + dir_z }; //角度
	GLfloat white[] = { 1.0f, 0.5, 0.31f, 1.0f }; //定义黄铜

	if (isWhite) {
		color[0] = 0.0f, color[1] = 0.0f, color[2] = 0.0f, color[3] = 1.0f;
	}
	else {
		color[0] = 1.0f, color[1] = 0.0f, color[2] = 0.0f, color[3] = 1.0f;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); //设置第0号光源的光照位置
	glLightfv(GL_LIGHT0, GL_SPECULAR, white); //设置镜面反射光照颜色
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);  //设置漫射光成分
	glLightfv(GL_LIGHT0, GL_AMBIENT, color);   //设置第0号光源多次反射后的光照颜色（环境光颜色）

	glEnable(GL_LIGHT0); //开启第0号光源

	glLightfv(GL_LIGHT1, GL_AMBIENT, color);//设置环境光成分
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);//设置镜面光成分
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);//设置漫射光成分

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotangle); //裁减角度
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);//光源方向
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.);//聚集度

	glEnable(GL_LIGHT1);

	glRotatef(fRotate, 0, 1.0f, 0);	//旋转
	glRotatef(-90, 1, 0, 0); //旋转
	glScalef(0.2, 0.2, 0.2);  //缩放
	display();	//绘制场景

	if (bAnim) fRotate+= 0.5f; //旋转因子改变

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-4, 7,7, 0, 0, 0, 0, 0, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 3.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 3.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(3.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();
	glutSwapBuffers(); //交换缓冲区
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Matryoshka doll");
    glutKeyboardFunc(key); //注册按键回调函数
    glutIdleFunc(idle);
    init();
    glutDisplayFunc(display);
    glutDisplayFunc(redraw); //注册绘制回调函数
    glutReshapeFunc(reshape);//注册重绘回调函数
    glutMainLoop();
    return 0;
}
