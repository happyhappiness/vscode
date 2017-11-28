static void
check_free(void *s)
{
    int B, I;
    B = DBG_HASH_BUCKET(s);

    for (I = 0; I < DBG_ARRY_SZ; ++I) {
        if (malloc_ptrs[B][I] != s)
            continue;

        malloc_ptrs[B][I] = NULL;
        malloc_size[B][I] = 0;
        break;
    }

    if (I == DBG_ARRY_SZ) {
        static char msg[128];
        snprintf(msg, 128, "xfree: ERROR: s=%p not found!", s);
        if (failure_notify)
            (*failure_notify) (msg);
        else
            perror(msg);
    }
}