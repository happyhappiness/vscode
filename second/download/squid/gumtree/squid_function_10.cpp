void
xmalloc_find_leaks(void)
{
    int B, I;
    int leak_sum = 0;

    extern void _etext;
    fprintf(stderr, "----- Memory map ----\n");
    xmalloc_scan_region(&_etext, (void *) sbrk(0) - (void *) &_etext, 0);

    for (B = 0; B < DBG_ARRY_BKTS; B++) {
        for (I = 0; I < DBG_ARRY_SZ; I++) {
            if (malloc_ptrs[B][I] && malloc_refs[B][I] == 0) {
                /* Found a leak... */
                fprintf(stderr, "Leak found: %p", malloc_ptrs[B][I]);
                fprintf(stderr, " %s", malloc_file[B][I]);
                fprintf(stderr, ":%d", malloc_line[B][I]);
                fprintf(stderr, " size %d", malloc_size[B][I]);
                fprintf(stderr, " allocation %d\n", malloc_count[B][I]);
                leak_sum += malloc_size[B][I];
            }
        }
    }

    if (leak_sum) {
        fprintf(stderr, "Total leaked memory: %d\n", leak_sum);
    } else {
        fprintf(stderr, "No memory leaks detected\n");
    }

    fprintf(stderr, "----------------------\n");
}