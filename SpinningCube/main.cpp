#include <math.h>
#include <SDL.h>

/*
											Commands:
	Use numbers from 1 to 9 to control the cube rotation, or 0 to reset the cube to the initial position.
							
						7	8	9		 x++    x    x--
						4	5	6		 y++    y    y--
						1	2	3		 z++	z    z--
							0		   x = 0, y = 0, z = 0
							
						Use the mousewheel to zoom in or zoom out the cube.							
*/

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

const SDL_Color Black = {0x00, 0x00, 0x00};
const SDL_Color White = {0xff, 0xff, 0xff};
const SDL_Color Red = {0xff, 0x00, 0x0};
const SDL_Color Green = {0x00, 0xff, 0x00};
const SDL_Color Blue = {0x00, 0x00, 0xff};
const SDL_Color Yellow = {0xff, 0xff, 0x00};
const SDL_Color Orange = {0xff, 100, 0x00};
const SDL_Color Pink = {0xff, 0x00, 0xff};
const SDL_Color Aqua = {0x00, 0xff, 0xff};

const int WindowWidth = 900, WindowHeight = WindowWidth;
const int Hw = WindowWidth / 2, Hh = Hw;
int Scale =  WindowWidth / (2 * 3.6);

void DrawPix(int x, int y, SDL_Color Col){
	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * WindowWidth + x) * 4;
	*(pixel_ptr + 2) = Col.r;
	*(pixel_ptr + 1) = Col.g;
	*(pixel_ptr) = Col.b;
}

void DrawLine(int x0, int y0, int x1, int y1, SDL_Color Col){
	int i;
    double x = x1 - x0; 
	double y = y1 - y0; 
	double length = sqrt(x * x + y * y); 
	double addx = x / length; 
	double addy = y / length; 
	x = x0; 
	y = y0; 
	for (i = 0; i < length; i += 1){ 
		DrawPix(x, y, Col); 
		x += addx;
		y += addy;		
	} 
}

bool IsBlack(int x, int y){
	Uint8* pixel_ptr = (Uint8*)surface->pixels + (y * WindowWidth + x) * 4;
	if(	*(pixel_ptr + 2) == 0x00 && *(pixel_ptr + 1) == 0x00 && *(pixel_ptr) == 0x00)
		return true;
	else
		return false;
}

class Cube{
	public:
		Cube();
		float CalculateX(int, int, int);
		float CalculateY(int, int, int);
		void Movement(char, float&);
		void Draw(SDL_Color);
	// 	x, y, z angles
		float A, B, C;
	private:
	//	Cube's vertices coord
		const int Points[8][3] = {
			{-1, -1,  1},
			{ 1, -1,  1},
			{ 1,  1,  1},
			{-1,  1,  1},
			{-1, -1, -1},
			{ 1, -1, -1},
			{ 1,  1, -1},
			{-1,  1, -1}
		};
};

Cube::Cube(){
	A = B = C = 0;
}

float Cube::CalculateX(int x, int y, int z){
  	return (y * sin(A) * sin(B) * cos(C) - z * cos(A) * sin(B) * cos(C) + y * cos(A) * sin(C) + z * sin(A) * sin(C) + x * cos(B) * cos(C)) * Scale + Hw;
}

float Cube::CalculateY(int x, int y, int z){
  	return (y * cos(A) * cos(C) + z * sin(A) * cos(C) - y * sin(A) * sin(B) * sin(C) + z * cos(A) * sin(B) * sin(C) - x * cos(B) * sin(C)) * Scale + Hh;
}

void Cube::Movement(char Move, float &Angle){
	switch(Move){
		case 0:
			break;
		case 1:
			Angle += 0.05;
			break;
		case 2:
			Angle -= 0.05;
			break;
	}
}

