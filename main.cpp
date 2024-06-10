// functionalites of the program
// 1.) With left click you can change the baloons color randomly
// 2.) By pressing letter E you can enlarge objects
// 3.) By pressing letter S you can shrink objects
// 4.) By pressing letter C you can open&close curtains and open program manual
// 5.) With right click you can change the location of the air baloon
// 6.) Press ESC to quit the program
// 7. )press space bar to stop moving animation

 /*****************************************************************************************************/
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 400
#define TIMER_PERIOD   20   // Period for the timer
#define TIMER_ON        1   // 0:Disable timer, 1:Enable timer

#define D2R 0.0174532
#define PI 3.1415

 // Shapes
#define BALLOON   2

// Global variables for Template File
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // Current Window width and height

// Global variables
int flag;
bool activeTimer = true;
int mode = BALLOON; // Initial shape is BALLOON
int r = 180, g = 172, b = 50; // Initial color


// BALLOON
int xB = -190, yB = -55; // BALLOON's initial position
double xS = -100, yS = 100; //sun^s initial position
int radiusB = 60; // BALLOON's initial radius

// To draw a filled circle, centered at (x,y) with radius r
void circle(int x, int y, int r) {
    float angle;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        angle = 2 * PI*i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

// To draw a hollow circle, centered at (x,y) with radius r
void circle_wire(int x, int y, int r) {
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        angle = 2 * PI*i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char *string, void *font) {
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);
}

// To display text with variables
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, str[i]);
}

void vprint2(int x, int y, float size, const char *string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    glPopMatrix();
}


