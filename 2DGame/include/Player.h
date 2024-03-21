#ifndef PLAYER_H
#define PLAYER_H
#include <windows.h>
#include "GL/glut.h"


class Player
{
    public:
        Player();
        Player(bool player);
        virtual ~Player();
        int x, y;
        bool attacking, moving;
        int upMove, downMove, leftMove, rightMove;
        void movePlayer();
        void attack();
        void draw(GLuint* texture);
        int step, swing;
        int direction;
        bool controller;
        int health;
    protected:

    private:
        int offsetX, offsetY;
        void animation();
};

#endif // PLAYER_H
