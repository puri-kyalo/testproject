#include <stdio.h>
#include <conio.h> // For Windows systems, use "conio.h" for keyboard input handling

#define WIDTH 20
#define HEIGHT 10

int snakeX[100], snakeY[100]; // Arrays to store the positions of the snake segments
int snakeLength = 1;
int foodX, foodY;
int gameover = 0;
int i, j, k;

void setup() {
    snakeX[0] = WIDTH / 2; // Initialize the snake in the middle of the screen
    snakeY[0] = HEIGHT / 2;
    foodX = rand() % WIDTH; // Place food at a random position
    foodY = rand() % HEIGHT;
}

void draw() {
    system("cls"); // Clear the screen (for Windows systems, use "cls")

    for (i = 0; i < WIDTH + 2; i++)
        printf("#"); // Top wall
    printf("\n");

    for (i = 0; i < HEIGHT; i++){
	     for (j = 0; j < WIDTH; j++) {
            if (j == 0)
                printf("#"); // Left wall

            if (i == snakeY[0] && j == snakeX[0])
                printf("O"); // Head of the snake
            else if (i == foodY && j == foodX)
                printf("*"); // Food
            else {
                int tail = 0;
                for (k = 1; k < snakeLength; k++) {
                    if (i == snakeY[k] && j == snakeX[k]) {
                        printf("o"); // Body of the snake
                        tail = 1;
                    }
                }
                if (!tail)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#"); // Right wall
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++)
        printf("#"); // Bottom wall
    printf("\n");
}

void input() {
    if (_kbhit()) { // Check if a key is pressed
        switch (_getch()) { // Get the pressed key
            case 'a':
                snakeX[0]--; // Move left
                break;
            case 'd':
                snakeX[0]++; // Move right
                break;
            case 'w':
                snakeY[0]--; // Move up
                break;
            case 's':
                snakeY[0]++; // Move down
                break;
            case 'x':
                gameover = 1; // Quit the game
                break;
        }
    }
}

void logic() {
    // Check if the snake eats the food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeLength++; // Increase the length of the snake
        foodX = rand() % WIDTH; // Place food at a new random position
        foodY = rand() % HEIGHT;
    }

    // Move the body of the snake
    for (i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Check for collision with walls
    if (snakeX[0] == -1 || snakeX[0] == WIDTH || snakeY[0] == -1 || snakeY[0] == HEIGHT)
        gameover = 1;

    // Check for collision with itself
    for (i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameover = 1;
    }
}

int main() {
    setup();

    while (!gameover) {
        draw();
        input();
        logic();
    }

    printf("Game Over!\nYour Score: %d\n", snakeLength - 1);
    return 0;
}