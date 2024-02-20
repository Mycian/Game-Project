#include "Player.h"
#include "main.h"
#define SPRITEX 0.1655
#define SPRITEY 0.25

Player::Player()
{
    x = 0;
    y = 0;
    moving = 0;
    attacking = 0;
    direction = 1;
    step = 0;
}

Player::~Player()
{
    //dtor
}

void Player::movePlayer(){
    //rotate player to the direction they are moving
    if (upMove && step%2 == 0)
        direction = 0;
    if (downMove && step%2 == 0)
        direction = 1;
    if (leftMove && step%2 == 0)
        direction = 2;
    if (rightMove && step%2 == 0)
        direction = 3;

    if (moving){
        //finds the coordinates
        int X1 = x, Y1 = y;
        if(direction == 0 && moving)
            Y1 += 10;
        if(direction == 1 && moving)
            Y1 -= 10;
        if(direction == 2 && moving)
            X1 -= 10;
        if(direction == 3 && moving)
            X1 += 10;

        //checks for collision and moves if able
        /*int hit = collision(X1, Y1, bounds, 1);
        if(!hit || (hit && !(X1%10) && !(Y1%10)))
        {*/
            x += (X1 - x)/2;
            y += (Y1 - y)/2;
        //}

        //cycles through steps
        if(step == 3)
            step = 0;
        else
            step++;

        //stops player
        if(!upMove && !downMove && !leftMove && !rightMove && !(step%2))
            moving = 0;

    }
}

void Player::attack(){

}

void Player::draw(GLuint* texture){
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, playerTex );
    // Draw rectangle with texture
    animation();
    glBegin(GL_QUADS);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * offsetY)); glVertex2d(-15, -10);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * offsetY)); glVertex2d(15, -10);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * (offsetY+1))); glVertex2d(15, 10);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * (offsetY+1))); glVertex2d(-15, 10);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Player::animation(){
    if(attacking){
        switch(attacking){
        case 1:
            offsetX = 3;
            attacking++;
            break;
        case 2:
            offsetX = 4;
            attacking++;
            break;
        case 3:
            offsetX = 5;
            attacking = 0;
            break;
        }
        switch(direction){
        case 0:
            offsetY = 2;
            break;
        case 1:
            offsetY = 3;
            break;
        case 2:
            offsetY = 1;
            break;
        case 3:
            offsetY = 0;
        }
    } else {
        switch(step){
        case 0: case 2:
            offsetX = 0;
            break;
        case 1:
            offsetX = 1;
            break;
        case 3:
            offsetX = 2;
            break;
        }
        switch(direction){
        case 0:
            offsetY = 2;
            break;
        case 1:
            offsetY = 3;
            break;
        case 2:
            offsetY = 1;
            break;
        case 3:
            offsetY = 0;
            break;
        }
    }
}


