void memtest_test(size_t megabytes, int passes) {
    size_t bytes = megabytes*1024*1024;
    unsigned long *m = malloc(bytes);
    int pass = 0, j;

    if (m == NULL) {
        fprintf(stderr,"Unable to allocate %zu megabytes: %s",
            megabytes, strerror(errno));
        exit(1);
    }
    while (pass != passes) {
        pass++;
        memtest_progress_start("Random fill",pass);
        memtest_fill(m,bytes);
        memtest_progress_end();
        for (j = 0; j < 4; j++) {
            memtest_progress_start("Compare",pass);
            memtest_compare(m,bytes);
            memtest_progress_end();
        }
    }
}