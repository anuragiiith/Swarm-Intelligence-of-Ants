#include<iostream>
#include<cmath>
#include<GL/glut.h>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<string.h>
#include<assert.h>
#include"imageloader.cpp"
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#define RAD2DEG(deg) (deg * 180 / PI)
#define sqr(a) (a*a)
// Function Declarations
void drawScene();
void update(int value);
void drawBox(float x,float y,float length_x,float length_y);
void drawFloor(float x,float y);
void drawFood(float length_floor_x,float length_floor_y,int quadrent);
void drawSource(float length_floor_x,float length_floor_y,int quadrent);
int opposite(int a);
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

// Global Variables
int pause=0;
float length_box=1.0;
float length_floor_x=70.0,length_floor_y=40;
int quadrent=1;
float radius_source=2.0;
int number_of_ants=40;
float radius_head=0.5,radius_tail=1;
int timer_limit=10;
int flag_pheromone=0,j,k;
string message;
int message_counter=0;
int game_stage=0; // game_stage 0->blank, 1->learn(AI) ,2-> Learn(without block), 3-> Instructions , 4->Play, 5-> exit;
float block_xpos=-47.0;
float block_ypos=-22.0;
float block_radius=3.0;
int displaywon=0;


struct point
{
    float x;
    float y;
};

map<pair<float,float>,int> mymap;
typedef map<pair<float,float>,int> ::iterator outer_iter,it;

// Global Flag
bool start_ant_from_source=0;
float w,h;
void setOrthographicProjection()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}
void resetPerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
#include "classes.h"
#include"button.cpp"
int loop=0;
void yoyo();
int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    w = glutGet(GLUT_SCREEN_WIDTH);
    h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = (int)w ;
    int windowHeight = (int)h ;

    glutInitWindowSize(windowWidth, windowHeight);
    //    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("SWARM INTELLIGENCE");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);

    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(MousePassiveMotion);
    yoyo();
    Init();

    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
Food food;
Source source;
Ant ant[50];
#include "functions.h"
GLuint _textureId; //The id of the texture
GLuint _textureId0; //The id of the texture
GLuint _textureId1; //The id of the texture
GLuint _textureId2; //The id of the texture
GLuint _textureId3; //The id of the texture
GLuint _textureId4; //The id of the texture
GLuint _textureId5; //The id of the texture
GLuint _textureId6; //The id of the texture
GLuint _textureId7; //The id of the texture
GLuint _textureId8; //The id of the texture
GLuint _textureId9; //The id of the texture
GLuint _textureId10; //The id of the texture
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
            0,                            //0 for now
            GL_RGB,                       //Format OpenGL uses for image
            image->width, image->height,  //Width and height
            0,                            //The border of tee image
            GL_RGB, //GL_RGB, because pixels are stored in RGB format
            GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
            image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}
void yoyo() // Well This was the last function added. It loads the images, was not named Properly Sorry :( .
{
    Image* image = loadBMP("main.bmp");
    _textureId0 = loadTexture(image);
    delete image;
    Image *image1 = loadBMP("learn.bmp");
    _textureId1 = loadTexture(image1);
    delete image1;
    Image *image2 = loadBMP("instruction.bmp");
    _textureId2 = loadTexture(image2);
    delete image2;
    Image *image3 = loadBMP("grass.bmp");
    _textureId3 = loadTexture(image3);
    delete image3;

}

