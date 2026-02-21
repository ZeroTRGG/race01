#include <way_home.h>

bool is_valid_map_char(char c) {
    return (c == '#' || c == '.' || c == ',' || c == '\n');
}

void get_map_dimensions(const char *filename, int *width, int *height) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        mx_printerr("map does not exist\n");
        exit(1);
    }

    char c;
    int current_width = 0;
    int first_row_width = -1;
    *height = 0;
    int bytes_read;

    while ((bytes_read = read(fd, &c, 1)) > 0) {
        if (!is_valid_map_char(c)) {
            mx_printerr("map error\n");
            exit(1);
        }
        if (c == '#' || c == '.') current_width++;
        if (c == '\n') {
            if (current_width > 0) {
                if (first_row_width == -1) {
                    first_row_width = current_width;
                } 
                else if (current_width != first_row_width) {
                    mx_printerr("map error\n");
                    exit(1);
                }
                (*height)++;
                current_width = 0;
            }
        }
    }
    
    if (current_width > 0) {
        if (first_row_width != -1 && current_width != first_row_width) {
            mx_printerr("map error\n");
            exit(1);
        }
        (*height)++;
    }
    *width = first_row_width;
    if (*height == 0 || *width <= 0) {
        mx_printerr("map does not exist\n");
        exit(1);
    }
    close(fd);
}
