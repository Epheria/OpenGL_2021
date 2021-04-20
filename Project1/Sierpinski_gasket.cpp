#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
void main(void) {\n\
 gl_Position = vertex; \n\
}";

const static char* fsSource = "#version 120 \n\
void main(void) { \n\
 gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0); \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

void myinit(void)
{
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);

	prog = glCreateProgram();

	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glUseProgram(prog);
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESCAPE
		exit(0);
		break;
	}
}

void mydisplay(void) {
	GLuint loc;
	typedef GLfloat point2[2];
	point2 vertices[3] = { {-0.5, -0.5},{-0.5, 0.5}, {0.5, -0.5} };
	point2 p = { 0.5, 0.5 };
	int j, k;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (k = 0; k < 5000; k++)
	{
		j = rand() % 3;

		p[0] = (p[0] + vertices[j][0]) / 2.0;
		p[1] = (p[1] + vertices[j][1]) / 2.0;

		glBegin(GL_POINTS);
		glVertex2fv(p);
		glEnd();
	}
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2015113775 ¼Õ¼¼Çù");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);

	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}