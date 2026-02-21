#ifndef WAY_HOME_H
#define WAY_HOME_H

#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h>   
#include <stdbool.h> 

typedef struct s_point {
    int x;
    int y;
}              t_point;

bool mx_isdigit(int c);
bool mx_isspace(char c);
int mx_atoi(const char *src);
void mx_printchar(char c);
void mx_printerr(const char *s);
void mx_printint(int n);
void mx_printstr(const char *s);
int mx_strlen(const char *c);
void get_map_dimensions(const char *filename, int *width, int *height);
void mx_print_map(char **map, int width, int height);
void populate_map(const char *filename, char **map);
int **get_distance_map(char **map, int width, int height, int x1, int y1);


#endif
