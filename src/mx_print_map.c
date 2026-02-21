#include "way_home.h"

void mx_print_map(char **map, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            mx_printchar(map[i][j]);
        }
        mx_printchar('\n');
    }
}
