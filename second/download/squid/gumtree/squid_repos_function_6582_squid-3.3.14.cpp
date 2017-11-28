static char *
malloc_file_name(void *p)
{
    int B, I;
    B = DBG_HASH_BUCKET(p);

    for (I = 0; I < DBG_ARRY_SZ; ++I) {
        if (malloc_ptrs[B][I] == p)
            return malloc_file[B][I];
    }

    return 0;
}