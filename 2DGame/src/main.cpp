#include "main.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//globalvariables
GLuint playerTex;
GLuint firstBackTex;
GLuint secondBackTex;
GLuint enemyTex;
GLuint heartTex;
float scale = 1;
vector<Player> actors;
int movementTick = 0;
int controllerIndex;

//function prototypes
void defineBounds();
void loadTexture();
void grid();
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

//displays grid for steps. NOT WORKING----------------------------------------------------------------------------------------------------
void grid(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    for(int i = -310; i < 320; i+=10){
        glBegin(GL_LINE);
         glVertex2f(i, -180);
         glVertex2f(i, 180);
        glEnd();
    }
    for(int i = -170; i < 180; i+=10){
        glBegin(GL_LINE);
         glVertex2f(-320, i);
         glVertex2f(320, i);
        glEnd();
    }

}

void defineBounds(){

}

void game()
{
	glLoadIdentity();
    actors[controllerIndex].turnPlayer();
	if(!actors[controllerIndex].attacking )
        actors[controllerIndex].movePlayer();

    sort(actors.begin(), actors.end(), compareZ);
    for(int i = 0; i < actors.size(); i++){
        if(actors[i].controller){
            controllerIndex = i;
        }
    }
    enemyActions();
    // Draw background
    {
    glScalef(scale, scale, scale);
	glTranslated(-actors[controllerIndex].x, -actors[controllerIndex].y, 0.0);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, firstBackTex );
    glBegin(GL_QUADS);
     glTexCoord2f(1.0f, 0.0f); glVertex2d(320, -180);
     glTexCoord2f(0.0f, 0.0f); glVertex2d(-320, -180);
     glTexCoord2f(0.0f, 1.0f); glVertex2d(-320, 180);
     glTexCoord2f(1.0f, 1.0f); glVertex2d(320, 180 );
    glEnd();
    glColor3f( 1.0, 1.0, 1.0 );
    }


    // Draw actors
    {
    glPopMatrix();
    for(int i = 0; i < actors.size(); i++){
        if(!actors[i].controller){
            glPushMatrix();
            glTranslated(actors[i].x, actors[i].y, 0.0);
            actors[i].draw(&enemyTex);
            if(actors[i].swing == 3){
                std::cout << "Actor " << i << std::endl;
                actors[i].attack();
            }
            if(actors[i].health == -4){
                actors.erase(actors.begin()+i);
                i--;
            }
        } else {
            glPushMatrix();
            glLoadIdentity();
            glScalef(scale, scale, scale);
            actors[controllerIndex].draw(&playerTex);
            if(actors[i].swing == 3){
                actors[controllerIndex].attack();
            }
            if(actors[i].health == -4){
                actors.erase(actors.begin()+i);
                controllerIndex = 0;
                i--;
            }
        }
        glPopMatrix();
    }
    }

    /*
     glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    for(int i = -310; i < 320; i+=10){
        glBegin(GL_LINE);
         glVertex2f(i, -180);
         glVertex2f(i, 180);
        glEnd();
    }
    for(int i = -170; i < 180; i+=10){
        glBegin(GL_LINE);
         glVertex2f(-320, i);
         glVertex2f(320, i);
        glEnd();
    }
     */

    //Draw health Indicators
    glLoadIdentity();
    if(actors[controllerIndex].health > 0){
        for(int i = 0; i < actors[controllerIndex].health; i++){
            glEnable(GL_TEXTURE_2D);
            glBindTexture( GL_TEXTURE_2D, heartTex );
            glBegin(GL_QUADS);
             glTexCoord2f(1.0f, 0.0f); glVertex2d(-98 + (i*10), 90);
             glTexCoord2f(0.0f, 0.0f); glVertex2d(-90 + (i*10), 90);
             glTexCoord2f(0.0f, 1.0f); glVertex2d(-90 + (i*10), 98);
             glTexCoord2f(1.0f, 1.0f); glVertex2d(-98 + (i*10), 98 );
            glEnd();
        }
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

    //bind texture
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    heartTex = SOIL_load_OGL_texture(
        "sprites/heart.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    actors.push_back(Player(false));
}

bool compareZ(Player p1, Player p2){
    return (p1.y > p2.y);
}

//Action keys for this application, called the from keyboard() callback.
void gameKeys( unsigned char key )
{
    if(actors[controllerIndex].controller){
        switch( key )
        {
        case 'W':
            actors[controllerIndex].upMove = 1;
            actors[controllerIndex].downMove = 0;
            actors[controllerIndex].leftMove = 0;
            actors[controllerIndex].rightMove = 0;
            actors[controllerIndex].moving = 1;
            break;
        case 'S':
            actors[controllerIndex].upMove = 0;
            actors[controllerIndex].downMove = 1;
            actors[controllerIndex].leftMove = 0;
            actors[controllerIndex].rightMove = 0;
            actors[controllerIndex].moving = 1;
            break;
        case 'A':
            actors[controllerIndex].upMove = 0;
            actors[controllerIndex].downMove = 0;
            actors[controllerIndex].leftMove = 1;
            actors[controllerIndex].rightMove = 0;
            actors[controllerIndex].moving = 1;
            break;
        case 'D':
            actors[controllerIndex].upMove = 0;
            actors[controllerIndex].downMove = 0;
            actors[controllerIndex].leftMove = 0;
            actors[controllerIndex].rightMove = 1;
            actors[controllerIndex].moving = 1;
            break;
        case 'K':
            actors[controllerIndex].health = 0;
        }
    }
}

void gameKeysUp( unsigned char key )
{
	switch( key )
	{
	case 'W':
	    actors[controllerIndex].upMove = 0;
		break;
	case 'S':
	    actors[controllerIndex].downMove = 0;
		break;
	case 'A':
	    actors[controllerIndex].leftMove = 0;
		break;
	case 'D':
	    actors[controllerIndex].rightMove = 0;
		break;
	}
}

void attack(){
    if(actors[controllerIndex].attacking == false && actors[controllerIndex].controller)
        actors[controllerIndex].attacking = true;
}

void enemyActions(){
    if(actors.size() < 4)
        actors.push_back(Player(true));
    for(int i = 0; i < actors.size(); i++){
        if(!actors[i].controller){
            if(actors[i].x < actors[controllerIndex].x){
                    //if the Enemy is to the left of the Player
                if(actors[i].y - actors[controllerIndex].y > -(actors[i].x - actors[controllerIndex].x)){
                    actors[i].upMove = 0;
                    actors[i].downMove = 1;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else if (-(actors[i].y - actors[controllerIndex].y) > -(actors[i].x - actors[controllerIndex].x)){
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
                    //if the Enemy is to the right of the Player
                if(actors[i].y - actors[controllerIndex].y > actors[i].x - actors[controllerIndex].x){
                    actors[i].upMove = 0;
                    actors[i].downMove = 1;
                    actors[i].leftMove = 0;
                    actors[i].rightMove = 0;
                } else if (-(actors[i].y - actors[controllerIndex].y) > actors[i].x - actors[controllerIndex].x){
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

            //This determines if the enemy is close enough to attack and does so if able
            {
            int diffX = actors[i].x - actors[controllerIndex].x;
            int diffY = actors[i].y - actors[controllerIndex].y;
            if(movementTick == 0){
                if(diffX <= 5 && diffX >= -5 && diffY <= 20 && diffY >= -20) { //This determines the enemy's state
                    actors[i].attacking = true;
                    actors[i].moving = false;
                } else if (diffX <= 20 && diffX >= -20 && diffY <= 5 && diffY >= -5){
                    actors[i].attacking = true;
                    actors[i].moving = false;
                } else {
                    actors[i].attacking = false;
                    actors[i].moving = true;
                }
                actors[i].turnPlayer();
                actors[i].movePlayer();
            }
            movementTick++;
            movementTick = movementTick % 5;
            }
        }

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
    actors.erase(actors.begin(),actors.end());
    actors.push_back(Player(false));
}
