#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define L_LIMIT 26
#define ARR_LIMIT 123
#define BUF_LIMIT 500

struct letter {
    int occurrences;
    int c;
};

int cmp(const void *x, const void *y) {
    struct letter *a = (struct letter *) x;
    struct letter *b = (struct letter *) y;

    if (a->occurrences == b->occurrences) return 0;
    if (a->occurrences < b->occurrences) return 1;
    return -1;
}

int main(int argc, char *argv[]) {
    FILE *fr = fopen("beautiful_stringstxt.txt", "r"), *fw = fopen("beautiful_strings_output.txt", "w+");
    char buf[BUF_LIMIT], *s;
    int i, high, len, temp, total;
    int j = 1, arr[ARR_LIMIT];

    struct letter l[L_LIMIT];

    fgets(buf, sizeof (buf), fr);

    while (fgets(buf, sizeof (buf), fr) != NULL) {

        memset(l, 0, sizeof (l));
        memset(arr, 0, sizeof (arr));

        s = buf;
        while (*s) {
            temp = tolower(*s); s++;
            if (temp < 'a' || temp > 'z') continue;
            arr[temp]++;
        }

        len = 0;
        for (i = 0; i < ARR_LIMIT; i++) {
            if (arr[i] > 0) {
                l[len].occurrences = arr[i];
                l[len].c = i;
                len++;
            }
        }

        qsort(l, len, sizeof (struct letter), cmp);

        total = 0, high = 26;
        for (i = 0; i < len; i++) {
            temp = high * l[i].occurrences;
            total += temp;
            high--;
        }

        fprintf(fw, "Case #%d: %d\n", j++, total);
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
