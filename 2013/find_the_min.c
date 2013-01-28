#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K_LIMIT 1000 * 1000

int cmp(const void *x, const void *y) {
    int *a = (int *) x;
    int *b = (int *) y;

    if (*a == *b) return 0;
    if (*a < *b) return -1;

    return 1;
}


int calculate_Nth(int n, int k, int a, int b, int c, int r) {
    int m[k + 1], i, count, loc, temp, hash[K_LIMIT] = { 0 };

    m[0] = a;
    for (count = 1; count < k; count++) {
         m[count] = (b * m[count - 1] + c) % r;
    }

    for (i = 0; i < k; i++) {
        hash[m[i]]++;
    }

    --count;

    while (count < n) {
        i = 0;
        while (hash[i] > 0) i++;

        loc = ++count % k;
        temp = m[loc]; m[loc] = i;
        hash[temp]--; hash[i]++;
    }

    return m[(count - 1) % k];
}

int main(int argc, char *argv[]) {
    FILE *fr = fopen("find_the_min_input.txt", "r"), *fw = fopen("find_the_min_output.txt", "w+");
    int cases, k, n, a, b, c, r, ret, i;

    ret = fscanf(fr, "%d", &cases);
    if (ret != 1) printf("No. of cases not provided.\n");

    for (i = 0; i < cases; i++) {
        ret = fscanf(fr, "%d %d", &n, &k);
        if (ret != 2) printf("N or K not provided.\n");

        ret = fscanf(fr, "%d %d %d %d", &a, &b, &c, &r);
        if (ret != 4) printf("A, B, C or R not provided.\n");

        fprintf(fw, "Case #%d: %d\n", i + 1, calculate_Nth(n, k, a, b, c, r));
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
