#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LIMIT 150

struct stack_node {
    int c;
    struct stack_node *p;
};

static struct stack_node *head = NULL;

void push_stack(int c) {
    struct stack_node *node = malloc(sizeof (*node));
    if (!node) {
        fprintf(stderr, "Malloc failed for push_stack()\n");
        exit(EXIT_FAILURE);
    }
    node->p = head; //autohandles the NULL case
    node->c = c;
    head = node;
}

struct stack_node *pop_stack() {
    if (head) {
        struct stack_node *cur = head;
        head = head->p;
        return cur;
    }
    return NULL;
}

int count_purge_stack() {
    int i = 0;
    while (pop_stack()) i++;
    return i;
}

int main(int argc, char *argv[]) {
    FILE *fr = fopen("balanced_smileystxt.txt", "r"), *fw = fopen("balanced_smileys_output.txt", "w+");
    char buf[BUF_LIMIT], *s, *prev;
    int smiley_count, count_stack, i = 0;

    fgets(buf, sizeof (buf), fr);

    while (fgets(buf, sizeof (buf), fr) != NULL) {
        smiley_count = 0;
        prev = s = buf;
        while (*s) {
            if (*s == '(') {
                if (*prev == ':')
                    smiley_count++;
                push_stack((int) *s);
            } else if (*s == ')') {
                if (*prev == ':') {
                    smiley_count++; prev = s++;
                    continue;
                }
                if (!pop_stack()) {
                    goto loopwhile;
                };
            }
            prev = s++;
        }
        count_stack = count_purge_stack();
        if ((!count_stack && smiley_count) || (smiley_count >= count_stack)) {
            fprintf(fw, "Case #%d: YES\n", ++i);
            continue;
        }
loopwhile:
        fprintf(fw, "Case #%d: NO\n", ++i);
    }

    fclose(fr);
    fclose(fw);

    return 0;
}
