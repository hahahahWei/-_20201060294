#include<windows.h>
#include<stdlib.h>
#include<math.h>
#include<gl/glut.h>
#include<stdio.h>
//P106

//好像是画点函数
void setPixel(int x,int y){

	glPointSize(6.0f);//栅格化点的直径。 默认值为 1.0，此处改为5.0

	glBegin(GL_POINTS);//GL_POINTS表示单个顶点集
		glVertex2i(x,y);//设置顶点坐标
	glEnd();

	glFlush();//强制刷新缓冲，保证绘图命令将被执行，而不是存储在缓冲区中等待其他的OpenGL命令。
}


//当斜率为（0，1.0）,改进的算法
void lineUpperBres(int x0,int y0,int xEnd, int yEnd)
{
    //计算初始值
    int dx=fabs(xEnd-x0),dy=fabs(yEnd-y0);
    int k=dy/dx;
    int d=0;
    int x,y;

    //确定线段的开始位置(x,y)
    if(x0>xEnd)
    {
        x=xEnd;
        y=yEnd;
        xEnd=x0;
    }else{
        x=x0;
        y=y0;
    }

    setPixel(x,y);

    //直线没有画完时
    while(x<xEnd)
    {
        x++;//x的值每次都加1
        d+=k;
        if(d>0.5){
            y++;
            d-=1;
        }
        setPixel(x,y);
    }
}

void myDisplay(void){

	lineUpperBres(5,5,300,300);
}

//窗口大小改变时调用的登记函数
void ChangeSize(GLsizei w, GLsizei h){//GLsizei表示int
    if(h==0)
		h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);//声明接下来要做GL_PROJECTION（把物体投影到一个平面上（三维->二维））
    glLoadIdentity();//将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
    if (w <= h)
        glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0,-1.0);
    else
        glOrtho(0.0f,250.0f*w/h,0.0f,250.0f,1.0,-1.0);
}

int main(int argc,char* argv[]){


    system("color F5");//设置颜色白底紫字

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(500,200);//显示窗口左上角在屏幕左边界向右500个像素，上边界向下200像素
	glutInitWindowSize(500,550);//指定一个宽度为400像素，高度为500像素的显示窗口
	glutCreateWindow("UpperBresenHam");//显示窗口在创建时给定一个标题
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//设置显示窗口的颜色
	glColor3f(0.0,0.0,0.0);//设置直线颜色
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}

