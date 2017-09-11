    l2 = l1+words;
    for (w = 0; w < words; w++) {
        if (*l1 != *l2) {
            printf("\n*** MEMORY ERROR DETECTED: %p != %p (%lu vs %lu)\n",
                (void*)l1, (void*)l2, *l1, *l2);
            exit(1);
        }
        l1 ++;
        l2 ++;
        if ((w & 0xffff) == 0) memtest_progress_step(w,words,'=');
    }
}

void memtest_compare_times(unsigned long *m, size_t bytes, int pass, int times) {
    int j;

    for (j = 0; j < times; j++) {
        memtest_progress_start("Compare",pass);
        memtest_compare(m,bytes);
        memtest_progress_end();
    }
}

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

        memtest_progress_start("Addressing test",pass);
        memtest_addressing(m,bytes);
        memtest_progress_end();

        memtest_progress_start("Random fill",pass);
        memtest_fill_random(m,bytes);
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);

        memtest_progress_start("Solid fill",pass);
        memtest_fill_value(m,bytes,0,(unsigned long)-1,'S');
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);

        memtest_progress_start("Checkerboard fill",pass);
        memtest_fill_value(m,bytes,ULONG_ONEZERO,ULONG_ZEROONE,'C');
        memtest_progress_end();
        memtest_compare_times(m,bytes,pass,4);
    }
    free(m);
}

