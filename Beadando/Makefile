all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o Darts.exe 

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o Darts -Wall -Wextra -Wpedantic