void drawBalloon() {
    // Part 1 : String/ropes
    glLineWidth(3);
    glColor3ub(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(xB + 15, yB - radiusB + 5);
    glVertex2f(xB, yB - radiusB - radiusB * 0.8);
    glEnd();
    glLineWidth(1);


    glLineWidth(3);
    glColor3ub(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(xB - 15, yB - radiusB + 5);
    glVertex2f(xB, yB - radiusB - radiusB * 0.8);
    glEnd();
    glLineWidth(1);

    glLineWidth(3);
    glColor3ub(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(xB, yB - radiusB + 1);
    glVertex2f(xB, yB - radiusB - radiusB * 0.8);
    glEnd();
    glLineWidth(1);

    //quad platform
    glColor3ub(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(xB - 10, yB - radiusB - 20);
    glVertex2f(xB + 10, yB - radiusB - 20);
    glVertex2f(xB + 45, yB - radiusB - 60);
    glVertex2f(xB - 45, yB - radiusB - 60);



    glEnd();

    //plaka
    glColor3f(0.0, 0.0, 0.0);
    vprint(xB - 35, yB - radiusB - 58, GLUT_BITMAP_8_BY_13, "06 ST 164");

    // Part 2 : Body
    glColor3ub(r, g, b);
    circle(xB, yB, radiusB);


    glColor3f(1, 1.0, 1.0);
    vprint(xB - (radiusB / 3) - 15, yB - (radiusB / 3) + 55, GLUT_BITMAP_8_BY_13, "B A B A M");
    vprint(xB - (radiusB / 3) - 16, yB - (radiusB / 3) + 40, GLUT_BITMAP_9_BY_15, "SAGOLSUN");


    //nazar boncugu
    glColor3f(0.0, 0.0, 1.0);
    circle(xB - (radiusB / 3) + 20, yB - (radiusB / 3) + 15, (radiusB / 3));


    glColor3f(1.0, 1.0, 1.0);
    circle(xB - (radiusB / 3) + 20, yB - (radiusB / 3) + 15, (radiusB / 5));

    glColor3f(1.0, 0.7, 0.3);
    circle(xB - (radiusB / 3) + 20, yB - (radiusB / 3) + 15, (radiusB / 8));

    glColor3f(0.0, 0.0, 0.0);
    circle(xB - (radiusB / 3) + 20, yB - (radiusB / 3) + 15, (radiusB / 15));



    //Türk Bayrağı
    glColor3f(1, 0.0, 0.0);
    glRectf(xB - (radiusB / 3), yB - (radiusB / 3) - 30, xB - (radiusB / 3) + 38, yB - (radiusB / 3) - 15);
    glColor3f(1, 1.0, 1.0);
    vprint(xB - (radiusB / 3) + 10, yB - (radiusB / 3) - 28, GLUT_BITMAP_8_BY_13, "C*");


    glColor3f(1.0, 0.8, 0.0);
    circle(xS + 400, yS - 100, (radiusB / 2));



}


// To display onto window using OpenGL commands
void display() {

    glClearColor(0.25, 0.25, 0.25, 0);
    glClear(GL_COLOR_BUFFER_BIT);


    //there are 4 glRectf functions because at first i planned to make 4 colored wall
        //but then i changed my mind to make it 2 colored but i did not want to delete the //functions because i was afraid i would broke something

    glColor3f(0.9, 0.9, 0.8);
    glRectf(-winWidth / 2, -winHeight / 2, 0, 0);

    glColor3f(0.9, 0.9, 0.8);
    glRectf(-winWidth / 2, winHeight / 2, 0, 0);

    glColor3f(0.5, 0.6, 0.5);
    glRectf(winWidth / 2, -winHeight / 2, 0, 0);

    glColor3f(0.5, 0.6, 0.5);
    glRectf(winWidth / 2, winHeight / 2, 0, 0);




    glColor3f(0.5, 0.8, 0.9);
    glRectf(-WINDOW_WIDTH * 0.40, -WINDOW_HEIGHT / 3, 0, WINDOW_HEIGHT / 3);

    glColor3f(0.5, 0.8, 0.9);
    glRectf(WINDOW_WIDTH*0.4, -WINDOW_HEIGHT / 3, 0.0, WINDOW_HEIGHT / 3);


    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2f(0, WINDOW_HEIGHT / 3);
    glVertex2f(-0, -WINDOW_HEIGHT / 3);

    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(25, 0);

    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(23, 0);
    glVertex2f(23, -20);

    glEnd();


    glColor3ub(r, g, b);

    drawBalloon();

    glColor3f(0.9, 0.9, 0.8);
    glRectf(-WINDOW_WIDTH * 0.4, WINDOW_HEIGHT / 3, 0, WINDOW_HEIGHT);

    glColor3f(0.5, 0.6, 0.5);
    glRectf(WINDOW_WIDTH*0.4, WINDOW_HEIGHT / 3, 0, WINDOW_HEIGHT);


    glColor3f(0.5, 0.6, 0.5);
    glRectf(WINDOW_WIDTH*0.4, -WINDOW_HEIGHT, 0, -WINDOW_HEIGHT / 3);

    glColor3f(0.9, 0.9, 0.8);
    glRectf(-WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT, 0, -WINDOW_HEIGHT / 3);


    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 3);
    glVertex2f(WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8);
    glVertex2f(0, -WINDOW_HEIGHT / 3);

    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(WINDOW_WIDTH*0.4, -WINDOW_HEIGHT / 3);
    glVertex2f(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 96);
    glVertex2f(WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 3);

    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(-WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 3);
    glVertex2f(-WINDOW_WIDTH / 8, WINDOW_HEIGHT / 64);
    glVertex2f(0, -WINDOW_HEIGHT / 3);

    glColor3f(0.8, 0.5, 0.2);
    glBegin(GL_TRIANGLES);
    glVertex2f(-WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT / 3);
    glVertex2f(-WINDOW_WIDTH / 3, WINDOW_HEIGHT / 128);
    glVertex2f(-WINDOW_WIDTH / 4, -WINDOW_HEIGHT / 3);


    glEnd();

    glColor3f(0.7, 0.3, 0.2);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH * 0.4, WINDOW_HEIGHT / 3);
    glVertex2f(-WINDOW_WIDTH * 0.4, -WINDOW_HEIGHT / 3);

    glEnd();

    glColor3f(0.7, 0.3, 0.2);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2f(WINDOW_WIDTH*0.4, WINDOW_HEIGHT / 3);
    glVertex2f(WINDOW_WIDTH*0.4, -WINDOW_HEIGHT / 3);

    glEnd();

    glColor3f(0.7, 0.3, 0.2);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH * 0.4 - 5, WINDOW_HEIGHT / 3);
    glVertex2f(WINDOW_WIDTH*0.4 + 4, WINDOW_HEIGHT / 3);



    glColor3f(0.7, 0.3, 0.2);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2f(-WINDOW_WIDTH * 0.4 - 5, -WINDOW_HEIGHT / 3);
    glVertex2f(WINDOW_WIDTH*0.4 + 4, -WINDOW_HEIGHT / 3);

    glEnd();


    // glColor3f(1.0, 1.0, 0.0);
    // circle(WINDOW_WIDTH/3-70, WINDOW_HEIGHT/8-90, (radiusB / 2));



    glColor3f(0.5, 0.3, 0.7);
    glRectf(-WINDOW_WIDTH / 4, WINDOW_HEIGHT / 6 + 75, WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 95);
    glColor3f(1, 1, 1);

    vprint(-WINDOW_WIDTH / 4 + 140, WINDOW_HEIGHT / 6 + 110, GLUT_BITMAP_8_BY_13, "Hamit Efe ELDEM");

    vprint(-WINDOW_WIDTH / 4 + 100, WINDOW_HEIGHT / 6 + 80, GLUT_BITMAP_8_BY_13, "CEO Of CTIS Cappadocia");

    if (flag == 1) {

        glColor3f(0.7, 0.1, 0.2);
        glRectf(-WINDOW_WIDTH * 0.40, -WINDOW_HEIGHT / 3, 0, WINDOW_HEIGHT / 3);

        glColor3f(0.7, 0.1, 0.2);
        glRectf(WINDOW_WIDTH*0.4, -WINDOW_HEIGHT / 3, 0.0, WINDOW_HEIGHT / 3);


        glColor3f(1, 1, 1);
        vprint(-310, 100, GLUT_BITMAP_8_BY_13, "1.) Press 'c' or 'C' to open the curtains again");
        vprint(-310, 80, GLUT_BITMAP_8_BY_13, "2.) Left click: change the color of the air baloon");
        vprint(-310, 60, GLUT_BITMAP_8_BY_13, "3.) Right click: change the location of the air baloon");
        vprint(-310, 40, GLUT_BITMAP_8_BY_13, "4.) Press 'e' or 'E' to enlarge objects (baloon and sun)");
        vprint(-310, 20, GLUT_BITMAP_8_BY_13, "5.) Press 's' or 'S' to shrink objects (baloon and sun)");
        vprint(-310, 0, GLUT_BITMAP_8_BY_13, "6.) Press [Space Bar] to stop animations");
        vprint(-310, -20, GLUT_BITMAP_8_BY_13, "7.) Press [esc] to quit program");






    }






    glColor3f(0.7, 0.1, 0.2);
    glRectf(-WINDOW_WIDTH / 4 - 120, WINDOW_HEIGHT / 6 - 245, WINDOW_WIDTH / 4 + 120, WINDOW_HEIGHT / 6 - 265);
    glColor3f(1, 1, 1);
    vprint(-WINDOW_WIDTH / 4 - 110, WINDOW_HEIGHT / 6 - 260, GLUT_BITMAP_8_BY_13, "Press 'c' or 'C' to close the curtains and get more info about the program :)");




    glutSwapBuffers();
}

// Key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
void onKeyDown(unsigned char key, int x, int y) {
    // Exit when ESC is pressed.
    if (key == 27)
        exit(0);

    if (key == 'e' || key == 'E') {

        if (radiusB < winHeight / 3) {
            radiusB += 10;
        }

    }

    if (key == 's' || key == 'S') {

        if (radiusB > winHeight / 10) {
            radiusB -= 10;
        }



    }

    if (key == 'c' || key == 'C') {

        flag = !flag;

    }






    if (key == ' ')
        activeTimer = !activeTimer;

    // To refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y) {
    // Exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // To refresh the window it calls display() function
    glutPostRedisplay();
}




// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT

/*
   When a click occurs in the window, it provides which button
   buttons : GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
   states  : GLUT_UP, GLUT_DOWN
   x, y is the coordinate of the point at which the mouse is clicked
*/
void onClick(int button, int stat, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;
    }
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN) {

        xB = x - winWidth / 2;
        yB = winHeight / 2 - y;

    }

    // To refresh the window it calls display() function
    glutPostRedisplay();
}

