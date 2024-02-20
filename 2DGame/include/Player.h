#ifndef PLAYER_H
#define PLAYER_H
#include <windows.h>
#include "GL/glut.h"


class Player
{
    public:
        Player();
        virtual ~Player();
        int x, y, attacking, moving;
        int upMove, downMove, leftMove, rightMove;
        void movePlayer();
        void attack();
        void draw(GLuint* texture);
        int step;
        int direction;
    protected:

    private:
        int offsetX, offsetY;
        void animation();
};

#endif // PLAYER_H