// Converts int to string
string itoa(int a)
{
    string s;
    int b=a,count=0,i;
    if(a==0)
    {    
        s+='0';
        return s;
    }    
    while(b!=0)
    {    
        count++;
        b/=10;
    }    
    for(int i=0;i<count;i++)
    {    
        s+=((int)(a/pow(10,count-1-i))%10)+'0';  
    }    
    return s;
}
// To continously show pop ups on tthe screen.
void drawpopup()
{
    if(game_stage==4)
    {
        setOrthographicProjection();
        glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0f,1.0f,1.0f);


        if(message_counter>0 && message!="")
        {
            message_counter--;
            glRasterPos2f(1170,180);
            int len=message.length();
            for (int i = 0; i < len; i++) 
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,message[i]);
        }
        if(displaywon==0)
        {
            glRasterPos2f(1170,280);
            int player_won=0;
            for(int i=0;i<number_of_ants;i++)
                player_won+=(ant[i].dead_flag==1);

            string temp="Score " + itoa(player_won*10+(loop++)/100);
            int len=temp.length();
            for (int i = 0; i < len; i++) 
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,temp[i]);
            glRasterPos2f(1170,380);
            temp="Ants Killed " + itoa(player_won);
            len=temp.length();
            for (int i = 0; i < len; i++) 
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,temp[i]);
        }
        glPopMatrix();
        resetPerspectiveProjection();
    }

}
// Draws Pheromone
void drawPheromone(float xPos,float yPos,float radius,int x)
{
    glPushMatrix();
    glTranslatef(xPos, yPos,5.0);
    float intensity=(float)x;
    float X=intensity/100.00;
    glColor3f(X*1.0f,0.0f, (1.0-X)*0.0f);
    glVertex2d(0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);

    double theta;
    for (int a = 0; a < 360; a+=5 )
    {
        theta = a * 3.1415/180;
        glVertex2d (cos(theta) * radius , sin(theta) * radius);
    }
    glEnd();
    glPopMatrix();
}
void draw_block();
// Just a declaration Function Later in the Code.
// Draw Scene Most important because it calls all rest of the functions.
void drawScene() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,80, 0,0, 0, 0.0, 1.0, 0.0);
    GLfloat ambientColor[] = {0.3,0.3,0.3,1.0f};
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);   // Decide overall size of screen 
    Draw2D();
    drawFloor(length_floor_x,length_floor_y); // drawFloor takes two argument the length and the width of the floor
    drawpopup();
    if(game_stage==5)
        exit(1);
    if(game_stage==4)
    {
        draw_block();
        if(pause==0){
            food.setFood(length_floor_x,length_floor_y); //food and source would be drawn in opposite quadrents
            source.setSource(length_floor_x,length_floor_y,opposite(food.quadrent)); 
        }
        int player_won=0;
        for(int i=0;i<number_of_ants;i++)
        {
            if(start_ant_from_source==0)		// Ant will start from source only at once.	
            {	ant[i].xpos=source.xpos;
                ant[i].ypos=source.ypos;
            }
            if((((ant[i].xpos-block_xpos)*(ant[i].xpos-block_xpos)) + ((ant[i].ypos-block_ypos)*(ant[i].ypos-block_ypos)) <= (block_radius-1.5)*(block_radius-1.5)))
            {
                ant[i].dead_flag=1;
                if(pause==0)
                {
                    message="WOW Score!!";
                    message_counter=20;
                    drawpopup();
                }

            }
            if(ant[i].dead_flag==0)
            {
                if(pause==0)
                    ant[i].setAnt();
            }
            else
                player_won++;
        }
        for(it itr=mymap.begin();itr!=mymap.end();itr++)
        {
            if(itr->second>0)
                itr->second-- ;
            else
                mymap.erase(itr);
        }
        for(outer_iter itr=mymap.begin(); itr!=mymap.end(); itr++)
        {
            if(pause==0)drawPheromone(itr->first.first,itr->first.second,0.1,itr->second);
        }
        if(food.radius<=0.0 && displaywon==0)
        {
            displaywon=1;
            message="Computer WON!!";
            message_counter=500;
            pause=1;
            drawpopup();
        }
        if(player_won==number_of_ants && displaywon==0)
        {
            displaywon=1;
            message="Congrats You WON!!";
            message_counter=500;
            drawpopup();
            pause=1;
        }
        if(displaywon && message_counter==0)
            exit(1);
        start_ant_from_source=1;			// Here it deactivates the above for loop if statement .
    }
    glPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) 
{
    glutTimerFunc(10, update, 0);
}
// Just some Hacks in the Game.
int opposite(int quadrent)
{
    return (quadrent+1)%4+1;
}
// Draws Circular Block.
void draw_block()
{
    glPushMatrix();
    glTranslatef(block_xpos,block_ypos,5.0);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2d(0.0,0.0);
    glBegin(GL_TRIANGLE_FAN);
    float radius=block_radius;
    double theta;
    for (int a = 0; a < 360; a+=5 )
    {   
        theta = a * 3.1415/180;
        glVertex2d (cos(theta) * radius , sin(theta) * radius);
    }   
    glEnd();
    glPopMatrix();
}
// Draws Floor
void drawFloor(float length_x,float length_y)
{
    if(game_stage<=4)
    {
        glEnable(GL_TEXTURE_2D);
        if(game_stage==0)
            glBindTexture(GL_TEXTURE_2D, _textureId0);
        if(game_stage==1)
            glBindTexture(GL_TEXTURE_2D, _textureId1);
        if(game_stage==3)
            glBindTexture(GL_TEXTURE_2D, _textureId2);
        if(game_stage==4)
            glBindTexture(GL_TEXTURE_2D, _textureId3);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    length_x+=10;
    length_y+=10;
    float start_x=length_x/2.0,finish_x=length_x/2;
    float start_y=length_y/2.0,finish_y=length_y/2;
    int i,j;
    if(game_stage<=4)
    {
        glColor3f(1.0f, 1.0f, 1.0f);
        drawBox(0,0,length_x,length_y);
    }
    else
    {
        for(i=-start_x; i<=finish_x; i++)
        {   
            for(j=start_y; j>=-finish_y;j--)
            {   
                glPushMatrix();
                glColor3f(0.2f, 0.2f, 1.0f);    
                drawBox(i,j,length_box,length_box);      
                glPopMatrix();
            }   
        } 
    }
    if(game_stage<=4)
        glDisable(GL_TEXTURE_2D);

}
// Draws Boxes.
void drawBox(float x,float y,float length_x,float length_y) 
{
    float var=length_x/2.0,var1=length_y/2.0;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f( x-var, y-var1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f( x+var, y-var1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f( x+var, y+var1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(	x-var, y+var1);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if(key=='q')
        exit(1);
    if(key=='p')
        pause=!pause;

}

void handleKeypress2(int key, int x, int y) {
    if(game_stage==4)
    {
        if (key == GLUT_KEY_LEFT)
        {
            block_xpos -= 0.6;

            if(sqrt((food.xpos - block_xpos)*(food.xpos - block_xpos) + (food.ypos - block_ypos)*(food.ypos - block_ypos)) < (food.radius + block_radius + 3))
                block_xpos +=0.6;        
            if(sqrt((source.xpos - block_xpos)*(source.xpos - block_xpos) + (source.ypos - block_ypos)*(source.ypos - block_ypos)) < (source.radius + block_radius + 3))
                block_xpos +=0.6;        
        }
        if (key == GLUT_KEY_RIGHT)
        {    block_xpos += 0.6;
            if(sqrt((food.xpos - block_xpos)*(food.xpos - block_xpos) + (food.ypos - block_ypos)*(food.ypos - block_ypos)) < (food.radius + block_radius + 3))
                block_xpos -=0.6;        
            if(sqrt((source.xpos - block_xpos)*(source.xpos - block_xpos) + (source.ypos - block_ypos)*(source.ypos - block_ypos)) < (source.radius + block_radius + 3))
                block_xpos -=0.6;        
        }
        if (key == GLUT_KEY_UP)
        {
            block_ypos += 0.6;
            if(sqrt((food.xpos - block_xpos)*(food.xpos - block_xpos) + (food.ypos - block_ypos)*(food.ypos - block_ypos)) < (food.radius + block_radius + 3))
                block_ypos -=0.6;        
            if(sqrt((source.xpos - block_xpos)*(source.xpos - block_xpos) + (source.ypos - block_ypos)*(source.ypos - block_ypos)) < (source.radius + block_radius +3))
                block_ypos -=0.6;        

        }
        if (key == GLUT_KEY_DOWN)
        {
            block_ypos -= 0.6;
            if(sqrt((food.xpos - block_xpos)*(food.xpos - block_xpos) + (food.ypos - block_ypos)*(food.ypos - block_ypos)) < (food.radius + block_radius +3))
                block_ypos +=0.6;        
            if(sqrt((source.xpos - block_xpos)*(source.xpos - block_xpos) + (source.ypos - block_ypos)*(source.ypos - block_ypos)) < (source.radius + block_radius +3))
                block_ypos +=0.6;         
        }
    }
}

void handleMouseclick(int button, int state, int x, int y) 
{
    block_xpos=x;
    block_ypos=y;
}

}
