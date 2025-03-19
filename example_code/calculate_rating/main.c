#include <stdio.h>

// How many decimals
#define PRECISION 1000

int compute_integer_part(int A, int B) {
    if (A == B)
        return 1;
    else
        return 0;
}

int compute_decimal_part(int A, int B) {
    int remainder;
    int decimal_part;

    if (B == 0)
        return 0;

    remainder = A % B;
    decimal_part = (remainder * PRECISION) / B;

    return decimal_part;
}

int main(int argc, char const *argv[]) {
    int num_served_groups = 7;
    int num_left_groups = 2;
    int integer_part = compute_integer_part(num_served_groups, num_served_groups + num_left_groups);
    int decimal_part = compute_decimal_part(num_served_groups, num_served_groups + num_left_groups);

    float for_verify = (num_served_groups * 1.0) / (num_served_groups + num_left_groups);

    printf("%d.%d, %f\n", integer_part, decimal_part, for_verify);

    return 0;
}
