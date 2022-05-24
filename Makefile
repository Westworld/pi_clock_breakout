game:
	g++ -std=c++11 main.cpp screen.cpp paddle.cpp ball.cpp shot.cpp block.cpp blocks.cpp TetrisMatrixDraw.cpp WString.cpp -o play -L lib -l SDL2-2.0.0 -l SDL2_ttf-2.0.0

gamepi:
	g++ -std=c++11 main.cpp screen.cpp paddle.cpp ball.cpp shot.cpp block.cpp blocks.cpp TetrisMatrixDraw.cpp WString.cpp -o play `sdl2-config --cflags --libs`