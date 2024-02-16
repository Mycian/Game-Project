#include	<GL/glut.h>
#include    <SOIL/SOIL.h>

//main globals
extern void game(); //To draw general scenery of the game
extern void initWindow();
extern void gameKeys( unsigned char key );
extern void gameKeysUp( unsigned char key);
extern void resetGame();
extern void movePlayer();


//Models
extern void loadTexture();
extern void player();
extern void background();
extern void drawBounds();

//Game globals
extern int playerDir;
extern int playerX;
extern int playerY;
extern int moving;
extern int step;
struct boundary{
    int points;
    int coordX[100];
    int coordY[100];
};
extern struct boundary bounds;

//OpenGL globals and functions
extern int advance, anim, alias;
extern int orthox1, orthoy1, orthox2, orthoy2;
//extern void initWindow( int argc, char **argv );
extern void init3D();
extern void defineCallbacks();
extern void glutPrintBM(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );
extern void glutPrintSt(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );

