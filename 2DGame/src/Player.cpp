#include "Player.h"
#include "main.h"
#include <iostream>
#define SPRITEX 0.1655
#define SPRITEY 0.2
#define PLAYERWIDTH 42
#define PLAYERHEIGHT 27

Player::Player()
{
    x = 0;
    y = 0;
    moving = 0;
    attacking = 0;
    direction = 1;
    step = 0;
    swing = 0;
}

Player::Player(bool enemy){

    moving = 0;
    attacking = 0;
    direction = 1;
    step = 0;
    swing = 0;
    if(enemy){
        controller = false;
        int x1 = ((rand() % 41) + 270);
        int y1 = ((rand() % 340) - 170);
        x = x1 - (x1 % 20);
        y = y1 - (y1 % 20);
        health = 1;
    } else {
        controller = true;
        x = 0;
        y = 0;
        health = 3;
    }
}


Player::~Player()
{
    //dtor
}

void Player::movePlayer(){
    //rotate player to the direction they are moving
    if (upMove && step%2 == 0 && direction != 0){
        direction = 0;
        return;
    }
    if (downMove && step%2 == 0 && direction != 1){
        direction = 1;
        return;
    }
    if (leftMove && step%2 == 0 && direction != 2){
        direction = 2;
        return;
    }
    if (rightMove && step%2 == 0 && direction != 3){
        direction = 3;
        return;
    }
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



        //checks to see if the actor is blocked by another actor NOT WORKING----------------------------------------------------------------------------------------------------
        bool canMove = true;
        for (int i = 0; i < actors.size(); i++){
            int diffX = actors[i].x - x;
            int diffY = actors[i].y - y;
            if(!(diffX == 0) && !(diffY == 0)){
                std::cout << "a";
                switch(direction){
                case 0:
                    if(diffX <= 5 && diffX >= -5 && diffY <= 20)
                        canMove = false;
                    break;
                case 1:
                    if(diffX <= 5 && diffX >= -5 && diffY >= -20)
                        canMove = false;
                    break;
                case 2:
                    if(diffX >= -20 && diffY <= 5 && diffY >= -5)
                        canMove = false;
                    break;
                case 3:
                    if(diffX <= 20 && diffY <= 5 && diffY >= -5)
                        canMove = false;
                    break;
                }
            }
        }
        if(canMove){
            x += (X1 - x);
            y += (Y1 - y);
        }

        //cycles through steps
        if(step == 3)
            step = 0;
        else
            step++;

        //stops player
        if(!upMove && !downMove && !leftMove && !rightMove && !(step%2))
            moving = 0;
        std::cout << x << "," << y << std::endl;
    }
}

void Player::attack(){
    /*switch(direction){
    case 0:
        glBegin(GL_LINE_LOOP);
         glVertex2d(-6, -PLAYERHEIGHT/2);
         glVertex2d(-6, 5-PLAYERHEIGHT/2);
         glVertex2d(9, 5-PLAYERHEIGHT/2);
         glVertex2d(9, -PLAYERHEIGHT/2);
        glEnd();
        break;
    case 1:
        glBegin(GL_LINE_LOOP);
         glVertex2d(-6, 0);
         glVertex2d(-6, 5);
         glVertex2d(9, 5);
         glVertex2d(9, 0);
        glEnd();
        break;
    case 2:
        glBegin(GL_LINE_LOOP);
         glVertex2d(2, PLAYERHEIGHT/2);
         glVertex2d(2, 5+PLAYERHEIGHT/2);
         glVertex2d(8, 5+PLAYERHEIGHT/2);
         glVertex2d(8, PLAYERHEIGHT/2);
        glEnd();
        break;
    case 3:
        glBegin(GL_LINE_LOOP);
         glVertex2d(2-PLAYERWIDTH/2, PLAYERHEIGHT/2);
         glVertex2d(2-PLAYERWIDTH/2, 5+PLAYERHEIGHT/2);
         glVertex2d(2+PLAYERWIDTH/2, 5+PLAYERHEIGHT/2);
         glVertex2d(2+PLAYERWIDTH/2, PLAYERHEIGHT/2);
        glEnd();
        break;
    }*/

}

void Player::draw(GLuint* texture){
    // Bind texture
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBindTexture( GL_TEXTURE_2D, *texture );
    // Draw rectangle with texture
    animation();
    glBegin(GL_QUADS);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * offsetY)); glVertex2d(-PLAYERWIDTH/2, -PLAYERHEIGHT/2);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * offsetY)); glVertex2d(PLAYERWIDTH/2, -PLAYERHEIGHT/2);
    glTexCoord2f((SPRITEX * (offsetX+1)), (SPRITEY * (offsetY+1))); glVertex2d(PLAYERWIDTH/2, PLAYERHEIGHT/2);
    glTexCoord2f((SPRITEX * offsetX), (SPRITEY * (offsetY+1))); glVertex2d(-PLAYERWIDTH/2, PLAYERHEIGHT/2);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

void Player::animation(){
    if(attacking){
        switch(swing){
        case 0:
            offsetX = 3;
            ++swing;
            break;
        case 1:
            offsetX = 4;
            ++swing;
            break;
        case 2:
            offsetX = 5;
            ++swing;
            break;
        case 3:
            offsetX = 0;
            swing = 0;
            attacking = false;
            break;
        }
        switch(direction){
        case 0:
            offsetY = 3;
            break;
        case 1:
            offsetY = 4;
            break;
        case 2:
            offsetY = 2;
            break;
        case 3:
            offsetY = 1;
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
            offsetY = 3;
            break;
        case 1:
            offsetY = 4;
            break;
        case 2:
            offsetY = 2;
            break;
        case 3:
            offsetY = 1;
            break;
        }
    }
}


