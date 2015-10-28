#include <stdio.h>
#include <math.h>

#include "Graphics.h"
#include "MapFile.h"

using namespace std;

typedef struct ssprite{
    int x;
    int y;
    int width;
    int height;
} Sprite;

typedef struct scamera{
	int x;
	int y;
} Camera;

Camera camera;

Graphics graphics; 
Image block1;
Image block2;
Image block_tiles;
Image sprite_sheet_scenario;

Sprite sprite_tile[9][3];
Sprite sprite_clouds[1][3];
Sprite sprite_bushes[1][3];
Sprite sprite_hills[1][2];

vector<vector<char>> mapFile;

void MainLoop()
{	
	float elapsed_time = graphics.GetElapsedTime();

	for(int y = 0; y < mapFile.size(); y++)
		for(int x = 0; x < mapFile[y].size(); x++)
		{
			if(mapFile[y][x] == '*')
				graphics.DrawImage2D(x * sprite_tile[4][0].width - camera.x,    //Position x
					600 - (y * sprite_tile[4][0].height) - sprite_tile[4][0].height - camera.y,  //Position y
					sprite_tile[4][0].width, // width
					sprite_tile[4][0].height, // height
					sprite_tile[4][0].x, // crop x
					sprite_tile[4][0].y, // crop y
					sprite_tile[4][0].width,  // crop width
					sprite_tile[4][0].height, // crop height
					block_tiles);
			else if(mapFile[y][x] == 'c'){
				graphics.DrawImage2D(x* 48 - camera.x, 600 - (y * 48) - 48 - camera.y, 
					sprite_clouds[0][2].width,
					sprite_clouds[0][2].height,
					sprite_clouds[0][2].x,
					sprite_clouds[0][2].y,
					sprite_clouds[0][2].width,
					sprite_clouds[0][2].height,
					sprite_sheet_scenario);
				}
				else if(mapFile[y][x] == 'h'){
					graphics.DrawImage2D(x* 48 - camera.x, 600 - (y * 48) - 48 - camera.y,
					sprite_hills[0][0].width,
					sprite_hills[0][0].height,
					sprite_hills[0][0].x,
					sprite_hills[0][0].y,
					sprite_hills[0][0].width,
					sprite_hills[0][0].height,
					sprite_sheet_scenario);
				}
			else if(mapFile[y][x] == 'b'){
					graphics.DrawImage2D(x* 48 - camera.x, 600 - (y * 48) - 48 - camera.y,
					sprite_bushes[0][0].width,
					sprite_bushes[0][0].height,
					sprite_bushes[0][0].x,
					sprite_bushes[0][0].y,
					sprite_bushes[0][0].width,
					sprite_bushes[0][0].height,
					sprite_sheet_scenario);
				}
			else if(mapFile[y][x] == '#')
				graphics.DrawImage2D(x* 48 - camera.x, 600 - (y * 48) - 48 - camera.y, 48, 48, block1);
			else if(mapFile[y][x] == '?')
				graphics.DrawImage2D(x* 48 - camera.x, 600 - (y * 48) - 48 - camera.y, 48, 48, block2);
		}


}

void InitTileSprites()
{
	int sprite_width = 48;
	int sprite_height = 48;

	int rows = 9;
	int cols = 3;

	int qt_images = rows * cols;

    int x = 0, y = 0;
    int spritex = 0;
    int spritey = 0;
    for (int w = 0; w < qt_images; w++)
    {
        sprite_tile[y][x].x = spritex;
        sprite_tile[y][x].y = spritey;
        sprite_tile[y][x].width = sprite_width;
        sprite_tile[y][x].height = sprite_height;
        spritex += sprite_width;
        x++;
        if (spritex >= sprite_width * cols)
        {      
            spritex = 0;
            spritey += sprite_height;
            y++;
            x = 0;
        }
    }
}

void InitScenarioSprites(){
	sprite_hills[0][0].x = 6;
    sprite_hills[0][0].y = 47;
    sprite_hills[0][0].width = 144;
    sprite_hills[0][0].height = 57;

	sprite_hills[0][1].x = 158;
    sprite_hills[0][1].y = 0;
    sprite_hills[0][1].width = 240;
    sprite_hills[0][1].height = 105;

	sprite_clouds[0][0].x = 0;
    sprite_clouds[0][0].y = 114;
    sprite_clouds[0][0].width = 144;
    sprite_clouds[0][0].height = 72;

	sprite_clouds[0][1].x = 150;
    sprite_clouds[0][1].y = 114;
    sprite_clouds[0][1].width = 192;
    sprite_clouds[0][1].height = 72;
	
	sprite_clouds[0][2].x = 349;
    sprite_clouds[0][2].y = 114;
    sprite_clouds[0][2].width = 96;
    sprite_clouds[0][2].height = 72;

	
	sprite_bushes[0][0].x = 14;
    sprite_bushes[0][0].y = 278;
    sprite_bushes[0][0].width = 96;
    sprite_bushes[0][0].height = 48;

	sprite_bushes[0][1].x = 117;
    sprite_bushes[0][1].y = 278;
    sprite_bushes[0][1].width = 192;
    sprite_bushes[0][1].height = 48;
	
	sprite_bushes[0][2].x = 315;
    sprite_bushes[0][2].y = 278;
    sprite_bushes[0][2].width = 144;
    sprite_bushes[0][2].height = 48;

}

void KeyboardInput(int key, int state, int x, int y)
{
  if ((key == 'f')&&(state == KEY_STATE_DOWN))
  {
    graphics.SetFullscreen(true);
  }
  if ((key == KEY_RIGHT)&&(state == KEY_STATE_DOWN))
  {
	  camera.x += 4;
  }  
  else if ((key == KEY_LEFT)&&(state == KEY_STATE_DOWN))
  {
	  camera.x -= 4;
  }  
  else if ((key == KEY_UP)&&(state == KEY_STATE_DOWN))
  {
	  camera.y += 4;
  }  
  else if ((key == KEY_DOWN)&&(state == KEY_STATE_DOWN))
  {
	  camera.y -= 4;
  }  

  if ((key == KEY_ESC)&&(state == KEY_STATE_DOWN))
  {
    exit(0);
  }	
}


int main (void)
{
	graphics.CreateMainWindow(800, 600, "Example MapFile");

	camera.x = 0;
	camera.y = 0;

	MapFile mf;
	mapFile = mf.Load("fase1.txt");

	graphics.SetBackgroundColor(93,148,251);
	block1.LoadPNGImage("block1.png");
	block2.LoadPNGImage("block2.png");
	block_tiles.LoadPNGImage("block_tiles.png");
	sprite_sheet_scenario.LoadPNGImage("scenario.png");

	InitTileSprites();
	InitScenarioSprites();

	graphics.SetKeyboardInput(KeyboardInput);
	graphics.SetMainLoop(MainLoop);
	graphics.StartMainLoop();

	return 0;
}