/*
   This function is called when the window size changes.
   w : is the new width of the window in pixels
   h : is the new height of the window in pixels
*/
void onResize(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // Refresh window
}

void onMoveDown(int x, int y) {
    // Write your codes here.

    // To refresh the window it calls display() function
    glutPostRedisplay();
}

/*
   GLUT to OpenGL coordinate conversion
   x2 = x1 - winWidth / 2
   y2 = winHeight / 2 - y1
*/
void onMove(int x, int y) {
    // Write your codes here.

    // To refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);

    if (activeTimer) {
        // animate the current shape until it touches the edge of the window.

        if (yB + radiusB < winHeight / 2 + 250) {
            yB++;
            xS -= 2;
            yS += 0.8;
        }
        else {
            yB = -WINDOW_HEIGHT / 3;
            xS = -100;
            yS = 100;
        }


    }

    //to refresh the window it calls display() function
    glutPostRedisplay(); //display()
}
#endif

void init() {
    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char *argv[]) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(600, 300);
    glutCreateWindow("164 HW1 Hamit Efe Eldem Cappadocia Hotel Room");

    // Window Events
    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    // Keyboard Events
    glutKeyboardFunc(onKeyDown);

    glutKeyboardUpFunc(onKeyUp);

    // Mouse Events
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
    // Timer Event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    // Initialize random generator
    srand(time(0));

    init();
    glutMainLoop();
    return 0;
}


