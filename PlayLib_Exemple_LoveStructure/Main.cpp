#include "Graphics.h"

Graphics graphics;

void load(void)
{
	graphics.SetBackgroundColor(255,255,255);
}

void update(float dt)
{
	
}

void draw(void)
{
	
}

void MainLoop(void){
	float dt = graphics.GetElapsedTime();
	draw();
	update(dt);
}

int main (void)
{
	graphics.CreateMainWindow(800, 600, "Projeto Exemplo");
	load();	
	graphics.SetMainLoop(MainLoop);
	graphics.StartMainLoop();

	return 0;
}
