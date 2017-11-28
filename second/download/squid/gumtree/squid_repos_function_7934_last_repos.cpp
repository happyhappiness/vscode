static int
malloc_stat(int sz)
{
    if (!dbg_stat_init)
        stat_init();

    return malloc_sizes[XMS_DBG_INDEX(sz)] += 1;
}