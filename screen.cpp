#include "screen.h"

// Window size
int _width = 640;
int _height = 480;

SDL_Rect rectangle;

// SDL Window
SDL_Window *_window;

// SDL Renderer to draw to
SDL_Renderer *_renderer;

/**
 * Initialise SDL2 and output some useful display info
 */
void init_sdl()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("[Error] SDL Init : %s \n", SDL_GetError());
  } else {
    printf("SDL INITIALISED\n");
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    printf("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);
  }
}

/**
 * Initialise an SDL Window and Renderer
 *
 * This uses SDL_CreateWindowAndRenderer. They can alternatively be created separately. See SDL2 Docs
 */
void init_window_and_renderer()
{
  if (SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_SHOWN, &_window, &_renderer) != 0) {
    printf("[Error] Creating Window and Renderer: %s\n", SDL_GetError());
    exit(0);
  } else {
    printf("Created Window and Renderer %dx%d\n", _width, _height);
  }
}


Screen::Screen() {

    //Init SDL2 and SDL2_TTF
    init_sdl();
    TTF_Init();
	init_window_and_renderer();

    x_offset=0;y_offset=0;

    //tetris = new TetrisMatrixDraw(tft);
}

void Screen::setOffset(int16_t x, int16_t y) {
    x_offset=x;
    y_offset=y;
}

void Screen::reset() {
    x_offset=0;y_offset=0;
	//SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); 

    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = _width;
    rectangle.h = _height;
    //SDL_RenderFillRect(_renderer, &rectangle);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Screen::setRotation(int16_t rot) {
    //tft.setRotation(rot);
}

void Screen::test(void) {

}

// Get pin name for ESP8266
int8_t Screen::getPinName(int8_t pin)
{
 
}

long Screen::getwidth(void) { 
    return _width;
 }
long Screen::getheight(void){ 
    return _height;
}
void Screen::fillCircle(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    //tft.fillCircle(x + x_offset, y + y_offset, radius, color);
}
void Screen::fillRect(int16_t x, int16_t y, int16_t radius, uint16_t color) {
    //tft.fillRect(x + x_offset, y + y_offset, radius, radius, color);
}    

void Screen::fillRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
    SDL_Rect _sampleRect;
    _sampleRect.x = x;
    _sampleRect.y =y;
    _sampleRect.h =height;
    _sampleRect.w = width;
    SDL_RenderFillRect(_renderer, &_sampleRect);

    //tft.fillRect(x + x_offset, y + y_offset, width, height, color);
}

void Screen::drawRect(int16_t x, int16_t y, int16_t width, int16_t height, uint16_t color) {
    //tft.drawRect(x + x_offset, y + y_offset, width, height, color);
}

void Screen::drawRoundRect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t corner, uint16_t color) {
    //tft.drawRoundRect(x + x_offset, y + y_offset, width, height, corner, color);
}

void Screen::setTextColor(int16_t front,int16_t back) {
    //tft.setTextColor(front,back); 
}

void Screen::setTextSize(int16_t size) {
    //tft.setTextSize(size);
}

 void Screen::setFreeFontFix() {
     //tft.setFreeFont(FF20); // FF20
 }

 void Screen::clearFreeFont() {
     //tft.setFreeFont(NULL); // FF20
 }

 void Screen::drawNumber(int16_t number, int16_t x, int16_t y) {
     //tft.drawNumber(number, x + x_offset, y + y_offset);
 }

void Screen::drawText(std::string text, int16_t x, int16_t y) {
        /*tft.setTextColor(ILI9486_YELLOW, ILI9486_BLACK);
        tft.setCursor(x + x_offset, y + y_offset);
        tft.println(text);
        */
}

void Screen::fillScreen(uint16_t color) {
    //SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); 
    //SDL_RenderFillRect(_renderer, &rectangle);

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
}

void Screen::drawicon(int x, int y, const uint16_t *icon) { // Draws the graphics icons based on stored image bitmaps  

 //tft.pushImage(x + x_offset, y + y_offset, 28, 28, icon);
  
}


void Screen::Tetris_setText(std::string txt, bool forceRefresh) {
   // tetris->setText(txt, forceRefresh);
}

bool Screen::Tetris_drawText(int x, int y) {
    //return tetris->drawText(x, y);
    return false;
}    

bool Screen::Tetris_drawText(int x, int y, int color) {
    //return tetris->drawText(x, y, color);
    return false;
}  

 void Screen::Tetris_DrawChar(std::string letter, uint8_t x, uint8_t y, uint16_t color) {
     //tetris->drawChar(letter,  x,  y,  color);
 }

 void Screen::Tetris_drawShape(int blocktype, uint16_t color, int x_pos, int y_pos, int num_rot) {
    // tetris->drawLargerShape(10, blocktype,  color,  x_pos,  y_pos,  num_rot);
 }

void Screen::Tetris_setNumbers(long nummer) {
    // tetris->setNumbers(nummer);
 }

bool Screen::Tetris_drawNumbers(int x_pos, int y_pos, bool drawColon){
    // return tetris->drawNumbers(x_pos,y_pos, drawColon);
 }

bool Screen::Tetris_drawNumbers(int x_pos, int y_pos, bool drawColon, int color) {
    // return tetris->drawNumbers(x_pos,y_pos, drawColon, color);
 }

void Screen::Tetris_setTime(char * timeString) {
  //  tetris->setTime(timeString, true);
}

void Screen::tft_setSwapBytes(bool swap) {
   // tft.setSwapBytes(swap);
}

 // This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool Screen::tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  /*
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  */
  return 1;
}

bool Screen::event() {
     SDL_Event event;
     SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            return true;
        }
        else   
            return false;
}

void Screen::doRender() {
    SDL_RenderPresent(_renderer);
}

void Screen::sleep(int ms) {
    SDL_Delay(ms);
}