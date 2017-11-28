void
malloc_statistics(void (*func) (int, int, int, void *), void *data)
{
    int i;

    for (i = 0; i <= DBG_SPLIT; i += DBG_GRAIN_SM)
        func(i, malloc_sizes[DBG_INDEX(i)], malloc_histo[DBG_INDEX(i)], data);

    i -= DBG_GRAIN_SM;

    for (i = i; i <= DBG_MAXSIZE; i += DBG_GRAIN)
        func(i, malloc_sizes[DBG_INDEX(i)], malloc_histo[DBG_INDEX(i)], data);

    xmemcpy(&malloc_histo, &malloc_sizes, sizeof(malloc_sizes));
}