static void
check_malloc(void *p, size_t sz)
{
    void *P, *Q;
    int B, I;

    if (!dbg_initd)
        check_init();

    B = DBG_HASH_BUCKET(p);

    for (I = 0; I < DBG_ARRY_SZ; ++I) {
        if (!(P = malloc_ptrs[B][I]))
            continue;

        Q = P + malloc_size[B][I];

        if (P <= p && p < Q) {
            static char msg[128];
            snprintf(msg, 128, "xmalloc: ERROR: p=%p falls in P=%p+%d",
                     p, P, malloc_size[B][I]);
            if (failure_notify)
                (*failure_notify) (msg);
            else
                perror(msg);
        }
    }

    for (I = 0; I < DBG_ARRY_SZ; ++I) {
        if (malloc_ptrs[B][I])
            continue;

        malloc_ptrs[B][I] = p;

        malloc_size[B][I] = (int) sz;

#if XMALLOC_TRACE

        malloc_file[B][I] = xmalloc_file;

        malloc_line[B][I] = xmalloc_line;

        malloc_count[B][I] = xmalloc_count;

#endif

        break;
    }

    if (I == DBG_ARRY_SZ) {
        if (failure_notify)
            (*failure_notify) ("xmalloc: debug out of array space!");
        else
            perror("xmalloc: debug out of array space!");
    }
}