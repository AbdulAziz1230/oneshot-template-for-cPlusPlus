default:
	g++ main.cpp -o ./game_name.exe -O2 -static -s -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm