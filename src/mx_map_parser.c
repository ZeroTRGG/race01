#include <way_home.h>

bool is_valid_char(char c) {
    return (c == '#' || c == '.' || c == ',' || c == '\n');
}

void open_map(const char *filename, int *fd) {
    *fd = open(filename, O_RDONLY);
    if (*fd < 0) {
        mx_printerr("map does not exist\n");
        exit(1);
    }
}

void proc_char(char c, int *cw, int *fw, int *h) {
    if (!is_valid_char(c)) {
        mx_printerr("map error\n");
        exit(1);
    }
    if (c == '#' || c == '.') (*cw)++;
    if (c == '\n' && *cw > 0) {
        if (*fw == -1) *fw = *cw;
        else if (*cw != *fw) {
            mx_printerr("map error\n");
            exit(1);
        }
        (*h)++;
        *cw = 0;
    }
}

void get_map_dimensions(const char *file, int *w, int *h) {
    int fd, br;
    char c;
    int v[2] = {0, -1};
    
    open_map(file, &fd);
    *h = 0;
    while ((br = read(fd, &c, 1)) > 0) proc_char(c, &v[0], &v[1], h);
    if (v[0] > 0) {
        if (v[1] != -1 && v[0] != v[1]) {
            mx_printerr("map error\n");
            exit(1);
        }
        (*h)++;
    }
    *w = v[1];
    if (*h == 0 || *w <= 0) {
        mx_printerr("map does not exist\n");
        exit(1);
    }
    close(fd);
}
