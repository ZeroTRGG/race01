#include "way_home.h"

int **get_distance_map(char **map, int width, int height, int x1, int y1) {
    int **dist = (int **)malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        dist[i] = (int *)malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) dist[i][j] = -1;
    }

    if (map[y1][x1] == '#') return dist;
    dist[y1][x1] = 0;

    bool changed = true;
    for (int d = 0; changed; d++) {
        changed = false;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (dist[y][x] == d) {
                    int dx[] = {0, 0, 1, -1};
                    int dy[] = {1, -1, 0, 0};
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i], ny = y + dy[i];
                        if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                            map[ny][nx] == '.' && dist[ny][nx] == -1) {
                            dist[ny][nx] = d + 1;
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    return dist;
}
