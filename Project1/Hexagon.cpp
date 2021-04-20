#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const static char* vsSource = "#version 120 \n\
attribute vec4 vertex; \n\
attribute vec4 acolor; \n\
varying vec4 fcolor; \n\
void main(void) {\n\
    gl_Position = vertex; \n\
    fcolor = acolor; \n\
}";

const static char* fsSource = "#version 120 \n\
varying vec4 fcolor; \n\
void main(void) { \n\
   gl_FragColor = fcolor; \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

char buf[1024];

void myinit(void)
{
	GLint status;
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("2015113775 ¼Õ¼¼Çù\n");
	printf("vs compile status = %s\n", (status == GLU_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GLU_TRUE) ? "true" : "false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GLU_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GLU_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog);
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = {
	0.0, 0.6, 0.0, 1.0,
	-0.5, 0.25, 0.0, 1.0,
	-0.5, -0.25, 0.0, 1.0,
	0.0, -0.6, 0.0, 1.0,
	0.5, -0.25, 0.0, 1.0,
	0.5, 0.25, 0.0, 1.0,
};
GLfloat colors[] = {
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	0.0, 1.0, 1.0, 1.0,
	1.0, 0.0, 1.0, 1.0,
};

void mydisplay(void) {
	GLuint loc;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	loc = glGetAttribLocation(prog, "vertex");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);

	loc = glGetAttribLocation(prog, "acolor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, colors);

	glDrawArrays(GL_POLYGON, 0, 6);
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