#include "main.h"

int playerDir=0, playerX=0, playerY=0, moving = 0, attacking = 0;
int step=0, upMove = 0, downMove = 0, leftMove = 0, rightMove = 0;
struct boundary bounds;


//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
    initWindow( argc, argv ); //without &
	init3D();
	defineCallbacks();
	defineBounds();
	glutMainLoop( );
}

void defineBounds(){
    bounds.points = 36;
    for (int i = 0; i < bounds.points; i++){
        bounds.coordX[i] = cos(((360/bounds.points)/57.29f)*i) * 160;
        bounds.coordY[i] = sin(((360/bounds.points)/57.29f)*i) * 155 + 5;
    }
}


void game()
{
    loadTexture();
	glLoadIdentity();
	if(attacking && !(step%2))
        attack();
	else
        movePlayer();
	glTranslated(-playerX, -playerY, 0.0);
	background();
    glColor3f( 1.0, 1.0, 1.0 );

	glLoadIdentity();
	player();

	//Text data
	char message[120];
	sprintf( message, "X: %d Y: %d Moving: %d Collision:", playerX, playerY, moving, 0);
	glutPrintBM( -90.0, 90.0, GLUT_BITMAP_TIMES_ROMAN_24, message, 1.0, 1.0, 1.0 );

	drawBounds();
	glColor3f(1.0,1.0,1.0);
}
//Action keys for this application, called the from keyboard() callback.
void gameKeys( unsigned char key )
{
	switch( key )
	{
	case 'W':
	    upMove = 1;
	    downMove = 0;
	    leftMove = 0;
	    rightMove = 0;
	    moving = 1;
		break;
	case 'S':
	    upMove = 0;
	    downMove = 1;
	    leftMove = 0;
	    rightMove = 0;
	    moving = 1;
		break;
	case 'A':
	    upMove = 0;
	    downMove = 0;
	    leftMove = 1;
	    rightMove = 0;
	    moving = 1;
		break;
	case 'D':
	    upMove = 0;
	    downMove = 0;
	    leftMove = 0;
	    rightMove = 1;
	    moving = 1;
		break;
	}
}

void gameKeysUp( unsigned char key )
{
	switch( key )
	{
	case 'W':
	    upMove = 0;
		break;
	case 'S':
	    downMove = 0;
		break;
	case 'A':
	    leftMove = 0;
		break;
	case 'D':
	    rightMove = 0;
		break;
	}
}

void movePlayer(){
    //rotate player to the direction they are moving
    if (upMove && step%2 == 0)
        playerDir = 0;
    if (downMove && step%2 == 0)
        playerDir = 1;
    if (leftMove && step%2 == 0)
        playerDir = 2;
    if (rightMove && step%2 == 0)
        playerDir = 3;

    if (moving){
        //finds the coordinates
        int X1 = playerX, Y1 = playerY;
        if(playerDir == 0 && moving)
            Y1 += 10;
        if(playerDir == 1 && moving)
            Y1 -= 10;
        if(playerDir == 2 && moving)
            X1 -= 10;
        if(playerDir == 3 && moving)
            X1 += 10;

        //checks for collision and moves if able
        int hit = collision(X1, Y1, bounds, 1);
        if(!hit || (hit && !(X1%10) && !(Y1%10)))
        {
            playerX += (X1 - playerX)/2;
            playerY += (Y1 - playerY)/2;
        }

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

//collision detection with walls, returns 1 if player cant move
//takes a structure containing the coordinates of an object and the orientation of the boundary

int collision(int x, int y, struct boundary bounds, int orientation){
    if(orientation){
        for ( int i = 0; i < bounds.points - 1; i++ ){
            if(((y - bounds.coordY[i])*(bounds.coordX[i+1] - bounds.coordX[i]) - (x - bounds.coordX[i])*(bounds.coordY[i+1] - bounds.coordY[i])) < 1)
                return 1;
        }
        if(((y - bounds.coordY[bounds.points - 1])*(bounds.coordX[0] - bounds.coordX[bounds.points - 1]) - (x - bounds.coordX[bounds.points - 1])*(bounds.coordY[0] - bounds.coordY[bounds.points - 1])) < 1)
            return 1;
        return 0;
    }
    for ( int i = 0; i < bounds.points - 1; i++ ){
        if(((y - bounds.coordY[i])*(bounds.coordX[i+1] - bounds.coordX[i]) - (x - bounds.coordX[i])*(bounds.coordY[i+1] - bounds.coordY[i])) > -1)
            return 1;
    }
    if(((y - bounds.coordY[bounds.points - 1])*(bounds.coordX[0] - bounds.coordX[bounds.points - 1]) - (x - bounds.coordX[bounds.points - 1])*(bounds.coordY[0] - bounds.coordY[bounds.points - 1])) > -1)
        return 1;
    return 0;
}

//Called from gameKeys()
void attack(){

}


//Called from keyboard() callback
void resetGame()
{
    playerX = 0;
    playerY = 0;
    step = 0;
    moving = 0;
    playerDir = 1;
}


