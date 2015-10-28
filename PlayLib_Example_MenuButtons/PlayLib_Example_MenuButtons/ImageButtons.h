#ifndef _include_uiobjects
#include "uiobjects.h"
#define _include_uiobjects
#endif


#ifndef _include_graphics
#include "graphics.h"
#include "Audio.h"
#define _include_graphics
#endif


enum Button_State{
        normal,
        clicked,
        over 
};

typedef struct button
{
        Position position;
        Size size;
        Button_State state;
        Image img_normal;
        Image img_clicked;
        Image img_over;
        int tag;
} Button;

void ExecuteButtonTag(int tag);


void CheckMouseClick(Button* bt, int button, int state, int x, int y){

        if(IsCollision((*bt).position, (*bt).size, x, y) && button == MOUSE_LEFT_BUTTON && state == KEY_STATE_DOWN)
                (*bt).state = Button_State::clicked;

        else if(IsCollision((*bt).position, (*bt).size, x, y) && (*bt).state == Button_State::clicked && button == MOUSE_LEFT_BUTTON && state == KEY_STATE_UP)
        {
                (*bt).state = Button_State::normal;
                ExecuteButtonTag((*bt).tag);
        }
}

void CheckMouseOver (Button* bt, int xx, int yy)
{
        if(IsCollision((*bt).position, (*bt).size, xx, yy) && (*bt).state != Button_State::clicked){
                (*bt).state = Button_State::over;
        }
        else if(!IsCollision((*bt).position, (*bt).size, xx, yy) && (*bt).state != Button_State::normal)
        {
                (*bt).state = Button_State::normal;
        }

}


void DrawButton(Button* bt, Graphics graphics){

                Image img;

                if((*bt).state == Button_State::clicked) 
                        img = (*bt).img_clicked;
				else if((*bt).state == Button_State::over)
                        img = (*bt).img_over;
                else
                        img = (*bt).img_normal;

                graphics.DrawImage2D((*bt).position.x, (*bt).position.y, (*bt).size.width,
(*bt).size.height, img); 
}

void HorizontalAlignButton(Button* bt){
	(*bt).position.x = middle.x - ((*bt).size.width / 2);
}

