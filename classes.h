class Food
{
    public:
        float radius;
        int quadrent;
        float xpos;
        float ypos;
        int finish;
        void drawFood(float xpos,float ypos,float radius);
        void setFood(float length_floor_x,float length_floor_y);
        Food()
        {
            finish=1;
        }
};
class Source
{
    public:
        int radius;
        int quadrent;
        float xpos;
        float ypos;
        int finish;
        void drawSource(float xpos,float ypos,float radius);
        void setSource(float length_floor_x,float length_floor_y,int quadrent);
        Source()
        {   
            finish=1;
        }   
};
class Ant
{
    public:
        float xpos;
        float ypos;
        float theta;
        int timer;
        int dead_flag;
        float legs;
	    bool check_food_once;
        vector <float> path_x;
        vector <float> path_y;
        vector <float> :: iterator it1,it2;
        
        vector <point> path;
        vector <point> reverse_path;
        vector <point> store_path;
        vector <point> :: iterator it_point,it_find,it_head,it_block;
        
        vector <float> unlooped_path_x;
        vector <float> unlooped_path_y;
        vector <float> path_theta;
        vector <float> reverse_path_theta;
        vector <float> store_path_theta;
        char mode[10];
        void setAnt();
        void drawHead(float xpos,float ypos,float radius);
        void draw_unloopedHead(float xpos,float ypos,float radius,int x);
        void drawTail(float xpos,float ypos,float radius,float theta);
        Ant()
        {
            xpos=0.0;
            ypos=0.0;
            theta=rand()%360;
            timer=rand()%timer_limit;
            strcpy(mode,"no_food");
	        check_food_once=0;
            dead_flag=0;
            legs=50;
        }
};
void initRendering();
void handleResize(int w, int h);
void drawScene();
void update(int value);
