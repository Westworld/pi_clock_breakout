#ifndef SCREEN_HPP_
#define SCREEN_HPP_

//#include <string>

//Include SDL2 and SDL2_Ttf
#include "SDL2/SDL.h"
//#include "include/SDL2/SDL_ttf.h"

#define ILI9486_YELLOW      0xFE00 // FFE0
#define ILI9486_YELLOW2     0xFF34
#define ILI9486_BLACK       0x0000 
#define ILI9486_CYAN        0x07FF 
#define TFT_RED             0xFF00

#define WorldWidth 1024
#define WorldHeight 600

class Screen
{
private:
    //TetrisMatrixDraw * tetris;
    int16_t x_offset, y_offset;
        // Window size
    int _width = WorldWidth;
    int _height = WorldHeight;

    SDL_Rect rectangle;

    // SDL Window
    SDL_Window *_window;

    // SDL Renderer to draw to
    SDL_Renderer *_renderer;

    void init_sdl(void);
    void init_window_and_renderer(void);

public:
    Screen(void);
    void setOffset(int16_t x, int16_t y);
    void reset(void);
    void test(void);
    long getwidth(void);
    long getheight(void);
    void setSDLColor(uint16_t color);
    uint16_t calcY(uint16_t y);
    uint16_t calcX(uint16_t x);
    void fillCircle(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t radius, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color);
    void drawRoundRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t corner, uint16_t color);
    void drawText(char * text, int16_t x, int16_t y);
    void drawNumber(int16_t number, int16_t x, int16_t y);
    void setTextColor(int16_t front,int16_t back);
    void setTextSize(int16_t size);
    void setFreeFontFix();
    void clearFreeFont();
    void setRotation(int16_t rot);
    void fillScreen(uint16_t color);
    void drawicon(int x, int y, const uint16_t *icon); 


    int8_t getPinName(int8_t pin);

    void Tetris_setText(char * txt, bool forceRefresh);
    bool Tetris_drawText(int x, int y);
    bool Tetris_drawText(int x, int y, int color);
    void Tetris_setNumbers(long nummer);
    void Tetris_setTime(char * timeString);
    bool Tetris_drawNumbers(int x_pos, int y_pos, bool drawColon);
    bool Tetris_drawNumbers(int x_pos, int y_pos, bool drawColon, int color);
    void Tetris_DrawChar(char * letter, uint8_t x, uint8_t y, uint16_t color);
    void Tetris_drawShape(int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot);

    bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap);
    void tft_setSwapBytes(bool swap);


    bool event();
    void doRender();
    void sleep(int ms);
    int SDL_RenderFillCircle(SDL_Renderer * renderer, int x, int y, int radius);

};

#endif // SCREEN_HPP_