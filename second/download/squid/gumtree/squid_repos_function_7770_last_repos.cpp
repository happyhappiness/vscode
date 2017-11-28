static void
xprof_InitLib(void)
{
    if (xprof_inited)
        return;

    xprof_Timers = static_cast<TimersArray *>(calloc(XPROF_LAST + 2, sizeof(xprof_stats_node)));

    xprof_Timers[XPROF_PROF_UNACCOUNTED]->name = "PROF_UNACCOUNTED";
    xprof_Timers[XPROF_PROF_UNACCOUNTED]->accu.start = get_tick();
    xp_UNACCOUNTED = &xprof_Timers[XPROF_PROF_UNACCOUNTED]->accu;
    cstack_head = 0;
    xprof_inited = 1;
}