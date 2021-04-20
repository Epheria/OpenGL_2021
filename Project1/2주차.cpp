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
 gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n\
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

	prog = glCreateProgram(); // program object 생성

	// vs -> vertex processor 실행파일을 만들고
	// fs -> fragment processor 실행파일을 만듦
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

//vertex 추가가능 단, glDrawArrays 에서 3을 추가한 개수만큼 늘려주기
GLfloat vertices[] = { -0.5, -0.5, 0.0, 1.0,
					   +0.5, -0.5, 0.0, 1.0,
					   -0.0, +0.5, 0.0, 1.0 };

void mydisplay(void) {
	GLuint loc;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	loc = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("2015113775 손세협");
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}