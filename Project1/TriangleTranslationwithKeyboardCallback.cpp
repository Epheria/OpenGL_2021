#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

const char* vsSource = "#version 120 \n\
attribute vec4 aPosition; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
uniform float udist_x; \n\
uniform float udist_y; \n\
void main(void) { \n\
 gl_Position.x = aPosition.x + udist_x; \n\
 gl_Position.y = aPosition.y + udist_y; \n\
 gl_Position.zw = aPosition.zw; \n\
 vColor = aColor; \n\
}";
const char* fsSource = "#version 120 \n\
varying vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

void myidle_up(void);
void myidle_down(void);
void myidle_left(void);
void myidle_right(void);
void myidle_init(void);

enum KEYBOARD_INPUT
{
	UP_KEYBOARD_INPUT = 'w',
	DOWN_KEYBOARD_INPUT = 's',
	LEFT_KEYBOAR_INPUT = 'a',
	RIGHT_KEYBOARD_INPUT = 'd',
	INIT_KEYBOARD_INPUT = 'i'
};

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

char buf[1024];
float dist_x = 0.0f;
float dist_y = 0.0f;

void myinit(void) {
	GLint status;
	printf("***** 2015113775 ¼Õ¼¼Çù *****\n");
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
	switch (key)
	{
	case UP_KEYBOARD_INPUT:
		glutIdleFunc(myidle_up);
		break;
	case DOWN_KEYBOARD_INPUT:
		glutIdleFunc(myidle_down);
		break;
	case LEFT_KEYBOAR_INPUT:
		glutIdleFunc(myidle_left);
		break;
	case RIGHT_KEYBOARD_INPUT:
		glutIdleFunc(myidle_right);
		break;
	case INIT_KEYBOARD_INPUT:
		glutIdleFunc(myidle_init);
		break;
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

GLfloat vertices[] = {
0.0, 0.0, 0.0, 1.0,
0.3, 0.0, 0.0, 1.0,
0.0, 0.3, 0.0, 1.0,
};
GLfloat colors[] = {
1.0, 0.0, 0.0, 1.0, // red
0.0, 1.0, 0.0, 1.0, // green
0.0, 0.0, 1.0, 1.0, // blue
};

void myidle_up(void)
{
	dist_y += 0.002f;
	if (dist_y > 1.5)
		dist_y = 0;
	glutPostRedisplay();
}

void myidle_down(void)
{
	dist_y -= 0.002f;
	if (dist_y > 1.5)
		dist_y = 0;
	glutPostRedisplay();
}

void myidle_left(void)
{
	dist_x -= 0.002f;
	if (dist_x > 1.5)
		dist_x = 0;
	glutPostRedisplay();
}

void myidle_right(void)
{
	dist_x += 0.002f;
	if (dist_x > 1.5)
		dist_x = 0;
	glutPostRedisplay();
}

void myidle_init(void)
{
	dist_x = 0;
	dist_y = 0;
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

	loc = glGetUniformLocation(prog, "udist_x");
	glUniform1f(loc, dist_x);

	loc = glGetUniformLocation(prog, "udist_y");
	glUniform1f(loc, dist_y);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFlush();
	glutSwapBuffers();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("*** 2015113775 ¼Õ¼¼Çù ***");
	glutDisplayFunc(mydisplay);

	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}