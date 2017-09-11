    for (j = 0; j < words; j++) {
        *p = (unsigned long)p;
        p++;
        if ((j & 0xffff) == 0) memtest_progress_step(j,words*2,'A');
    }
    /* Test */
    p = l;
    for (j = 0; j < words; j++) {
        if (*p != (unsigned long)p) {
            printf("\n*** MEMORY ADDRESSING ERROR: %p contains %lu\n",
                (void*) p, *p);
            exit(1);
        }
        p++;
        if ((j & 0xffff) == 0) memtest_progress_step(j+words,words*2,'A');
    }
}

/* Fill words stepping a single page at every write, so we continue to
 * touch all the pages in the smallest amount of time reducing the
 * effectiveness of caches, and making it hard for the OS to transfer
 * pages on the swap. */
void memtest_fill_random(unsigned long *l, size_t bytes) {
    unsigned long step = 4096/sizeof(unsigned long);
    unsigned long words = bytes/sizeof(unsigned long)/2;
    unsigned long iwords = words/step;  /* words per iteration */
