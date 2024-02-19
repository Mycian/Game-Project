#include "main.h"
#define SPRITEX 0.214
#define SPRITEY 0.25

GLuint playerTex;
GLuint backTex;
int offsetX = 0, offsetY = 0;

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

void player()
{
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, playerTex );
    // Draw rectangle with texture
    animation();
    glBegin(GL_QUADS);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * offsetY)); glVertex2d(-10, -10);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * offsetY)); glVertex2d(10, -10);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * (offsetY+1))); glVertex2d(10, 10);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * (offsetY+1))); glVertex2d(-10, 10);
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
    if(attacking){
        switch(playerDir){
        case 0:
            switch(attacking){
            case 0: case 2:
                offsetX = 0;
                offsetY = 2;
                break;
            case 1:
                offsetX = 1;
                offsetY = 2;
                break;
            case 3:
                offsetX = 2;
                offsetY = 2;
                break;
            }
            break;
        case 1:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 3;
                break;
            case 1:
                offsetX = 1;
                offsetY = 3;
                break;
            case 3:
                offsetX = 2;
                offsetY = 3;
                break;
            }
            break;
        case 2:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 1;
                break;
            case 1:
                offsetX = 1;
                offsetY = 1;
                break;
            case 3:
                offsetX = 2;
                offsetY = 1;
            }
            break;
        case 3:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 0;
                break;
            case 1:
                offsetX = 1;
                offsetY = 0;
                break;
            case 3:
                offsetX = 2;
                offsetY = 0;
            }
            break;
        }
    } else {
        switch(playerDir){
        case 0:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 2;
                break;
            case 1:
                offsetX = 1;
                offsetY = 2;
                break;
            case 3:
                offsetX = 2;
                offsetY = 2;
                break;
            }
            break;
        case 1:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 3;
                break;
            case 1:
                offsetX = 1;
                offsetY = 3;
                break;
            case 3:
                offsetX = 2;
                offsetY = 3;
                break;
            }
            break;
        case 2:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 1;
                break;
            case 1:
                offsetX = 1;
                offsetY = 1;
                break;
            case 3:
                offsetX = 2;
                offsetY = 1;
            }
            break;
        case 3:
            switch(step){
            case 0: case 2:
                offsetX = 0;
                offsetY = 0;
                break;
            case 1:
                offsetX = 1;
                offsetY = 0;
                break;
            case 3:
                offsetX = 2;
                offsetY = 0;
            }
            break;
        }
    }
}

