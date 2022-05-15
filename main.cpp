#include <time.h>
#include "main.h"
#include "screen.h"
#include "paddle.h"
#include "ball.h"
#include "blocks.h"

char uhrzeit[6] = {1, 2, 3, 0, 0, 0};
  int16_t last_hour = -1;
  int16_t last_min  = -1;
  int16_t last_sec  = -1;


short GameType = -1;

Screen * tft;
Paddle * paddle;
Ball * ball;
Blocks * blocks;
int16_t curBlock;

/**
 * The main game loop. Continues to loop until Escape or an SDL_Quit event occurs
 */
void main_loop()
{
  //static int rect_y=200;

  Get_Time();
  PlayArkonid();
  //tft->sleep(1);
      
}

void GetTime( int16_t &hour, int16_t &min, int16_t &sec) {

	time_t curr_time;
	curr_time = time(NULL);
	tm *tm_local = localtime(&curr_time);
 // printf("time %d\n",  tm_local->tm_hour);

  hour = tm_local->tm_hour;
  min  = tm_local->tm_min;
  sec = tm_local->tm_sec;


    uhrzeit[0] = hour / 10;
    uhrzeit[1] = hour % 10;
    uhrzeit[2] = min / 10;
    uhrzeit[3] = min % 10;
    uhrzeit[4] = sec / 10;
    uhrzeit[5] = sec % 10;
}

void Get_Time() {
  int16_t cur_hour;
  int16_t cur_min;
  int16_t cur_sec;
  GetTime( cur_hour,cur_min, cur_sec);
}

void CheckTime() {
  int16_t cur_hour;
  int16_t cur_min;
  int16_t cur_sec;
  GetTime( cur_hour,cur_min, cur_sec);

  if ((cur_hour != last_hour) || (cur_min != last_min)) {

    int16_t newgame = uhrzeit[2] % 6;  
  
  
  if (GameType <0) {  // ++GameType
      InitArkonid();
  }

  /*
  else {    
       if (newgame == 5)
        newgame =  random(5);  // new game between 0-5

       switch (newgame) {
        case Arkonoid:  // 0
          GameType = Arkonoid;
          InitArkonid();
          break;
        case Tetris: 
          GameType = Tetris;
          InitTetris();
          break;
        case Space_Invader: 
          if (GameType == Space_Invader)
            ResetInvaders();
          else  
            GameType = Space_Invader;
          InitInvaders();
          break;    
        case Pict_Clock: 
          GameType = Pict_Clock;
          InitClock();
          break;
        case Pacman:  
          GameType = Pacman;
          pacman_init(tft);
          break;

        case 5: 
          GameType = Pacman;  // random?
          pacman_init(tft);
          break;                
        default:
          // nothing 
          ;
        }  
  }     
  */
    last_hour = cur_hour;
    last_min = cur_min;
    last_sec = cur_sec;

  }
}

int main(int argc, char* argv[])
{
    Get_Time();
    tft = new Screen();
    paddle = new Paddle(tft);
    ball = new Ball(tft);
    ball->setAngle(37);
    blocks = new Blocks(tft);

    InitArkonid();

    SDL_Event event;
    int FPS = 100; //Framerate

    while (1) {
          Uint32 start_time = SDL_GetTicks();
          if (tft->event())
              break;

          main_loop();
          if((1000/FPS)>(SDL_GetTicks()-start_time))
          {
            SDL_Delay((1000/FPS)-(SDL_GetTicks()-start_time)); //Yay stable framerate!
          }
    }


    return 0;
}


void InitArkonid() {
    SetGame(Arkonoid, 7);

    tft->fillScreen(ILI9486_BLACK);
    blocks->setColor(ILI9486_YELLOW);
    paddle->setType(true);
    paddle->draw();
 
    ball->SetY(20);
    blocks->Setup(uhrzeit);
    blocks->draw();

    tft->doRender();
}

void PlayArkonid() {
  tft->fillScreen(ILI9486_BLACK);

  //paddle->update(300); //ball->GetX());
  //tft->fillRect(loop+100, rect_y+10, 50, 50, ILI9486_YELLOW);
  //paddle->setX(loop+200);
  //paddle->draw();
  //paddle->update(loop);
  blocks->draw();
  curBlock = ball->move_draw();  
  blocks->checkBall(ball);
   
  paddle->update(ball->GetX());
  blocks->draw(ball);

  tft->doRender();
}
