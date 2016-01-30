// header files
#include <GL/glut.h>

// function prototypes
void display(void);
void reshape(int width, int height);
void init();


main(int argc, char **argv)
{

  // initialize glut 
  glutInit(&argc, argv);

  // set window size
  glutInitWindowSize(600,400);

  // establish glut display parameters
  glutInitDisplayMode(GLUT_SINGLE   | GLUT_RGB );

  // create window
  glutCreateWindow("My First OpenGL program");

  // register callback functions
  glutDisplayFunc(display);
  glutReshapeFunc(reshape); 

  // initalize opengl parameters
  init();

  // loop until something happens
  glutMainLoop();
  return 0;           
}

void init()
{

  // initialize viewing system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, 1.0, 1.0, 100.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // initialize background color to black
  glClearColor(0,0,0,0);

}


void reshape(int width, int height)
{
  glViewport(0,0,width,height);
}

void display()
{
// clear buffer
	glClear(GL_COLOR_BUFFER_BIT );
	
// draw a red triangle
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-3,-1,-8);
		glVertex3f(3,-1,-10);
		glVertex3f(0,3,-9);
	glEnd();

// flush buffer
	glFlush();

	
}

