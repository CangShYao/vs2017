#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "glut.h"
using namespace std;

#define PI 3.1415926535

GLfloat mat[4] = { 0.5, 0.5, 0.9, 0 };
//光源位置
GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
vector<vector<double>> vArr;
vector<vector<double>> fArr;
static int count_number = 0;
static float c =  PI / 180.0f;
static int du = 90, oldmy = -1, oldmx = -1;
static float r = 1.5f, h = 0.0f;

void init(void)
{
	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	
	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat local_view[] = { 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glFrontFace(GL_CW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}


void displayTeapot(void)
{
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// 	glPushMatrix();
// 	glTranslatef(8, 8, 0.0);
// 	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
// 	glutSolidTeapot(3.0);
// 	glPopMatrix();
// 	glFlush();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除缓冲，GL_COLOR_BUFFER_BIT ：颜色缓冲标志位
	glLoadIdentity();                                       //重置当前矩阵为4*4的单位矩阵
	glTranslatef(8, 8, 0.0);
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //从视点看远点
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glutWireTeapot(3.0f);
	glutSwapBuffers();
	glFlush();
}

void readFile(string fileName)
{
	int i = 0;// number of v
	int j = 0;// number of f
	char buffer[100];
	ifstream rfile;
	rfile.open(fileName);
	if (!rfile.is_open())
	{
		cout << "open file failed!" << endl;
		exit(1);
	}
	while (!rfile.eof())
	{
		rfile.getline(buffer, 100);
		string ch;
		double a, b, c;
		istringstream fin(buffer);
		fin >> ch >> a >> b >> c;
		if (ch == "v")
		{
			vector<double> temp;
			vArr.push_back(temp);
			vArr[i].push_back(a);
			vArr[i].push_back(b);
			vArr[i].push_back(c);
			i++;
		}
		if (ch == "f")
		{
			vector<double> temp;
			fArr.push_back(temp);
			fArr[j].push_back(a);
			fArr[j].push_back(b);
			fArr[j].push_back(c);
			j++;
		}
	}
	rfile.close();
}

void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	//glPushMatrix();
	glLoadIdentity();
	glTranslatef(8, 8, 0.0);
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	for (int i = 0; i < fArr.size(); i++)
	{
		int a = fArr[i][0];
		int b = fArr[i][1];
		int c = fArr[i][2];
		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0], vArr[a - 1][1], vArr[a - 1][2]);
		glVertex3d(vArr[b - 1][0], vArr[b - 1][1], vArr[b - 1][2]);
// 		glEnd();
// 		glBegin(GL_LINES);
		glVertex3d(vArr[b - 1][0], vArr[b - 1][1], vArr[b - 1][2]);
		glVertex3d(vArr[c - 1][0], vArr[c - 1][1], vArr[c - 1][2]);
// 		glEnd();
// 		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0], vArr[a - 1][1], vArr[a - 1][2]);
		glVertex3d(vArr[c - 1][0], vArr[c - 1][1], vArr[c - 1][2]);
		glEnd();
	}
	//glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	glClearColor(1.0f, 1.0f, 1.0f, 0);
	glLoadIdentity();
	glTranslatef(8, 8, 0.0);
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	for (int i = 0; i < fArr.size(); i++)
	{
		int a = fArr[i][0];
		int b = fArr[i][1];
		int c = fArr[i][2];
		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0] * 15, vArr[a - 1][1] * 15, vArr[a - 1][2] * 15);
		glVertex3d(vArr[b - 1][0] * 15, vArr[b - 1][1] * 15, vArr[b - 1][2] * 15);
		// 		glEnd();
		// 		glBegin(GL_LINES);
		glVertex3d(vArr[b - 1][0] * 15, vArr[b - 1][1] * 15, vArr[b - 1][2] * 15);
		glVertex3d(vArr[c - 1][0] * 15, vArr[c - 1][1] * 15, vArr[c - 1][2] * 15);
		// 		glEnd();
		// 		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0] * 15, vArr[a - 1][1] * 15, vArr[a - 1][2] * 15);
		glVertex3d(vArr[c - 1][0] * 15, vArr[c - 1][1] * 15, vArr[c - 1][2] * 15);
		glEnd();
	}
	//glPopMatrix();
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(0.0, 16.0, 0.0, 16.0*(GLfloat)h / (GLfloat)w,
			-10.0, 10.0);
	else
		glOrtho(0.0, 16.0*(GLfloat)w / (GLfloat)h, 0.0, 16.0,
			-10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void Mouse(int button, int state, int x, int y) //处理鼠标点击
{
	if (state == GLUT_DOWN) //第一次鼠标按下时,记录鼠标在窗口中的初始坐标
		oldmx = x, oldmy = y;
}

void onMouseMove(int x, int y) //处理鼠标拖动
{
	du += x - oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
	h += 0.03f*(y - oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
	if (h > 1.0f) h = 1.0f; //视点y坐标作一些限制，不会使视点太奇怪
	else if (h < -1.0f) h = -1.0f;
	oldmx = x, oldmy = y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
		{
			exit(0);
			break;
		}
		// up
		case 'w':
		{
			position[1] += 0.5;
			init();
			display();
			break;
		}
		// down
		case 's':
		{
			position[1] -= 0.5;
			init();
			display();
			break;
		}
		// left
		case 'a':
		{
			position[0] -= 0.5;
			init();
			display();
			break;
		}
		// right
		case 'd':
		{
			position[0] += 0.5;
			init();
			display();
			break;
		}
		case 'b':
		{
			position[0] = 1.0;
			position[1] = 1.0;
			init();
			display();
			break;
		}
		case 99:
		{

			if (count_number % 3 == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					mat[0] -= 0.5 / 10;
					mat[1] += 0.5 / 10;
					mat[2] -= 0.5 / 10;
					display();
					Sleep(150);
				}
// 				mat[0] = 0;
// 				mat[1] = 1;
// 				mat[2] = 0.4;
// 				display();
				cout << "green" << endl;
				count_number++;
				break;
			}
			if (count_number % 3 == 1)
			{
				for (int i = 0; i < 10; i++)
				{
					mat[0] += 1 / 10;
					mat[1] += 0 / 10;
					mat[2] += 0.6 / 10;
					display();
					Sleep(150);
				}
// 				mat[0] = 1;
// 				mat[1] = 1.0;
// 				mat[2] = 1;
// 				display();
				count_number++;
				cout << "white" << endl;
				break;
			}
			if (count_number % 3 == 2)
			{
				for (int i = 0; i < 10; i++)
				{
					mat[0] -= 0.5 / 10;
					mat[1] -= 0.5 / 10;
					mat[2] -= 0.1 / 10;
					display();
					Sleep(150);
				}
// 				mat[0] = 0.5;
// 				mat[1] = 0.5;
// 				mat[2] = 0.9;
// 				display();
				count_number++;
				cout << "origin color" << endl;
				break;
			}
		}
		default:
		{
			cout << "Unhandled key press " << key << endl;
			break;
		}
	}
}

/*
* Main Loop
*/
int main(int argc, char **argv)
{
	string fname = "cube.obj";
	string fname1 = "bunny_200.obj";
	string fname2 = "bunny_1k.obj";
	readFile(fname2);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("hello world");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(onMouseMove);
	glutMainLoop();
	return 0;
}