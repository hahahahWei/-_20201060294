#include<windows.h>
#include<math.h>
#include<gl/glut.h>

void myDisplay(void);//该函数调用lineDDA以显示图像
void setPixel(int x,int y);//画点的函数，只能显示整数像素值
int round1(const float a);//（a+0.5）取整
void ChangeSize(GLsizei w, GLsizei h);
void lineDDA(int x0,int y0,int xEnd,int yEnd);

void myDisplay(void){
	lineDDA(50,50,200,200);
}

void setPixel(int x,int y){

	glPointSize(6.0f);//栅格化点的直径。 默认值为 1.0，此处改为5.0

	glBegin(GL_POINTS);//GL_POINTS表示单个顶点集
		glVertex2i(x,y);//设置顶点坐标
	glEnd();

	glFlush();//强制刷新缓冲，保证绘图命令将被执行，而不是存储在缓冲区中等待其他的OpenGL命令。
}

int round1(const float a){
	return int(a+0.5);
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

void lineDDA(int x0,int y0,int xEnd,int yEnd){
	glPointSize(5.0f);//设置像素点大小
	int dx=xEnd-x0,dy=yEnd-y0,steps,k;
	float xIncrement,yIncrement,x=x0,y=y0;
	if(abs(dx)>abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
	xIncrement=float(dx)/float(steps);//增量当中有一个会为1，另一个会为斜率k
	yIncrement=float(dy)/float(steps);
	setPixel(round(x),round(y));//由于每次都加了小于1的增量，所以需要取整
	for(k=0;k<steps;k++){
		/*
		glBegin(GL_POINTS);
		glVertex2i((int)x,(int)y);
		glEnd();
		glFlush();
		*/
		x+=xIncrement;
		y+=yIncrement;
		setPixel(round(x),round(y));
	}
}

int main(int argc,char* argv[]){

system("color F5");//设置颜色白底紫字
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(500,200);//显示窗口左上角在屏幕左边界向右500个像素，上边界向下200像素
	glutInitWindowSize(400,450);//指定一个宽度为400像素，高度为500像素的显示窗口
	glutCreateWindow("DDA");//显示窗口在创建时给定一个标题
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);//设置显示窗口的颜色
	glColor3f(0.0,0.0,0.0);//设置直线颜色
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}
