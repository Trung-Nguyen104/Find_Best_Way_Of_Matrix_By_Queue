#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int x;
    int y;
    struct Node* next;
}*NODE;

typedef struct Queue {
    NODE front;
    NODE rear;
}*QUEUE;

NODE create_node(int x, int y) {
    NODE node = (struct Node*) malloc(sizeof(struct Node));
    node->x = x;
    node->y = y;
    node->next = NULL;
    return node;
}

QUEUE create_queue() {
    QUEUE q = (struct Queue*) malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(QUEUE q, int x, int y) {
    NODE node = create_node(x, y);
    if (q->rear == NULL) {
        q->front = node;
        q->rear = node;
    }
    else {
        q->rear->next = node;
        q->rear = node;
    }
}

void dequeue(QUEUE q) {
    if (q->front == NULL) {
        return;
    }
    NODE temp = q->front;
    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) {
        q->rear = NULL;
    }
}

NODE front(QUEUE q) {
    return q->front;
}

int is_empty(QUEUE q) {
    return q->front == NULL;
}

void print_path(int path[][5], int x, int y) {
    if (path[x][y] == -1) {
        printf("Khong co duong di\n");
        return;
    }
    int i = x, j = y;
    printf("(%d, %d) ", i, j);
    while (path[i][j] != 0) {
        if (i > 0 && path[i - 1][j] == path[i][j] - 1) {
            printf("-> (%d, %d) ", i - 1, j);
            i--;
        }
        else if (i < 4 && path[i + 1][j] == path[i][j] - 1) {
            printf("-> (%d, %d) ", i + 1, j);
            i++;
        }
        else if (j > 0 && path[i][j - 1] == path[i][j] - 1) {
            printf("-> (%d, %d) ", i, j - 1);
            j--;
        }
        else if (j < 4 && path[i][j + 1] == path[i][j] - 1) {
            printf("-> (%d, %d) ", i, j + 1);
            j++;
        }
    }
}


void bfs(int maze[][5], int path[][5], int row, int col, int sx, int sy, int ex, int ey) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    QUEUE q = create_queue();
    enqueue(q, sx, sy);
    path[sx][sy] = 0;

    while (!is_empty(q)) {
        NODE current = front(q);
        int cx = current->x;
    	int cy = current->y;
	    dequeue(q);
	    for (int i = 0; i < 4; i++) {
	        int nx = cx + dx[i];
	        int ny = cy + dy[i];
	        if (nx >= 0 && nx < row && ny >= 0 && ny < col && maze[nx][ny] != 1 && path[nx][ny] == -1) {
	            path[nx][ny] = path[cx][cy] + 1;
			if (maze[nx][ny] == 2){
	            		print_path(path, ex, ey);
	        		return;
			}
	            enqueue(q, nx, ny);
	        }
	    }
	}
}

int main() {
	int maze[5][5] = {
		{3, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 2, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0}
		};
	int path[5][5];
		for (int i = 0; i < 5; i++) {
		    for (int j = 0; j < 5; j++) {
		        path[i][j] = -1;
		    }
		}
		
	bfs(maze, path, 5, 5, 0, 0, 2, 2);
	printf("\n");
	for (int i = 0; i < 5; i++) {
		    for (int j = 0; j < 5; j++) {
		        printf("%d	", path[i][j]);
		    }
		    printf("\n");
		}

	return 0;
}


