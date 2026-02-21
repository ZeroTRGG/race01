#include <way_home.h>

void populate_map(const char *filename, char **map) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printerr("map does not exist\n");
        exit(1);
    }

    char c;
    int row = 0;
    int col = 0;
    int bytes_read;

    while ((bytes_read = read(fd, &c, 1)) > 0) {
        if (c == '#' || c == '.') {
            map[row][col] = c;
            col++;
        } 
        else if (c == '\n') {
            if (col > 0) {
                row++;
                col = 0;
            }
        }
    }
    close(fd);
}
