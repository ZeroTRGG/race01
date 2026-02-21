#include <way_home.h>
void mx_printint(int n) {
    char n_string [10];
    int digit_count = 1;
    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }
    for (int d = n / 10; d != 0; d /= 10) digit_count ++;
    for (int i = digit_count - 1; i >= 0; i--) {
        n_string[i] = n % 10 + 48;
        n /= 10;
    }
    for (int i = 0; i < digit_count; i++) mx_printchar(n_string[i]);

}
