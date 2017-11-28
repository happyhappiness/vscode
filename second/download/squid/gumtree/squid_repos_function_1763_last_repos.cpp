static void
xprof_sorthist(TimersArray * xprof_list)
{
    for (int i = 0; i < XPROF_LAST; ++i) {
        sortlist[i] = xprof_list[i];
    }

    qsort(&sortlist[XPROF_PROF_UNACCOUNTED+1], XPROF_LAST - XPROF_PROF_UNACCOUNTED+1, sizeof(xprof_stats_node *), xprof_comp);
}