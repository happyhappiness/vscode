static void
check_free(void *s)
{
    int B, I;
    B = DBG_HASH_BUCKET(s);

    for (I = 0; I < DBG_ARRY_SZ; I++) {
        if (malloc_ptrs[B][I] != s)
            continue;

        malloc_ptrs[B][I] = NULL;

        malloc_size[B][I] = 0;

#if XMALLOC_TRACE

        malloc_file[B][I] = NULL;

        malloc_line[B][I] = 0;

        malloc_count[B][I] = 0;

#endif

        break;
    }

    if (I == DBG_ARRY_SZ) {
        snprintf(msg, 128, "xfree: ERROR: s=%p not found!", s);
        (*failure_notify) (msg);
    }
}