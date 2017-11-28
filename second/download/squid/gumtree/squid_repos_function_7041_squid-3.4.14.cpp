void
malloc_statistics(void (*func) (int, int, int, void *), void *data)
{
    int i = 0;

    for (; i <= XMS_DBG_SPLIT; i += XMS_DBG_GRAIN_SM)
        func(i, malloc_sizes[XMS_DBG_INDEX(i)], malloc_histo[XMS_DBG_INDEX(i)], data);

    i -= XMS_DBG_GRAIN_SM;

    for (; i <= XMS_DBG_MAXSIZE; i += XMS_DBG_GRAIN)
        func(i, malloc_sizes[XMS_DBG_INDEX(i)], malloc_histo[XMS_DBG_INDEX(i)], data);

    memcpy(&malloc_histo, &malloc_sizes, sizeof(malloc_sizes));
}