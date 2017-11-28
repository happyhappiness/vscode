int
malloc_number(void *p)
{
    int B, I;
    B = DBG_HASH_BUCKET(p);

    for (I = 0; I < DBG_ARRY_SZ; ++I) {
        if (malloc_ptrs[B][I] == p)
            return malloc_count[B][I];
    }

    return 0;
}