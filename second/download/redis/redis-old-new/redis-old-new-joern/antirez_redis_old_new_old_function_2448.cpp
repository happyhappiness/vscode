void memtest_test(size_t megabytes, int passes) {
    size_t bytes = megabytes*1024*1024;
    unsigned long *m = malloc(bytes);
    int pass = 0;

    if (m == NULL) {
        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
            megabytes, strerror(errno));
        exit(1);
    }
    while (pass != passes) {
        pass++;
        printf("PASS %d... ", pass);
        fflush(stdout);
        memtest_fill(m,bytes);
        memtest_compare(m,bytes);
        printf("ok\n");
    }
}