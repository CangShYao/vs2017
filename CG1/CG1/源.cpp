#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "glut.h"
using namespace std;

GLfloat mat[4] = { 0.5, 0.5, 0.9, 0 };
//光源位置
GLfloat position[] = { 1.0, 1.0, 5.0, 0.0 };
vector<vector<double>> vArr;
vector<vector<double>> fArr;
static int count_number = 0;

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


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(8, 8, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glutSolidTeapot(3.0);
	glPopMatrix();
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
	//glPushMatrix();
	glTranslatef(8, 8, 0.0);
	for (int i = 0; i < fArr.size(); i++)
	{
		int a = fArr[i][0];
		int b = fArr[i][1];
		int c = fArr[i][2];
		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0], vArr[a - 1][1], vArr[a - 1][2]);
		glVertex3d(vArr[b - 1][0], vArr[b - 1][1], vArr[b - 1][2]);
		glVertex3d(vArr[c - 1][0], vArr[c - 1][1], vArr[c - 1][2]);
		glEnd();
	}
	//glPopMatrix();
	glFlush();
}

void displayBunny(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	glTranslatef(8, 8, 0.0);
	for (int i = 0; i < fArr.size(); i++)
	{
		int a = fArr[i][0];
		int b = fArr[i][1];
		int c = fArr[i][2];
		glBegin(GL_LINES);
		glVertex3d(vArr[a - 1][0] * 10, vArr[a - 1][1] * 10, vArr[a - 1][2] * 10);
		glVertex3d(vArr[b - 1][0] * 10, vArr[b - 1][1] * 10, vArr[b - 1][2] * 10);
		glVertex3d(vArr[c - 1][0] * 10, vArr[c - 1][1] * 10, vArr[c - 1][2] * 10);
		glEnd();
	}
	//glPopMatrix();
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
	readFile(fname);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("hello world");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}