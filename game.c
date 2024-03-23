#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 80
#define HEIGHT 25
#define DELAY_MS 1
void delay(int milliseconds) {
    long pause;
    clock_t now, then;

    pause = milliseconds * (CLOCKS_PER_SEC / 1000);
    now = then = clock();

    while ((now - then) < pause) {
        now = clock();
    }
}

int countNeighbors(int **grid, int x, int y, int cols, int rows) {
    int sum = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int col = (x + i + cols) % cols;
            int row = (y + j + rows) % rows;
            sum += grid[col][row];
        }
    }
    sum -= grid[x][y];
    return sum;
}

int **make2DArray(int cols, int rows) {
    int **arr = (int **)malloc(cols * sizeof(int *));
    for (int i = 0; i < cols; i++) {
        arr[i] = (int *)malloc(rows * sizeof(int));
    }
    return arr;
}

/*void setup(int ***grid, int *cols, int *rows) {
    *cols = WIDTH;
    *rows = HEIGHT;
    *grid = make2DArray(*cols, *rows);
    srand(time(NULL));
    for (int i = 0; i < *cols; i++) {
        for (int j = 0; j < *rows; j++) {
            (*grid)[i][j] = 1;
        }
    }
}*/

void frog(int ***grid, int *cols, int *rows) {
    *cols = WIDTH;
    *rows = HEIGHT;
    *grid = make2DArray(*cols, *rows);
    for (int i = 0; i < *cols; i++) {
        for (int j = 0; j < *rows; j++) {
            if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 2 && (j == 0 || j == 1 || j == 2)))
            (*grid)[i][j] = 1;
        }
    }
}


void draw(int **grid, int cols, int rows) {
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            if (grid[i][j] == 1)
                printf("O");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void computeNext(int **grid, int **next, int cols, int rows) {
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int state = grid[i][j];
            int sum = 0;
            int neighbors = countNeighbors(grid, i, j, cols, rows);
            if (state == 0 && neighbors == 3) {
                next[i][j] = 1;
            } else if (state == 1 && (neighbors < 2 || neighbors > 3)) {
                next[i][j] = 0;
            } else {
                next[i][j] = state;
            }
        }
    }
}

void clear1() {
  for (int i = 0; i <= 155; i++) {
    printf("\n");
  }
}


int main() {
    int **grid;
    int cols, rows;
    frog(&grid, &cols, &rows);

    while (1) {
        draw(grid, cols, rows);
        delay(1000);
        clear();
        int **next = make2DArray(cols, rows);
        computeNext(grid, next, cols, rows);

        for (int i = 0; i < cols; i++) {
            free(grid[i]);  //ОСВОБОЖДАЕМ ПОЛЕ
        }
        free(grid);

        grid = next; //ОБНОВЛЯЕМ ПОЛЕ
    }

    return 0;
}
