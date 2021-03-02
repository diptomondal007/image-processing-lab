#include <glew.h>
#include <glfw3.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float xmin=-100;
float ymin=-100;
float xmax=100;
float ymax=100;
float xd1,yd1,xd2,yd2;

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);

    glBegin(GL_POINTS);
    glVertex2i(xmin,ymin);
    glVertex2i(xmin,ymax);
    glVertex2i(xmax,ymax);
    glVertex2i(xmax,ymin);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2i(xd1,yd1);
    glVertex2i(xd2,yd2);
    glEnd();
    glFlush();
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
            exit(0);
        }

        float xi=x1;float yi=y1;
        int c=c1;
        if(c==0)
        {
            c=c2;
            xi=x2;
            yi=y2;
        }
        float x,y;
        if((c & 8)>0)
        {
            y=ymax;
            x=xi+ 1.0/m*(ymax-yi);
        }
        else
        if((c & 4)>0)
        {
            y=ymin;
            x=xi+1.0/m*(ymin-yi);
        }
        else
        if((c & 2)>0)
        {
            x=xmax;
            y=yi+m*(xmax-xi);
        }
        else
        if((c & 1)>0)
        {
            x=xmin;
            y=yi+m*(xmin-xi);
        }

        if(c==c1)
        {
            xd1=x;
            yd1=y;
            c1=code(xd1,yd1);
        }

        if(c==c2)
        {
            xd2=x;
            yd2=y;
            c2=code(xd2,yd2);
        }
    }

    display();

}

int main() {
    printf("Enter line co-ordinates:");
    std::cin>>xd1>>yd1>>xd2>>yd2;

    GLFWwindow *window;

    // Initialize the library
    if ( !glfwInit( ) )
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Bresenham's Line Drawing Algo", NULL, NULL );

    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glViewport( 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment

    GLfloat pointVertex[] = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

    // Loop until the user closes the window
    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear( GL_COLOR_BUFFER_BIT );

        cohen_Line(xd1,yd1,xd2,yd2);

        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );
    }

    glfwTerminate( );

    return 0;
}
