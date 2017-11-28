static void
xprof_sorthist(TimersArray * xprof_list)
{
    int i;

    for (i = 0; i < XPROF_LAST; i++) {
        sortlist[i] = xprof_list[i];
    }

    qsort(&sortlist[XPROF_hash_lookup], XPROF_LAST - XPROF_hash_lookup, sizeof(xprof_stats_node *), (QS *) xprof_comp);
}