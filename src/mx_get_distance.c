#include <way_home.h>

int **alloc_dist(int w, int h) {
    int **dist = (int **)malloc(h * sizeof(int *));
    
    for (int i = 0; i < h; i++) {
        dist[i] = (int *)malloc(w * sizeof(int));
        for (int j = 0; j < w; j++) dist[i][j] = -1;
    }
    return dist;
}

void update_adj(char **map, int **dist, int *in, int *s) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int nx, ny;
    
    for (int i = 0; i < 4; i++) {
        nx = s[0] + dx[i];
        ny = s[1] + dy[i];
        if (nx >= 0 && nx < in[0] && ny >= 0 && ny < in[1]) {
            if (map[ny][nx] == '.' && dist[ny][nx] == -1) {
                dist[ny][nx] = s[2] + 1;
                s[3] = 1;
            }
        }
    }
}

int **get_distance_map(char **map, int *in) {
    int **dist = alloc_dist(in[0], in[1]);
    int s[4] = {0, 0, 0, 1};
    
    if (map[in[3]][in[2]] == '#') return dist;
    dist[in[3]][in[2]] = 0;
    for (s[2] = 0; s[3]; s[2]++) {
        s[3] = 0;
        for (s[1] = 0; s[1] < in[1]; s[1]++) {
            for (s[0] = 0; s[0] < in[0]; s[0]++) {
                if (dist[s[1]][s[0]] == s[2])
                    update_adj(map, dist, in, s);
            }
        }
    }
    return dist;
}
