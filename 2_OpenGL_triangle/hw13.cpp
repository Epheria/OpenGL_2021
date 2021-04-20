#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const static char* vsSource = "#version 120 \n\
attribute vec4 aPosition; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
uniform mat4 utranslate; \n\
void main(void) { \n\
 gl_Position = utranslate*aPosition; \n\
 vColor = aColor; \n\
}";

const static char* fsSource = "#version 120 \n\
varying vec4 vColor; \n\
void main(void) { \n\
 gl_FragColor = vColor; \n\
}";

GLuint vs = 0;
GLuint fs = 0;
GLuint prog = 0;

char buf[1024];
float t = 0.0f;

GLfloat vertices[] = {
-0.1, -0.1, -0.1, 1.0, // 0
-0.1, -0.1, +0.1, 1.0, // 1
+0.1, -0.1, -0.1, 1.0, // 2
+0.1, -0.1, +0.1, 1.0, // 3
0.0, +0.1, 0.0, 1.0  // 4
};

GLfloat colors[] = {
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
0.0, 0.0, 1.0,
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
};

GLushort indices[] = {
0, 4, 2,
0, 4, 1,
1, 4, 3,
2, 4, 3,
0, 1, 2,
1, 2, 3
};

void myinit(void) {
	GLint status;
	printf("***** 2015113775 ¼Õ¼¼Çù *****\n");
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");

	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");

	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" : "false");

	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("link log = [%s]\n", buf);
	glValidateProgram(prog);
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);
	printf("program validate status = %s\n", (status == GL_TRUE) ? "true" : "false");

	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);
	glUseProgram(prog);

	GLuint loc;
	GLuint vbo[1];
	// using vertex buffer object

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 5 * 4 * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 5 * 4 * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(GLfloat), 5 * 4 * sizeof(GLfloat),colors);

	loc = glGetAttribLocation(prog, "aPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
	loc = glGetAttribLocation(prog, "aColor");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(5 * 4 *sizeof(GLfloat)));
}

void mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESCAPE
		exit(0);
		break;
	}
}

void myidle(void) {
	t += 0.005f;
	if (t > 1)
		t = -1.0f;
	// redisplay 
	glutPostRedisplay();
}

GLfloat d[4] = { 1.0, 1.0, 0.0, 0.0 };
GLfloat m[16];

void mydisplay(void) {
	GLuint loc;
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f); // gray
	glClear(GL_COLOR_BUFFER_BIT);
	m[0] = 1.0; m[4] = 0.0; m[8] = 0.0; m[12] = t*d[0];
	m[1] = 0.0; m[5] = 1.0; m[9] = 0.0; m[13] = (sin(5.0*t)/2.0)*d[1];
	m[2] = 0.0; m[6] = 0.0; m[10] = 1.0; m[14] = d[2];
	m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
	loc = glGetUniformLocation(prog, "utranslate");
	glUniformMatrix4fv(loc, 1, GL_FALSE, m);
	glDrawElements(GL_TRIANGLES, 6 * 3, GL_UNSIGNED_SHORT, indices);
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
	glutIdleFunc(myidle);
	glutKeyboardFunc(mykeyboard);
	glewInit();
	myinit();
	glutMainLoop();
	return 0;
}