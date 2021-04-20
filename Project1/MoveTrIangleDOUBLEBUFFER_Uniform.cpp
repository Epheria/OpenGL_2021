#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const char* vsSource = "#version 120 \n\
attribute vec4 aPosition; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
uniform float udist; \n\
void main(void) { \n\
 gl_Position.x = aPosition.x + udist; \n\
 gl_Position.yzw = aPosition.yzw; \n\
 vColor = aColor; \n\
}";
const char* fsSource = "#version 120 \n\
varying vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

enum KEYBOARD_INPUT
{
	KEYBOARD_INPUT_START = 0,
	UP_KEYBOARD_INPUT,
	DOWN_KEYBOARD_INPUT,
	LEFT_KEYBOAR_INPUT,
	RIGHT_KEYBOARD_INPUT,
	INIT_KEYBOARD_INPUT = 'i'
};

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

char buf[1024];
float dist = 0.0f;

void myinit(void) {
	GLint status;
	printf("***** Your student number and name *****\n");
	// vs: vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs); // compile to get .OBJ
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);
	// fs: fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs); // compile to get .OBJ
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);
	// prog: program
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog); // link to get .EXE
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" :
		"false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog); // execute it !
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = {
-0.5, -0.5, 0.0, 1.0,
+0.5, -0.5, 0.0, 1.0,
-0.5, +0.5, 0.0, 1.0,
};
GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
};

void myidle(void)
{
	//float step = 0.0001F;

	//for (int i = 0; i < 12; i+=4)
	//{
	//	vertices[i] += step;
	//}

	dist += 0.001f;
	if (dist > 1.5)
		dist = 0;

	// redisplay
	glutPostRedisplay();
}

void mydisplay(void) {
	GLuint loc;

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT);
	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertices);
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, colors);

	loc = glGetUniformLocation(prog, "udist");
	glUniform1f(loc, dist);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	// 더블버퍼 스왑하기
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	// DOUBLE BUFFER 설정
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("*** Your Student number and name ***");
	glutDisplayFunc(mydisplay);
	glutIdleFunc(myidle);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}