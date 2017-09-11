    }
}

void memtest_test(size_t megabytes, int passes) {
    size_t bytes = megabytes*1024*1024;
    unsigned long *m = malloc(bytes);
    int pass = 0, j;

    if (m == NULL) {
        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
