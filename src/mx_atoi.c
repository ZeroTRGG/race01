#include <way_home.h>

bool mx_isdigit(int c);
bool mx_isspace(char c);

int mx_atoi(const char *src) {
    int result = 0;
    int sign = 1;
    while (mx_isspace(*src) || *src == '+') {
        src++;
    }
    if (*src == '-') {
        sign = -1;
        src++;
    }
    while (mx_isdigit(*src)) {
        result *= 10;
        result += (*src - 48) * sign;
        src++;
    }
    return result;
}
