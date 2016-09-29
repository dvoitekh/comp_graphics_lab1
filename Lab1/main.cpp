//
//  main.cpp
//  Lab1
//
//  Created by Dmitry Voitekh on 9/22/16.
//  Copyright © 2016 Dmitry Voitekh. All rights reserved.
//
#include <GLUT/glut.h>
#include <cmath>

//displacement
int xr,yr;
//step
int h=20;
//window size
int Width,Height;

float base = 150;

void init(void)
{
    glClearColor(0.95, 0.6, 0.17, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

//рисуем
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);
    glTranslatef(xr,yr,0);//move figure

    //shape
    glNewList(1, GL_COMPILE);
        glBegin(GL_TRIANGLES);
            glVertex2d(base, base);
            glVertex2d(base, 2*base);
            glVertex2d(2*base, 2*base);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2d(base+sqrt(2*base*base), base);
            glVertex2d(base+sqrt(2*base*base), base+sqrt(2*base*base));
            glVertex2d(base+sqrt(2*base*base)/2, base+sqrt(2*base*base)/2);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2d(base, 2*base);
            glVertex2d(2*base, 2*base);
            glVertex2d(3*base/2, 5*base/2);
        glEnd();
        glBegin(GL_QUADS);
            glVertex2f(2*base, 2*base);
            glVertex2f(base+sqrt(2*base*base), base+sqrt(2*base*base));
            glVertex2f(2*base, 2*sqrt(2*base*base));
            glVertex2f(3*base-sqrt(2*base*base), base+sqrt(2*base*base));
        glEnd();
        glBegin(GL_QUADS);
            glVertex2f(base+sqrt(2*base*base), base+sqrt(2*base*base)/2);
            glVertex2f(base+sqrt(2*base*base), base+sqrt(2*base*base));
            glVertex2f(2*sqrt(2*base*base), 2*sqrt(2*base*base));
            glVertex2f(2*sqrt(2*base*base), 3*sqrt(2*base*base)/2);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(base+sqrt(2*base*base), base+sqrt(2*base*base));
            glVertex2f(2*sqrt(2*base*base), 2*sqrt(2*base*base));
            glVertex2d(base+sqrt(2*base*base), 3*sqrt(2*base*base)-base);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(2*sqrt(2*base*base), 2*sqrt(2*base*base));
            glVertex2d(base+sqrt(2*base*base), 3*sqrt(2*base*base)-base);
            glVertex2d(3*sqrt(2*base*base)-base, 3*sqrt(2*base*base)-base);
        glEnd();
    glEndList();
    
    //draw filled shape
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(12,121,48);
    glCallList(1);
    
    //draw borders
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3ub(0,0,0);
    glCallList(1);
    
    xr=yr=0;//ensure figure is not moving
    glutSwapBuffers();
}

//delay
void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(30,TimerFunction,1);
}

//keybord callbacks
void Keyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP: yr=0.5*h; xr=h;
            break;
        case GLUT_KEY_DOWN: yr=-0.5*h; xr=-h;
            break;
    }
}

//resize window
void Reshape(GLint w, GLint h)
{
    //detect current size
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);//viewing area size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);//coordinates system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//main loop
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize( 700, 700 );
    glutCreateWindow("Lab1");
    glutDisplayFunc(draw);
    glutTimerFunc(30,TimerFunction,1);
    init();
    glutSpecialFunc(Keyboard);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}
