static void
check_init(void)
{
    int B = 0, I = 0;
    /* calloc the ptrs so that we don't see them when hunting lost memory */
    malloc_ptrs = calloc(DBG_ARRY_BKTS, sizeof(*malloc_ptrs));

    for (B = 0; B < DBG_ARRY_BKTS; B++) {
        for (I = 0; I < DBG_ARRY_SZ; I++) {
            malloc_ptrs[B][I] = NULL;
            malloc_size[B][I] = 0;
#if XMALLOC_TRACE

            malloc_file[B][I] = NULL;
            malloc_line[B][I] = 0;
            malloc_count[B][I] = 0;
#endif

        }
    }

    dbg_initd = 1;
}