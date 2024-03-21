#include "main.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
//globalvariables
Player character;
GLuint playerTex;
GLuint firstBackTex;
GLuint secondBackTex;
GLuint enemyTex;
float scale = 1;
vector<Player> actors;
int movementTick = 0;
//function prototypes
void defineBounds();
void loadTexture();
void attack();
void enemyActions();
bool compareZ(Player p1, Player p2);



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

void grid(){
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    for(int i = -310; i < 320; i+10){
         glVertex2d(i, -180);
         glVertex2d(i, 180);
    }
    for(int i = -170; i < 180; i+10){
         glVertex2d(-320, i);
         glVertex2d(320, i);
    }
    glEnd();
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

	if(!character.attacking )
        character.movePlayer();
    sort(actors.begin(), actors.end(), compareZ);


    enemyActions();

    // Draw background
    {
    glScalef(scale, scale, scale);
	glTranslated(-character.x, -character.y, 0.0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, firstBackTex );
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex2d(320, -180);
    glTexCoord2f(0.0f, 0.0f); glVertex2d(-320, -180);
    glTexCoord2f(0.0f, 1.0f); glVertex2d(-320, 180);
    glTexCoord2f(1.0f, 1.0f); glVertex2d(320, 180 );
    glEnd();
    //grid();
    glColor3f( 1.0, 1.0, 1.0 );
    }


    // Draw enemies
    {
    glPopMatrix();
    for(int i = 0; i < actors.size(); i++){
        glPushMatrix();
        glTranslated(actors[i].x, actors[i].y, 0.0);
        actors[i].draw(&enemyTex);
        glPopMatrix();
    }
    }

	// Draw Player
	{
    glLoadIdentity();
	glScalef(scale, scale, scale);
    character.draw(&playerTex);
    if(character.attacking )
        character.attack();
	}

	glColor3f(1.0,1.0,1.0);
}

void loadTexture(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    playerTex = SOIL_load_OGL_texture(
        "sprites/playerSheet.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    //bind texture
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    firstBackTex = SOIL_load_OGL_texture(
        "sprites/Map1.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    //bind texture
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    secondBackTex = SOIL_load_OGL_texture(
        "sprites/Map2.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    //bind texture
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    enemyTex = SOIL_load_OGL_texture(
        "sprites/enemySheet.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    actors.push_back(Player(false));
    character = actors[0];
}

bool compareZ(Player p1, Player p2){
    return (p1.y > p2.y);
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
    character.attacking = true;
}

void enemyActions(){
    if(actors.size() < 4)
        actors.push_back(Player(true));
    for(int i = 0; i < actors.size(); i++){
        if(!actors[i].controller)
            if(actors[i].x < character.x){
                if(actors[i].y - character.y > -(actors[i].x - character.x)){
                    actors[i].upMove = 0;
                    actors[i].downMove = 1;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else if (-(actors[i].y - character.y) > -(actors[i].x - character.x)){
                    actors[i].upMove = 1;
                    actors[i].downMove = 0;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else {
                    actors[i].upMove = 0;
                    actors[i].downMove = 0;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 1;
                }
            } else {
                if(actors[i].y - character.y > actors[i].x - character.x){
                    actors[i].upMove = 0;
                    actors[i].downMove = 1;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else if (-(actors[i].y - character.y) > actors[i].x - character.x){
                    actors[i].upMove = 1;
                    actors[i].downMove = 0;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else {
                    actors[i].upMove = 0;
                    actors[i].downMove = 0;
                    actors[i].leftMove = 1;
                    actors[i].rightMove = 0;
                }
            }
            if(actors[i].y - character.x == 20 || actors[i].x - character.x == 20){
                actors[i].attacking = true;
                actors[i].moving = false;
            } else {
                actors[i].attacking = false;
                actors[i].moving = true;
            }
            if(movementTick == 0){
                actors[i].movePlayer();
                //*std::cout << "Enemy " << i << ": " << actors[i].x << ", " << actors[i].y << std::endl;
            }
            movementTick++;
            movementTick = movementTick % 5;
        }

}

void zoom(bool in){
    if(!in && (scale > .5)){
        scale *= 0.9;
        return;
    }
    else if (in && scale < 1.5){
        scale *= 1.1;
    }
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
