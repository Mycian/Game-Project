#include "main.h"

//Variables for initializing process
int advance=0, anim=1, alias=1;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;

//Local prototypes
void loop( void );
void draw();
void reshape(int width, int height );
void keyboard( unsigned char key, int x, int y );
void keyboardUp( unsigned char key, int x, int y);
void mouse( int button, int state, int x, int y );
void movement( int x, int y );

void initWindow( int argc, char **argv )
{
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1000, 1000 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Application" );

}
void init3D()
{
	glClearColor( 0.0,0.0,0.0, 0.0 );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POLYGON_SMOOTH );
	glEnable( GL_BLEND);
}

void defineCallbacks()
{
    glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutKeyboardUpFunc( keyboardUp );
	glutMouseFunc( mouse );
	glutMotionFunc( movement );
	glutIdleFunc( loop );
}

//Function for the animation
void loop( void )
{
	advance++;
	draw();
	Sleep( 50 );//miliseconds
}

void draw()
{
    glClear( GL_COLOR_BUFFER_BIT );
    game();
    glutSwapBuffers();
}
//Callback, when a reshape happened
void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	float aspect=(float)width/height;
	if( aspect>=1.0 ) //wide
	{
		orthox1=-100*aspect; orthox2=100*aspect;
		orthoy1=-100; orthoy2=100;
	} else {
		orthox1=-100; orthox2=100;
		orthoy1=-100/aspect; orthoy2=100/aspect;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D( orthox1, orthox2, orthoy1, orthoy2 );

	glMatrixMode( GL_MODELVIEW );
}

void keyboard( unsigned char key, int x, int y )
{
	switch( toupper( key ) )
	{
	case 27:
		exit( 0 );
		break;
	case ' ':
		anim = !anim;
		if( anim )
			glutIdleFunc( loop );
		else
			glutIdleFunc( 0 );
		break;
	case 'R':
		resetGame();
		draw();
		break;
	default:
		gameKeys( toupper( key ) );
	}
}

void keyboardUp( unsigned char key, int x, int y ){
    gameKeysUp( toupper(key));
}

void mouse( int button, int state, int x, int y )
{
	if( state==GLUT_DOWN )
	{
		mn_x0=x;
		mn_y0=y;
		mouse_left =  ( button==GLUT_LEFT_BUTTON ?1:0 );
		mouse_right = ( button==GLUT_RIGHT_BUTTON?1:0 );
	}
	if( state==GLUT_UP )
		mouse_left=mouse_right=0;

    if(mouse_left){
        attack();
    }
}

void movement( int x, int y )
{
	if( mouse_right ){}
	if( mouse_left ){}
	mn_x0=x;
	mn_y0=y;
}

