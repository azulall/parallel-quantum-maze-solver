#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WALL 1
#define PATH 0




typedef struct {
    int edge_x, edge_y; // Dış çeperdeki kapı
    int in_x, in_y;     // İçerideki başlangıç yolu
} Point;

Point get_random_edge_point(int n) {
    Point p;
    int edge = rand() % 4; // 0: Üst, 1: Alt, 2: Sol, 3: Sağ
    
    // Rastgele bir tek sayı seç (1, 3, 5, ..., n-2)
    int rand_pos = 1 + 2 * (rand() % ((n - 1) / 2));

    switch (edge) {
        case 0: // Üst
            p.edge_x = rand_pos; p.edge_y = 0;
            p.in_x = rand_pos;   p.in_y = 1;
            break;
        case 1: // Alt
            p.edge_x = rand_pos; p.edge_y = n - 1;
            p.in_x = rand_pos;   p.in_y = n - 2;
            break;
        case 2: // Sol
            p.edge_x = 0;        p.edge_y = rand_pos;
            p.in_x = 1;          p.in_y = rand_pos;
            break;
        case 3: // Sağ
            p.edge_x = n - 1;    p.edge_y = rand_pos;
            p.in_x = n - 2;      p.in_y = rand_pos;
            break;
    }
    return p;
}


void shuffle(int *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}


void generate_maze(int **matrix, int x, int y, int n)
{
    int dirs[] = {0, 1, 2, 3}; // 0:Yukarı, 1:Aşağı, 2:Sol, 3:Sağ
    shuffle(dirs, 4);

    for (int i = 0; i < 4; i++)
    {
        int dx = 0, dy = 0;
        if (dirs[i] == 0)
            dy = -2; // Yukarı
        else if (dirs[i] == 1)
            dy = 2; // Aşağı
        else if (dirs[i] == 2)
            dx = -2; // Sol
        else if (dirs[i] == 3)
            dx = 2; // Sağ

        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < n && ny >= 0 && ny < n && matrix[ny][nx] == WALL)
        {
            // Aradaki duvarı kaldır ve yeni yolu aç
            matrix[y + dy / 2][x + dx / 2] = PATH;
            matrix[ny][nx] = PATH;
            generate_maze(matrix, nx, ny, n);
        }
    }

}




void save_maze_to_file(int **matrix, int n, Point start, Point end, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror("Dosya acilamadi");
        return;
    }

    // Header Bilgileri: Boyut, Giriş(x,y), Çıkış(x,y)
    fprintf(f, "%d\n", n);
    fprintf(f, "%d %d\n", start.edge_x, start.edge_y);
    fprintf(f, "%d %d\n", end.edge_x, end.edge_y);

    // Matris Verisi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(f, "%d", matrix[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}




int main(int argc, char *argv[])
{
    if (argc < 4) {
        printf("Usage: %s <maze_size> <output_file> <seed>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *output_file = argv[2];
    int seed = atoi(argv[3]);

    if (n % 2 == 0) {
        printf("Maze size must be an odd number.\n");
        return 1;
    }

    srand(seed);

    // Dinamik bellek tahsisi
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
            matrix[i][j] = WALL;
    }

    // Başlangıç noktası
    matrix[1][1] = PATH;
    generate_maze(matrix, 1, 1, n);

  
    // 2. Giriş ve Çıkış noktalarını belirle
    Point start = get_random_edge_point(n);
    Point end;
    do {
        end = get_random_edge_point(n);
    } while (start.edge_x == end.edge_x && start.edge_y == end.edge_y); // Giriş ve çıkış aynı olmasın

    // 3. Kapıları aç ve labirenti üret
    matrix[start.edge_y][start.edge_x] = PATH;
    matrix[end.edge_y][end.edge_x] = PATH;

    // Labirenti girişin içindeki hücreden başlatarak üret
    matrix[start.in_y][start.in_x] = PATH;
    generate_maze(matrix, start.in_x, start.in_y, n);

    // 4. Yazdır (Girişi 'S', çıkışı 'E' olarak işaretleyebilirsin)
    matrix[start.edge_y][start.edge_x] = 2; // Sembolik: Start
    matrix[end.edge_y][end.edge_x] = 3;   // Sembolik: End


    // Labirenti yazdır
   /* for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%s", matrix[i][j] == WALL ? "██" : "  ");
        }
        printf("\n");
    }*/

    // Labirenti dosyaya kaydet
    save_maze_to_file(matrix, n, start, end, output_file);
    
    // Belleği serbest bırak
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}