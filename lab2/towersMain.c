#include "towers.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n = 3;
    int from = 1;
    int dest = 2;

    if (argc > 1) {
        //printf("Entered 1");
        n = atoi(argv[1]);
        if (n <= 0) {
            fprintf(stderr, "Error: numberDisks must be a positive integer.\n");
            exit(1);
        }
    }

    if (argc > 2) {
        //printf("Entered 2");
        from = atoi(argv[2]);
        if (from < 1 || from > 3) {
            fprintf(stderr, "Error: fromTower must be '1', '2', or '3'.\n");
            exit(1);
        }
    }

    if (argc > 3) {
        //printf("Entered 3");
        dest = atoi(argv[3]);
        if (dest < 1 || dest > 3) {
            fprintf(stderr, "Error: destTower must be '1', '2', or '3'.\n");
            exit(1);
        }
    }

    if (from == dest) {
        fprintf(stderr, "Error: fromTower and destTower must be different.\n");
        exit(1);
    }

    towers(n, from, dest);
    exit(0);
}

