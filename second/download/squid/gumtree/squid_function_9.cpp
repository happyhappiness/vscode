static void
xmalloc_scan_region(void *start, int size, int depth)
{
    int B, I;
    char *ptr = start;
    char *end = ptr + size - XMALLOC_LEAK_ALIGN;
    static int sum = 0;

    while (ptr <= end) {
        void *p = *(void **) ptr;

        if (p && p != start) {
            B = DBG_HASH_BUCKET(p);

            for (I = 0; I < DBG_ARRY_SZ; I++) {
                if (malloc_ptrs[B][I] == p) {
                    if (!malloc_refs[B][I]++) {
                        /* A new reference */
                        fprintf(stderr, "%*s%p %s:%d size %d allocation %d\n",
                                depth, "",
                                malloc_ptrs[B][I], malloc_file[B][I],
                                malloc_line[B][I], malloc_size[B][I],
                                malloc_count[B][I]);
                        sum += malloc_size[B][I];
                        xmalloc_scan_region(malloc_ptrs[B][I], malloc_size[B][I], depth + 1);

                        if (depth == 0) {
                            if (sum != malloc_size[B][I])
                                fprintf(stderr, "=== %d bytes\n", sum);

                            sum = 0;
                        }

#if XMALLOC_SHOW_ALL_REFERENCES

                    } else {
                        /* We have already scanned this pointer... */
                        fprintf(stderr, "%*s%p %s:%d size %d allocation %d ... (%d)\n",
                                depth * 2, "",
                                malloc_ptrs[B][I], malloc_file[B][I],
                                malloc_line[B][I], malloc_size[B][I],
                                malloc_count[B][I], malloc_refs[B][I]);
#endif

                    }
                }
            }
        }

        ptr += XMALLOC_LEAK_ALIGN;
    }
}