
all: font/font.png
	g++ *.cpp -lSDL2 -lSDL2_image -Wall -Wextra -o game

font/font.png: font/gen_fontpng.py
	python font/gen_fontpng.py
