#ifndef _include_uiobjects
#include "uiobjects.h"
#define _include_uiobjects
#endif


#ifndef _include_graphics
#include "graphics.h"
#include "Audio.h"
#define _include_graphics
#endif
/*
typedef struct scolor{
	int r;
	int g;
	int b;
} Color;


typedef struct sposition{
	float x;
	float y;
} Position;

typedef struct ssize{
	float width;
	float height;
} Size;
*/

enum Button_State{
	normal,
	clicked,
	over
};

typedef struct sbutton{
	Position position;
	Size size;
	Color color_normal;
	Color color_over;
	Color color_clicked;
	Position text_position;
	char *text;
	Button_State state;	
	int tag;
} Button;

void ExecuteButtonTag(int tag);


bool IsButtonCollision(Button* bt, int x, int y){
	return (x >= (*bt).position.x &&  x <= ((*bt).position.x + (*bt).size.width)
		&& y >= (*bt).position.y &&  y <= ((*bt).position.y + (*bt).size.height));
}

void CheckMouseClick(Button* bt, int button, int state, int xx, int yy){

	if(IsButtonCollision(bt,xx,yy) && state == KEY_STATE_DOWN)
		(*bt).state = Button_State::clicked;

	else if((*bt).state == Button_State::clicked && IsButtonCollision(bt,xx,yy) && state == KEY_STATE_UP){
		(*bt).state = Button_State::normal;
		ExecuteButtonTag((*bt).tag);
	}
}

void CheckMouseOver(Button* bt, int xx, int yy){

	if(IsButtonCollision(bt,xx,yy) && bt1.state != Button_State::clicked)
		(*bt).state = Button_State::over;

	else if(!IsButtonCollision(bt,xx,yy))
		(*bt).state = Button_State::normal;

}


void UpdateButtonColor(Button bt){
	if(bt.state == Button_State::normal)
		graphics.SetColor(bt.color_normal.r,bt.color_normal.g,bt.color_normal.b);
	else if(bt.state == Button_State::clicked)
		graphics.SetColor(bt.color_clicked.r,bt.color_clicked.g,bt.color_clicked.b);
	else if(bt.state == Button_State::over)
		graphics.SetColor(bt.color_over.r,bt.color_over.g,bt.color_over.b);
}