void Cube::Draw(SDL_Color Col){
	DrawLine(CalculateX(Points[0][0], Points[0][1], Points[0][2]), CalculateY(Points[0][0], Points[0][1], Points[0][2]), CalculateX(Points[1][0], Points[1][1], Points[1][2]), CalculateY(Points[1][0], Points[1][1], Points[1][2]), Col);
	DrawLine(CalculateX(Points[0][0], Points[0][1], Points[0][2]), CalculateY(Points[0][0], Points[0][1], Points[0][2]), CalculateX(Points[3][0], Points[3][1], Points[3][2]), CalculateY(Points[3][0], Points[3][1], Points[3][2]), Col);
	DrawLine(CalculateX(Points[0][0], Points[0][1], Points[0][2]), CalculateY(Points[0][0], Points[0][1], Points[0][2]), CalculateX(Points[4][0], Points[4][1], Points[4][2]), CalculateY(Points[4][0], Points[4][1], Points[4][2]), Col);	
	DrawLine(CalculateX(Points[1][0], Points[1][1], Points[1][2]), CalculateY(Points[1][0], Points[1][1], Points[1][2]), CalculateX(Points[2][0], Points[2][1], Points[2][2]), CalculateY(Points[2][0], Points[2][1], Points[2][2]), Col);
	DrawLine(CalculateX(Points[1][0], Points[1][1], Points[1][2]), CalculateY(Points[1][0], Points[1][1], Points[1][2]), CalculateX(Points[5][0], Points[5][1], Points[5][2]), CalculateY(Points[5][0], Points[5][1], Points[5][2]), Col);
	DrawLine(CalculateX(Points[2][0], Points[2][1], Points[2][2]), CalculateY(Points[2][0], Points[2][1], Points[2][2]), CalculateX(Points[6][0], Points[6][1], Points[6][2]), CalculateY(Points[6][0], Points[6][1], Points[6][2]), Col);
	DrawLine(CalculateX(Points[2][0], Points[2][1], Points[2][2]), CalculateY(Points[2][0], Points[2][1], Points[2][2]), CalculateX(Points[3][0], Points[3][1], Points[3][2]), CalculateY(Points[3][0], Points[3][1], Points[3][2]), Col);
	DrawLine(CalculateX(Points[3][0], Points[3][1], Points[3][2]), CalculateY(Points[3][0], Points[3][1], Points[3][2]), CalculateX(Points[7][0], Points[7][1], Points[7][2]), CalculateY(Points[7][0], Points[7][1], Points[7][2]), Col);
	DrawLine(CalculateX(Points[4][0], Points[4][1], Points[4][2]), CalculateY(Points[4][0], Points[4][1], Points[4][2]), CalculateX(Points[5][0], Points[5][1], Points[5][2]), CalculateY(Points[5][0], Points[5][1], Points[5][2]), Col);
	DrawLine(CalculateX(Points[4][0], Points[4][1], Points[4][2]), CalculateY(Points[4][0], Points[4][1], Points[4][2]), CalculateX(Points[7][0], Points[7][1], Points[7][2]), CalculateY(Points[7][0], Points[7][1], Points[7][2]), Col);
	DrawLine(CalculateX(Points[6][0], Points[6][1], Points[6][2]), CalculateY(Points[6][0], Points[6][1], Points[6][2]), CalculateX(Points[5][0], Points[5][1], Points[5][2]), CalculateY(Points[5][0], Points[5][1], Points[5][2]), Col);
	DrawLine(CalculateX(Points[6][0], Points[6][1], Points[6][2]), CalculateY(Points[6][0], Points[6][1], Points[6][2]), CalculateX(Points[7][0], Points[7][1], Points[7][2]), CalculateY(Points[7][0], Points[7][1], Points[7][2]), Col);			
}

int main(int argc, char* argv[]){

	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("SpinningSquare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);

	Cube Cube;
	
	char MoveA = 1, MoveB = 1, MoveC = 1;
	bool MoveReset = false;
	
	int ChangeScale = Scale;
	
	SDL_Event event;
	
	bool quit = false;
	
	while (!quit){
		
		while (SDL_PollEvent(&event) != 0){
			
			if(event.type == SDL_QUIT)
				quit = true;
			
        	if(event.type == SDL_MOUSEWHEEL){
        		if(event.wheel.y > 0)
        			if(ChangeScale < WindowWidth / 3.6)
             			ChangeScale += 5;
        		if(event.wheel.y < 0)
        			if(ChangeScale > 5)
        				ChangeScale -= 5;
			}

			if(event.key.state == SDL_PRESSED){
				if(event.key.keysym.sym == SDLK_9 || event.key.keysym.sym == SDLK_KP_9)
					MoveA = 2;
				if(event.key.keysym.sym == SDLK_8 || event.key.keysym.sym == SDLK_KP_8)
					MoveA = 0;
				if(event.key.keysym.sym == SDLK_7 || event.key.keysym.sym == SDLK_KP_7)
					MoveA = 1;			
			 	if(event.key.keysym.sym == SDLK_6 || event.key.keysym.sym == SDLK_KP_6)
					MoveB = 1;		
				if( event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP_5)	
					MoveB = 0;			
				if(event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP_4)
					MoveB = 2;				
				if(event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP_3)
					MoveC = 2;
				if(event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_2)
					MoveC = 0;
			    if(event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_1)
			    	MoveC = 1;
				if(event.key.keysym.sym == SDLK_0 || event.key.keysym.sym == SDLK_KP_0)
					MoveReset = true;
			}
			
		}
		
	// 	Erase old cube
		for(int i = 0; i < WindowWidth; i++){
			for(int j = 0; j < WindowHeight; j++){
				if(!IsBlack(i, j))
					DrawPix(i, j, Black);
			}
		}
		
		Cube.Movement(MoveA, Cube.A);
		Cube.Movement(MoveB, Cube.B);
		Cube.Movement(MoveC, Cube.C);
		
		if(MoveReset){
			Cube.A = Cube.B = Cube.C = 0;
			MoveA = MoveB = MoveC = 0;
			MoveReset = false;
		}
	    
		SDL_Delay(50);
	
		Scale = ChangeScale;
		
		Cube.Draw(Aqua);

		SDL_UpdateWindowSurface(window);
	
	}
	
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window); 	
	SDL_Quit();   
	
	return 0;
	
}
