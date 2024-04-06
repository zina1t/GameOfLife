#include <ncurses.h>
#include <stdio.h>

#define HEIGHT 25
#define WIDTH 80

void scanField(int matrix[HEIGHT][WIDTH]);
void drawField(int matrix[HEIGHT][WIDTH]);
void newField(int (*matrix)[WIDTH], int (*matix_new)[WIDTH]);
int countNeighbours(int x, int y, int (*matrix)[WIDTH]);

int main() {
    int matrix[HEIGHT][WIDTH];
    int matrix_new[HEIGHT][WIDTH];
    int delay = 80;
    scanField(matrix);
    freopen("/dev/tty", "r", stdin);
    initscr();
    keypad(stdscr, TRUE);   // включает режим функциональных клавиш
    noecho();               // не отображает вводимые символы
    nodelay(stdscr, TRUE);  // включает неблокирующий ввод
    int flag = 1;
    while (flag == 1) {
        clear();
        refresh();
        drawField(matrix);
        int button = getch();
        switch (button) {
            case KEY_RIGHT:  // ускорение
                if (delay > 40) delay -= 20;
                break;
            case KEY_LEFT:
                if (delay < 100) delay += 20;  // замедление
                break;
            case 'q':
                flag = 0;
                endwin();  // очистка экрана и выход
                break;
        }
        timeout(delay);  // обновляем скорость согласно введённым данным
        newField(matrix, matrix_new);
    }
    return 0;
}

void scanField(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void drawField(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j] == 1)
                printw("x");  // living cell
            else if (matrix[i][j] == 0)
                printw(" ");  // dead cell
        }
        printw("\n");
    }
}

int countNeighbours(int x, int y, int (*matrix)[WIDTH]) {
    int sum = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int rows = (x + i + HEIGHT) % HEIGHT;
            int cols = (y + j + WIDTH) % WIDTH;
            sum += matrix[rows][cols];
        }
    }
    sum -= matrix[x][y];
    return sum;
}

void newField(int (*matrix)[WIDTH], int (*matrix_new)[WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int state = matrix[i][j];
            int neightbours = countNeighbours(i, j, matrix);
            if (state == 0 && neightbours == 3) {
                matrix_new[i][j] = 1;
            } else if (state == 1 && (neightbours < 2 || neightbours > 3)) {
                matrix_new[i][j] = 0;
            } else {
                matrix_new[i][j] = state;
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = matrix_new[i][j];
        }
    }
}
