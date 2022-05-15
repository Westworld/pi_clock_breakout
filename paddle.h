#ifndef PADDLE_HPP_
#define PADDLE_HPP_

#include "screen.h"
// #include "ball.h"

class Paddle
{
private:
    float pos_x;
   
    int16_t max_x, max_y;
    const int16_t paddlewidth=32;
    int16_t paddleheight=-6;
    int16_t pos_y=15;
    uint16_t color = ILI9486_YELLOW;
    bool justLine=true;
    int16_t paddlespeed=3;

    Screen * tft;


public:
    Paddle(Screen * mastertft);
    void setType(bool gametyp);
    void update(float ballpos);
    void move(int16_t movex);
    void draw(void);
    void undraw(void);
    int16_t getX(void);
    void setX(int16_t x);
};

#endif // PADDLE_HPP_