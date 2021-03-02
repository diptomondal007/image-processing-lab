#include <glew.h>
#include <glfw3.h>
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int pntX1, pntY1, r;

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void midPointCircleAlgo()
{
    int x = 0;
    int y = r;
    float decision = 5/4 - r;
    draw_pixel(x, y);

    while (y > x)
    {
        if (decision < 0)
        {
            x++;
            decision += 2*x+1;
        }
        else
        {
            y--;
            x++;
            decision += 2*(x-y)+1;
        }
        draw_pixel(x, y);
        draw_pixel(x, -y);
        draw_pixel(-x, y);
        draw_pixel(-x, -y);
        draw_pixel(y, x);
        draw_pixel(-y, x);
        draw_pixel(y, -x);
        draw_pixel(-y, -x);
    }

}


int main()
{
    GLFWwindow *window;

    std::cout << "Enter the coordinates of the center:\n\n" << std::endl;

    std::cout << "X-coordinate   : "; std::cin >> pntX1;
    std::cout << "\nY-coordinate : "; std::cin >> pntY1;
    std::cout << "\nEnter radius : "; std::cin >> r;

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

        midPointCircleAlgo();

        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );
    }

    glfwTerminate( );

    return 0;
}
