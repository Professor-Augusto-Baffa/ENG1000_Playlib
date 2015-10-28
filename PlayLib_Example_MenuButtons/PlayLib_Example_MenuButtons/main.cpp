#include <stdio.h>
#include <math.h>

#include "Graphics.h"
#include "TextButtons.h"

Graphics graphics; 
bool key_states[256];



Button bt1;
Button bt2;

Size screen;
Position screen_middle;

Position points[28];


void KeyboardInput(int key, int state, int x, int y)
{
	if (state == KEY_STATE_DOWN)
		key_states[key] = true;
	else if (state == KEY_STATE_UP)
		key_states[key] = false;
}



void MouseClick(int button, int state, int xx, int yy){
	CheckMouseClick(&bt1, button, state, xx, yy);
}

int mousex = 0;
int mousey = 0;
void MouseOver(int xx, int yy){
	mousex = xx;
	mousey = yy;
	CheckMouseOver(&bt1, xx, yy);
}



void DrawButton(Button bt){

	UpdateButtonColor(bt);
	graphics.FillRectangle2D(bt.position.x, bt.position.y, bt.position.x + bt.size.width, bt.position.y + bt.size.height);

	graphics.SetColor(0,0,0);
	graphics.DrawText2D(bt.position.x + bt.text_position.x,bt.position.y + bt.text_position.y,bt.text);

}

void ExecuteButtonTag(int tag){
	graphics.SetBackgroundColor(0,0,0);
}

void VerticalAlignButton(Button *bt){
	(*bt).position.y = screen_middle.y - ((*bt).size.height / 2);
}

void HoritonzalAlignButton(Button *bt){
	(*bt).position.x = screen_middle.x - ((*bt).size.width / 2);
}

void UpdateCenteredObjects(){
	VerticalAlignButton(&bt1);
	//	HoritonzalAlignButton(&bt1);
}


void UpdateScreenSize(){
	screen.width = graphics.GetScreenWidth();
	screen.height = graphics.GetScreenHeight();

	screen_middle.x = screen.width / 2;
	screen_middle.y = screen.height / 2;

	UpdateCenteredObjects();
}




void MainLoop()
{	
	float elapsed_time = graphics.GetElapsedTime();

	DrawButton(bt1);

	if(screen.width != graphics.GetScreenWidth() ||
		screen.height != graphics.GetScreenHeight()){
			UpdateScreenSize();
	}
}
int main (void)
{
	graphics.CreateMainWindow(800, 600, "Ex. 06");

	bt1.position.x = 100;
	bt1.position.y = 100;
	bt1.size.width = 100;
	bt1.size.height = 50;
	bt1.color_normal.r = 255;
	bt1.color_normal.g = 0;
	bt1.color_normal.b = 0;
	bt1.color_over.r = 255;
	bt1.color_over.g = 255;
	bt1.color_over.b = 0;
	bt1.color_clicked.r = 0;
	bt1.color_clicked.g = 255;
	bt1.color_clicked.b = 255;
	bt1.text_position.x = 20;
	bt1.text_position.y = 15;
	bt1.text = "Teste";
	bt1.state = Button_State::normal;
	bt1.tag = 0;


	graphics.SetBackgroundColor(255,255,255);

	graphics.SetMouseClickInput(MouseClick);
	graphics.SetMouseMotionInput(MouseOver);

	graphics.SetKeyboardInput(KeyboardInput);
	graphics.SetMainLoop(MainLoop);
	graphics.StartMainLoop();

	return 0;
}
