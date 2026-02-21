#include "way_home.h"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        exit(1);
    }

    int x1 = mx_atoi(argv[2]);
    int y1 = mx_atoi(argv[3]);
    int x2 = mx_atoi(argv[4]);
    int y2 = mx_atoi(argv[5]);
    int width = 0;
    int height = 0;
    get_map_dimensions(argv[1], &width, &height);

    char **map = (char **)malloc(height * sizeof(char *));
    for (int i = 0; i < height; i++) map[i] = (char *)malloc(width * sizeof(char));

    populate_map(argv[1], map);
    int **dist_map = get_distance_map(map, width, height, x1, y1);

    if (dist_map[y2][x2] == -1) {
        mx_printerr("route not found\n");
        exit(1);
    }

    int max_dist = 0;
    int x3 = 0, y3 = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (dist_map[i][j] > max_dist) {
                max_dist = dist_map[i][j];
                x3 = j;
                y3 = i;
            }
        }
    }
    mx_printstr("dist=");
    mx_printint(max_dist);
    mx_printstr("\nexit=");
    mx_printint(dist_map[y2][x2]);
    mx_printstr("\n");
    int curr_x = x2;
    int curr_y = y2;
    while (dist_map[curr_y][curr_x] != 0) {
        map[curr_y][curr_x] = '*';
        int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            int nx = curr_x + dx[i], ny = curr_y + dy[i];
            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                dist_map[ny][nx] == dist_map[curr_y][curr_x] - 1) {
                curr_x = nx; curr_y = ny;
                break;
            }
        }
    }
    map[y1][x1] = '*';
    if (map[y3][x3] == '*') map[y3][x3] = 'X';
    else map[y3][x3] = 'D';
    mx_print_map(map, width, height);
    for (int i = 0; i < height; i++) {
        free(map[i]);
        free(dist_map[i]);
    }
    free(map);
    free(dist_map);
    return 0;
}
