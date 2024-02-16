#include "main.h"

GLuint playerTex;
GLuint backTex;
int offset = 0, inverse = 1;

void loadTexture(){
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    playerTex = SOIL_load_OGL_texture(
        "sprites/PMMovement.png",
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

void player()
{
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, playerTex );
    // Draw rectangle with texture
    animation();
    glBegin(GL_QUADS);
    glTexCoord2f((0.166 * offset), 0.0f); glVertex2d(-4.5, -5);
    glTexCoord2f((0.166 * offset) + (inverse * 0.166f), 0.0f); glVertex2d(4.5, -5);
    glTexCoord2f((0.166 * offset) + (inverse * 0.166f), 1.0f); glVertex2d(4.5, 5);
    glTexCoord2f((0.166 * offset), 1.0f); glVertex2d(-4.5, 5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void background()
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture( GL_TEXTURE_2D, backTex );
    // Draw rectangle with texture
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex2d(-200, -200);
    glTexCoord2f(0.0f, 0.0f); glVertex2d(200, -200);
    glTexCoord2f(0.0f, 1.0f); glVertex2d(200, 200);
    glTexCoord2f(1.0f, 1.0f); glVertex2d(-200, 200);
    glEnd();
}

void drawBounds(){
    glTranslated(-playerX, -playerY, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
     for(int i = 0; i < bounds.points;i++){
        glVertex2d(bounds.coordX[i], bounds.coordY[i]);
     }
    glEnd();
}

void animation(){
    switch(playerDir){
    case 0:
        switch(step){
        case 0: case 2:
            offset = 1;
            inverse = 1;
            break;
        case 1:
            offset = 4;
            inverse = 1;
            break;
        case 3:
            offset = 5;
            inverse = -1;
            break;
        }
        break;
    case 1:
        switch(step){
        case 0: case 2:
            offset = 0;
            inverse = 1;
            break;
        case 1:
            offset = 3;
            inverse = 1;
            break;
        case 3:
            offset = 4;
            inverse = -1;
            break;
        }
        break;
    case 2:
        switch(step){
        case 0: case 2:
            offset = 2;
            inverse = 1;
            break;
        case 1: case 3:
            offset = 5;
            inverse = 1;
            break;
        }
        break;
    case 3:
        switch(step){
        case 0: case 2:
            offset = 3;
            inverse = -1;
            break;
        case 1: case 3:
            offset = 6;
            inverse = -1;
            break;
        }
        break;
    }
}

