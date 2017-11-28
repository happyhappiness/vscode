size_t
xmallocblksize(void *p)
{
    int B, I;
    B = DBG_HASH_BUCKET(p);

    for (I = 0; I < DBG_ARRY_SZ; I++) {
        if (malloc_ptrs[B][I] == p)
            return malloc_size[B][I];
    }

    return 0;
}