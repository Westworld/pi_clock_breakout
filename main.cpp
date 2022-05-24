#include <time.h>
#include "main.h"
#include "screen.h"
#include "paddle.h"
#include "ball.h"
#include "blocks.h"
#include "shot.h"
#include "TetrisMatrixDraw.h"

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
// Invaders
  int16_t invaders_move_x, invaders_move_y;
  int16_t invaders_domovex, invaders_domovey;
  int16_t invaders_loopx, invaders_blockcounter;
  int32_t invaders_maxxloop, invaders_loopcounter;
  Shot * shotup;
  Shot * shotdown;

  // Tetris
  bool twelveHourFormat = true;
  bool forceRefresh = true;
  TetrisMatrixDraw * tetris;


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
    shotup = new Shot(tft, 8);
    shotdown = new Shot(tft, -8);

    tetris = new TetrisMatrixDraw(tft);

    //InitArkonid();
    //InitInvaders();
    InitTetris();

    SDL_Event event;
    int FPS = 100; //Framerate

    while (1) {
          Uint32 start_time = SDL_GetTicks();
          if (tft->event())
              break;

          Get_Time();
          //PlayArkonid();
          //PlayInvaders();
          PlayTetris();
          if((1000/FPS)>(SDL_GetTicks()-start_time))
          {
            SDL_Delay((1000/FPS)-(SDL_GetTicks()-start_time)); //Yay stable framerate!
          }
    }


    return 0;
}


void InitArkonid() {
    tft->doRotate(false);
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

void InitInvaders() {
  tft->doRotate(false);
  tft->reset();
  tft->fillScreen(ILI9486_BLACK);
  SetGame(Space_Invader, 7);

   Get_Time();
   blocks->setColor(TFT_WHITE);
   paddle->setType(false);
   paddle->setX(tft->getwidth()/2);
   paddle->draw();
   blocks->Setup(uhrzeit);
   blocks->draw();
   shotup->deactivate();
   shotdown->deactivate();

  invaders_move_x = 0, invaders_move_y = 0;
  invaders_domovex = -5, invaders_domovey = 0;

  invaders_loopcounter = 0, invaders_loopx = 0, invaders_blockcounter = 0;
  invaders_maxxloop = 31 * numberblocks * 15;  // 24000
  tft->doRender();
}

void ResetInvaders() {
   // new game, stop old. Mark all surviving blocks red!
  blocks->ClearSurvivingBlocks(invaders_move_x, invaders_move_y);
  SDL_Delay(1000);
}

void PlayInvaders() {

tft->fillScreen(ILI9486_BLACK);  

for (int frameloop=0;frameloop<8;frameloop++) {

  if (invaders_loopcounter < invaders_maxxloop) {
      if (invaders_blockcounter <=numberblocks) {
        blocks->move(0, 0, invaders_blockcounter++, invaders_domovex, invaders_domovey);
      }
      else {
          invaders_blockcounter = 0;
          invaders_move_x += invaders_domovex;
          if (invaders_domovey != 0) {
            invaders_move_y -= 15;
            invaders_domovey = 0;
          } 

        if (++invaders_loopx >=31 ) {
            invaders_loopx = 0;
            invaders_domovey = -15;
            invaders_domovex = -invaders_domovex;
        }  
      }

      invaders_loopcounter++;

      if ((invaders_loopcounter % 30) == 1 ) {
        if (!shotup->move_draw()) {
            shotup->activate(paddle->getX(), 20, false);
          // new shot up, set x depending of paddle, which sets ative again      
        }


        if (!shotdown->move_draw()) {  
            int16_t x, y;
            blocks->findNearestBlock(x, y, paddle->getX());
            if (x != 0)
              shotdown->activate(x, y, true);
        } 

            // move paddle to follow lowest block, avoid shotdown
            // first check if shot is coming down, if yes move left/right (opposite of shot)
        int16_t x, paddlex;    
        x=shotdown->getX();
        paddlex = paddle->getX();
        if (x > 0)  {
          //paddle->undraw();
          if (x>paddlex)  {
            paddle->move(-1);
          }  
          else {
            paddle->move(1);
          }  
          //paddle->draw();  
        }
        else {
          // no risk being hit, but do we have a block above us or do we need to move?
          paddlex = paddle->getX();
          x = blocks->findNearestBlock(paddlex);
  
          if (x != 0) {  
            //paddle->undraw();  
            if (x < 0)  
              paddle->move(-2);
            else
              paddle->move(2);
            
          }  
        }
      }
      else {
        shotup->draw();
        shotdown->draw();
      }

      if (blocks->checkShot(shotup->getX(), shotup->getY(true))) 
        {  // check hit on block 
              shotup->deactivate();
        }
    }
  }
  paddle->draw(); 
  blocks->draw();
  tft->doRender();
}

void InitTetris() {
  tft->doRotate(true);
  tft->reset();
  tft->fillScreen(ILI9486_BLACK);
  char timeString [8];
  sprintf(timeString, "%d%d:%d%d", uhrzeit[0], uhrzeit[1], uhrzeit[2], uhrzeit[3]);
  tetris->setTime(timeString);

  bool displaycolon = false;
  while(!(tetris->drawNumbers(60,500, displaycolon))) {
    if (tft->event())
      break;
    Get_Time();
    displaycolon = ((uhrzeit[5] % 2) == 1);
    SDL_Delay(50);
    tft->doRender();
    tft->fillScreen(ILI9486_BLACK);
  }
}

void PlayTetris() {
  tft->fillScreen(ILI9486_BLACK);  
  bool displaycolon = ((uhrzeit[5] % 2) == 1);
  tetris->drawNumbers(60,500, displaycolon);
  tft->doRender();
}