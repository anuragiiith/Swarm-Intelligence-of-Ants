void Food::drawFood(float xPos, float yPos, float radius)
{
	glPushMatrix();
	glTranslatef(xPos, yPos,5.0);
	glColor3f(0.3f, 0.1f, 0.2f);
	glVertex2d(0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);

	double theta;
	for (int a = 0; a < 360; a+=5 )
	{
		theta = a * 3.1415/180;
		glVertex2d (cos(theta) * radius , sin(theta) * radius);
	}
	glEnd();
	glBegin(GL_LINE_LOOP);  
	for (int a = 0; a < 360; a+=5 )
	{
		theta = a * 3.1415/180;
		glVertex2d (cos(theta) * (radius+3.0) , sin(theta) * (radius+3.0));
	}
	glEnd();
	glPopMatrix();

}
void Food::setFood(float length_floor_x,float length_floor_y)
{
	length_floor_x-=8.0;
	length_floor_y-=8.0;
	if(finish==1)
	{
		quadrent=(rand())%4;
		xpos=(rand()%(int)length_floor_x)/2;
		ypos=(rand()%(int)length_floor_y)/2;
		if(quadrent==1 || quadrent==2)
			xpos+=length_floor_x/2;
		if(quadrent==2 || quadrent==3)
			ypos+=length_floor_y/2;
		radius=rand()%2+2;
        radius=5;
		xpos-=length_floor_x/2;
		ypos-=length_floor_y/2;
        finish=0;
	}
	drawFood(xpos,ypos,radius);
}
void Source::drawSource(float xPos, float yPos, float radius)
{
	glPushMatrix();
	glTranslatef(xPos, yPos,5.0);
	glColor3f(0.0f,0.0f, 0.0f);
	glVertex2d(0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);

	double theta;
	for (int a = 0; a < 360; a+=5 )
	{
		theta = a * 3.1415/180;
		glVertex2d (cos(theta) * radius , sin(theta) * radius);
    }
    glEnd();
    glBegin(GL_LINE_LOOP);
    for (int a = 0; a < 360; a+=5 )
    {
        theta = a * 3.1415/180;
        glVertex2d (cos(theta) * (radius+3.0) , sin(theta) * (radius+3.0));
    }
    glEnd();

	glPopMatrix();

}
void Source::setSource(float length_floor_x,float length_floor_y,int quadrent)
{
	length_floor_x-=8.0;
	length_floor_y-=8.0;
	if(finish==1)
	{   
		xpos=(rand()%(int)length_floor_x)/2;
		ypos=(rand()%(int)length_floor_y)/2;
		if(quadrent==1 || quadrent==2)
			xpos+=length_floor_x/2;
		if(quadrent==2 || quadrent==3)
			ypos+=length_floor_y/2;
		radius=rand()%3+1;
		xpos-=length_floor_x/2;
		ypos-=length_floor_y/2;
		finish=0;
	}   
	drawSource(xpos,ypos,radius_source);
}
void Ant::drawHead(float xPos,float yPos,float radius)
{
	glPushMatrix();
	glTranslatef(xPos, yPos,5.0);
	glColor3f(1.0f,1.0f, 0.0f);
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
void drawCircle(float xpos,float ypos,float radius)
{
    glPushMatrix();
    glTranslatef(xpos, ypos,5.0);
    glColor3f(0.0f,1.0f, 0.0f);
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
void Ant::draw_unloopedHead(float xPos,float yPos,float radius,int x)
{
    glPushMatrix();
    glTranslatef(xPos, yPos,5.0);
    float intensity=(float)x;
    float X=intensity/100.00;
    glColor3f(X*1.0f,0.0f, 0.0f);
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
void Ant::drawTail(float xPos,float yPos,float radius,float theta2)
{
	glPushMatrix();
	glTranslatef(xPos, yPos,5.0);
	if(strcmp(mode,"with_food")==0)
        glColor3f(0.0f,0.7f, 0.0f);
    else
        glColor3f(0.7f,0.0f, 0.0f);
	glVertex2d(0.0,0.0);
	glBegin(GL_TRIANGLE_FAN);

	double theta1;
	for (int a = 0; a < 360; a+=5 )
	{
		theta1 = a * 3.1415/180;
		glVertex2d (cos(theta1) * radius , sin(theta1) * radius);
	}
	glEnd();
    glBegin(GL_LINES);
    glLineWidth(5); 
    glColor3f(0.0f,0.0f,0.0f);
    theta2+=45.0;
    if(legs>25)
    {
        legs--;
        legs=0;
    }
    else
    {
        legs--;
        if(legs==0)
            legs=50;
    }
    glEnd();
	glPopMatrix();
}
bool operator ==(point a1,point a2){
	return (a1.x>a2.x-0.5 && a1.x<a2.x+0.5 &&  a1.y<a2.y+0.5 && a1.y > a2.y-0.5);
}
void Ant::setAnt()
{
    if(strcmp(mode,"within_range")==0)
    {
            if(!((xpos-food.xpos<0.1 && xpos-food.xpos>-0.1) && (ypos-food.ypos<0.1 && ypos-food.ypos>-0.1)))
            {
                float per=(food.ypos-ypos);
                float bas=(food.xpos-xpos);
                float hyp=sqrt(per*per + bas* bas);
                xpos += (bas/hyp)*0.1;
                ypos += (per/hyp)*0.1;
                struct point p;
                p.x=xpos;
                p.y=ypos;
                theta=RAD2DEG(atan(per/bas)) + ((bas<0.0)?180.00:0.0);
                path.push_back(p);
                path_theta.push_back(theta);
            }
            else
            {
                message="Food found";
                message_counter=20;
                strcpy(mode,"with_food");
            }
    }
	if(strcmp(mode,"no_food")==0)
	{
		if((xpos-food.xpos)*(xpos-food.xpos) + (ypos-food.ypos)*(ypos-food.ypos) < food.radius*food.radius)
		{	
                message="Detected Smell";
                message_counter=20;

			strcpy(mode,"within_range");
            food.radius -= (5.0/((float)number_of_ants));
			it_point=path.begin();
			it1=path_theta.begin();
			while(it_point!=path.end())
			{
				it_head=it_point;
				it_head=it_head+20;
				if(it_head==path.end())
					break;
				it_find=find(it_head,path.end(),*it_point);
				if(it_find!=path.end())
				{
					path.erase(it_point,it_find);
					path_theta.erase(it1,it1 + (it_find-it_point));
				}
                it_point++;
                it1++;
            }
		}
		else
        {
            for(outer_iter itr=mymap.begin(); itr!=mymap.end(); ++itr) 
            {
                if(itr->second > 0)
                {
                    if(abs(xpos - itr->first.first) <0.2 && abs(ypos - itr->first.second)<0.2)
                    {
                        flag_pheromone=1;
                        break;
                    }
                }
            }
            if(flag_pheromone==1)
            {
                for(int i=0;i<number_of_ants;i++)
                {
                    if(ant[i].check_food_once==1 && ant[i].dead_flag==0)
                    {
                        for(j=0;j<ant[i].store_path.size();j++)
                        {
                            reverse_path.push_back(ant[i].store_path[j]);
                            reverse_path_theta.push_back(ant[i].store_path_theta[j]);
                            if(abs(xpos - ant[i].store_path[j].x) <0.4 && abs(ypos - ant[i].store_path[j].y)<0.4)
                            {

                                flag_pheromone=0;
                                break;
                            }
                        }
                        if(flag_pheromone==0)
                        {
                            for(k=ant[i].store_path.size()-1;k!=j;k--)
                            {
                                path.push_back(ant[i].store_path[k]);
                                path_theta.push_back(ant[i].store_path_theta[k] + 180);
                            }
                            strcpy(mode,"go_to_food");
                            break;
                        }
                        else
                        {
                            reverse_path.clear();
                            reverse_path_theta.clear();
                        }
                    }
                    if(flag_pheromone==0)
                        break;
                }
            }
            else
                strcpy(mode,"no_food");
        }        
    }
    if(strcmp(mode,"no_food")==0)
    {
        timer--;
        if(timer<=0)
        {
			theta=(int)(theta + rand()%30 - 15)%360;
			timer=timer_limit;
		}
		if(xpos>length_floor_x/2 || ypos>length_floor_y/2 || xpos<-length_floor_x/2 || ypos<-length_floor_y/2)
		{
			theta=180+theta;
		}
		xpos = xpos +cos(DEG2RAD(theta))*0.1;
		ypos = ypos +sin(DEG2RAD(theta))*0.1;
        if(((xpos-block_xpos)*(xpos-block_xpos)+(ypos-block_ypos)*(ypos-block_ypos))<=(block_radius*block_radius))
        {
            theta=theta+180;
		    xpos = xpos +cos(DEG2RAD(theta))*0.1;
		    ypos = ypos +sin(DEG2RAD(theta))*0.1;
        }
		path_x.push_back(xpos);
		path_y.push_back(ypos);

		struct point p;
		p.x=xpos;
		p.y=ypos;
		path.push_back(p);
		path_theta.push_back(theta);
	}
	if(strcmp(mode,"with_food")==0)
	{
		reverse_path.push_back(path.back());				// store path from food to source.
		reverse_path_theta.push_back(path_theta.back() + 180);
		if(check_food_once==0)
		{
		store_path.push_back(path.back());
		store_path_theta.push_back(path_theta.back() +180);
		}

		xpos=path.back().x;
		ypos=path.back().y;
        float txpos,typos;
        
        if(((xpos-block_xpos)*(xpos-block_xpos)+(ypos-block_ypos)*(ypos-block_ypos))<=(block_radius*block_radius))
        {
            it_point=path.end();
            it1=path_theta.end();
            it1--;
            it1--;
            it_point--;
            it_point--;
            for(it_block=it_point;it_block!=path.begin();it_block--)
            {
                txpos=(*it_block).x;
                typos=(*it_block).y;
                it1--;
                if(!(((txpos-block_xpos)*(txpos-block_xpos)+(typos-block_ypos)*(typos-block_ypos))<=(block_radius*block_radius)))
                    break;
            }
            it1++;
        path.erase(it_block,path.end());
        path_theta.erase(it1,path_theta.end());
        int N=path.size();
        while(((xpos-txpos)*(xpos-txpos) + (ypos-typos)*(ypos-typos))>0.4)
        {
            float per=(ypos-block_ypos);
            float bas=(xpos-block_xpos);
            float hyp=sqrt(per*per + bas* bas);
            float pre_x=xpos;
            float pre_y=ypos;
                xpos += (per/hyp)*0.1;
                ypos -= (bas/hyp)*0.1;
            struct point p;
            p.x=xpos;
            p.y=ypos;
            per=ypos-pre_y;
            bas=xpos-pre_x;
            theta=RAD2DEG(atan(per/bas)) + ((bas>0.0)?180.00:0.0);
            path.push_back(p);
            path_theta.push_back(theta);
        }
        int N1=path.size();
        for(int i=N1-1;i>(N1+N+2)/2;i--)
        {
            point temp=path[i];
            path[i]=path[N1-i+N+1];
            path[N1-i+N-1]=temp;
            float temp1=path_theta[i];
            path_theta[i]=path_theta[N1-i+N-1];
            path_theta[N1-i+N-1]=temp1;
        }
        }
       
		xpos=path.back().x;
		ypos=path.back().y;
        mymap[make_pair(xpos,ypos)]+=100;
        theta=180 + path_theta.back();
		path.pop_back();
		path_theta.pop_back();
	}
	if((strcmp(mode,"with_food")==0) && ((xpos-source.xpos)*(xpos-source.xpos) + (ypos-source.ypos)*(ypos-source.ypos) < source.radius*source.radius))
	{
		strcpy(mode,"at_source");
		check_food_once=1;
	}
	if(strcmp(mode,"at_source")==0)
	{
		unsigned int max=100000,index;
		for(int i=0;i<number_of_ants;i++)
		{
			if(ant[i].check_food_once==1 && ant[i].dead_flag==0)
			{
				if(ant[i].store_path.size() < max)
				{
					max=ant[i].store_path.size();
					index=i;
                }
            }
        }
        reverse_path=ant[index].store_path;
        reverse_path_theta=ant[index].store_path_theta;
        strcpy(mode,"go_to_food");

        path.clear();
        path_theta.clear();
    }
    if(strcmp(mode,"go_to_food")==0)
    {
        path.push_back(reverse_path.back());
        path_theta.push_back(reverse_path_theta.back() + 180);

        xpos=reverse_path.back().x;
        ypos=reverse_path.back().y;


        float txpos,typos;

        if(((xpos-block_xpos)*(xpos-block_xpos)+(ypos-block_ypos)*(ypos-block_ypos))<=(block_radius*block_radius))
        {

            it_point=reverse_path.end();
            it1=reverse_path_theta.end();
            it1--;
            it1--;
            it_point--;
            it_point--;
            for(it_block=it_point;it_block!=reverse_path.begin();it_block--)
            {
                txpos=(*it_block).x;
                typos=(*it_block).y;
                it1--;
                if(!(((txpos-block_xpos)*(txpos-block_xpos)+(typos-block_ypos)*(typos-block_ypos))<=(block_radius*block_radius)))
                    break;
            }
            it1++;
            reverse_path.erase(it_block,reverse_path.end());
            reverse_path_theta.erase(it1,reverse_path_theta.end());
            int N=reverse_path.size();
            while(((xpos-txpos)*(xpos-txpos) + (ypos-typos)*(ypos-typos))>0.2)
            {
                float per=(ypos-block_ypos);
                float bas=(xpos-block_xpos);
                float hyp=sqrt(per*per + bas* bas);
                float pre_x=xpos;
                float pre_y=ypos;
                xpos += (per/hyp)*0.1;
                ypos -= (bas/hyp)*0.1;
                struct point p;
                p.x=xpos;
                p.y=ypos;
                per=ypos-pre_y;
                bas=xpos-pre_x;
                theta=RAD2DEG(atan(per/bas)) + ((bas>0.0)?180.00:0.0);
                reverse_path.push_back(p);
                reverse_path_theta.push_back(theta);
            }
            int N1=reverse_path.size();
            for(int i=N1-1;i>(N1+N+2)/2;i--)
            {
                point temp=reverse_path[i];
                reverse_path[i]=reverse_path[N1-i+N+1];
                reverse_path[N1-i+N-1]=temp;
                float temp1=reverse_path_theta[i];
                reverse_path_theta[i]=reverse_path_theta[N1-i+N-1];
                reverse_path_theta[N1-i+N-1]=temp1;
            }
        }

        xpos=reverse_path.back().x;
        ypos=reverse_path.back().y;

        mymap[make_pair(xpos,ypos)]+=100;
		
		theta=180 + reverse_path_theta.back();
		reverse_path.pop_back();
		reverse_path_theta.pop_back();

	}
	if((strcmp(mode,"go_to_food")==0) && ((xpos-food.xpos)*(xpos-food.xpos) + (ypos-food.ypos)*(ypos-food.ypos) < 0.2))
	{
		strcpy(mode,"with_food");
        food.radius--;
		reverse_path.clear();						// Clear the path from food to source
		reverse_path_theta.clear();

	}
	drawHead(xpos+radius_head*cos(DEG2RAD(theta)),ypos+radius_head*sin(DEG2RAD(theta)),radius_head);
	drawTail(xpos+radius_tail*cos(DEG2RAD((int)(180+theta)%360)),ypos+radius_tail*sin(DEG2RAD((int)(180+theta)%360)),radius_tail,theta);

}
