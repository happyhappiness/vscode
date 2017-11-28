static void
stat_init(void)
{
    for (int i = 0; i <= XMS_DBG_MAXINDEX; ++i)
        malloc_sizes[i] = malloc_histo[i] = 0;

    dbg_stat_init = 1;
}