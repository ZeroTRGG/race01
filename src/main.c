#include <way_home.h>

void validate_pts(char **map, int *in) {
    if (in[2] < 0 || in[2] >= in[0] || in[3] < 0 || in[3] >= in[1] ||
        in[4] < 0 || in[4] >= in[0] || in[5] < 0 || in[5] >= in[1]) {
        mx_printerr("points are out of map range\n");
        exit(1);
    }
    if (map[in[3]][in[2]] == '#') {
        mx_printerr("entry point cannot be an obstacle\n");
        exit(1);
    }
    if (map[in[5]][in[4]] == '#') {
        mx_printerr("exit point cannot be an obstacle\n");
        exit(1);
    }
}

void init_app(char **av, int *info, char ***map) {
    info[2] = mx_atoi(av[2]);
    info[3] = mx_atoi(av[3]);
    info[4] = mx_atoi(av[4]);
    info[5] = mx_atoi(av[5]);
    get_map_dimensions(av[1], &info[0], &info[1]);
    *map = (char **)malloc(info[1] * sizeof(char *));
    for (int i = 0; i < info[1]; i++)
        (*map)[i] = (char *)malloc(info[0] * sizeof(char));
    populate_map(av[1], *map);
}

void free_maps(char **m, int **d, int h) {
    for (int i = 0; i < h; i++) {
        free(m[i]);
        free(d[i]);
    }
    free(m);
    free(d);
}

void save_map(char **map, int *in) {
    int fd = open("path.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) return;
    for (int i = 0; i < in[1]; i++) {
        write(fd, map[i], in[0]);
        write(fd, "\n", 1);
    }
    close(fd);
}

void step_back(int **dist, int *cur, int *in) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int nx, ny;
    
    for (int i = 0; i < 4; i++) {
        nx = cur[0] + dx[i];
        ny = cur[1] + dy[i];
        if (nx >= 0 && nx < in[0] && ny >= 0 && ny < in[1]) {
            if (dist[ny][nx] == dist[cur[1]][cur[0]] - 1) {
                cur[0] = nx;
                cur[1] = ny;
                return;
            }
        }
    }
}

void make_path(char **map, int **dist, int *in, int *max) {
    int cur[2] = {in[4], in[5]};
    
    while (dist[cur[1]][cur[0]] != 0) {
        map[cur[1]][cur[0]] = '*';
        step_back(dist, cur, in);
    }
    map[in[3]][in[2]] = '*';
    if (map[max[2]][max[1]] == '*') map[max[2]][max[1]] = 'X';
    else map[max[2]][max[1]] = 'D';
    save_map(map, in);
}

void find_max(int **dist, int *in, int *max_p) {
    for (int i = 0; i < in[1]; i++) {
        for (int j = 0; j < in[0]; j++) {
            if (dist[i][j] > max_p[0]) {
                max_p[0] = dist[i][j];
                max_p[1] = j;
                max_p[2] = i;
            }
        }
    }
}

void print_res(int max_dist, int exit_dist) {
    mx_printstr("dist=");
    mx_printint(max_dist);
    mx_printstr("\nexit=");
    mx_printint(exit_dist);
    mx_printstr("\n");
}

void run_algo(char **map, int *info) {
    int **dist;
    int max_p[3] = {0, 0, 0};

    validate_pts(map, info);
    dist = get_distance_map(map, info);
    if (dist[info[5]][info[4]] == -1) {
        mx_printerr("route not found\n");
        exit(1);
    }
    find_max(dist, info, max_p);
    print_res(max_p[0], dist[info[5]][info[4]]);
    make_path(map, dist, info, max_p);
    free_maps(map, dist, info[1]);
}

int main(int argc, char *argv[]) {
    int info[6];
    char **map = NULL;

    if (argc != 6) {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        exit(1);
    }
    init_app(argv, info, &map);
    run_algo(map, info);
    return 0;
}
