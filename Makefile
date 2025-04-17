default:
	g++ main.cpp -o ./main.exe -O2 -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm