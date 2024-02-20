#include    <windows.h>
#include	<GL/glut.h>
#include    <SOIL/SOIL.h>
#include    <math.h>
#include    "Player.h"
#include    "Bounds.h"

//main globals
extern void game(); //To draw general scenery of the game
extern void gameKeys( unsigned char key );
extern void gameKeysUp( unsigned char key);
extern void attack();
extern void resetGame();
//models and actors
extern GLuint playerTex;
extern GLuint backTex;
extern Player character;


//OpenGL globals and functions
extern int advance, anim, alias;
extern int orthox1, orthoy1, orthox2, orthoy2;
extern void initWindow( int argc, char **argv );
extern void init3D();
extern void defineCallbacks();