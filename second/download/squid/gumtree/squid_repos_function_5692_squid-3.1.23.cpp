static void
stat_init(void)
{
    int i;

    for (i = 0; i <= DBG_MAXINDEX; i++)
        malloc_sizes[i] = malloc_histo[i] = 0;

    dbg_stat_init = 1;
}