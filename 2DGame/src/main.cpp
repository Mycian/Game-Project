#include "main.h"

//globalvariables
Player character;
GLuint playerTex;
GLuint backTex;
//function prototypes
void defineBounds();
void loadTexture();
void attack();

//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
    initWindow( argc, argv ); //without &
	init3D();
	defineCallbacks();
	defineBounds();
    loadTexture();
	glutMainLoop();
}

void defineBounds(){
    Bounds border;
    border.points = 36;
    for (int i = 0; i < border.points; i++){
        border.x[i] = cos(((360/border.points)/57.29f)*i) * 160;
        border.y[i] = sin(((360/border.points)/57.29f)*i) * 155 + 5;
    }
}

void game()
{
	glLoadIdentity();
	if(character.attacking && !(character.step%2))
        character.attack();
	else
        character.movePlayer();

    // Draw background
	glTranslated(-character.x, -character.y, 0.0);
	glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, backTex );
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex2d(-200, -200);
    glTexCoord2f(0.0f, 0.0f); glVertex2d(200, -200);
    glTexCoord2f(0.0f, 1.0f); glVertex2d(200, 200);
    glTexCoord2f(1.0f, 1.0f); glVertex2d(-200, 200);
    glEnd();
    glColor3f( 1.0, 1.0, 1.0 );



	glLoadIdentity();
    character.draw(&playerTex);
	glColor3f(1.0,1.0,1.0);
}

void loadTexture(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    playerTex = SOIL_load_OGL_texture(
        "sprites/playerSheet.png",
        SOIL_LOAD_AUTO,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    //bind texture
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    backTex = SOIL_load_OGL_texture(
        "sprites/back.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
}

//Action keys for this application, called the from keyboard() callback.
void gameKeys( unsigned char key )
{
	switch( key )
	{
	case 'W':
	    character.upMove = 1;
	    character.downMove = 0;
	    character.leftMove = 0;
	    character.rightMove = 0;
	    character.moving = 1;
		break;
	case 'S':
	    character.upMove = 0;
	    character.downMove = 1;
	    character.leftMove = 0;
	    character.rightMove = 0;
	    character.moving = 1;
		break;
	case 'A':
	    character.upMove = 0;
	    character.downMove = 0;
	    character.leftMove = 1;
	    character.rightMove = 0;
	    character.moving = 1;
		break;
	case 'D':
	    character.upMove = 0;
	    character.downMove = 0;
	    character.leftMove = 0;
	    character.rightMove = 1;
	    character.moving = 1;
		break;
	}
}

void gameKeysUp( unsigned char key )
{
	switch( key )
	{
	case 'W':
	    character.upMove = 0;
		break;
	case 'S':
	    character.downMove = 0;
		break;
	case 'A':
	    character.leftMove = 0;
		break;
	case 'D':
	    character.rightMove = 0;
		break;
	}
}

void attack(){
    if(!character.attacking)
        character.attacking++;
}

//Called from keyboard() callback
void resetGame()
{
    character.x = 0;
    character.y = 0;
    character.attacking = 0;
    character.moving = 0;
    character.upMove = 0;
    character.downMove = 0;
    character.leftMove = 0;
    character.rightMove = 0;
    character.step = 0;
    character.direction = 1;
}
