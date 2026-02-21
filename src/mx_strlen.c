#include <way_home.h>

int mx_strlen(const char *c) {
    int length = 0;

    for (const char *p = c; *p != '\0'; p++) length ++;

    return length;
}
