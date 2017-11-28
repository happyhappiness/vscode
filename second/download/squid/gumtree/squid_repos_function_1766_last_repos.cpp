static void
xprof_average(TimersArray ** list, int secs)
{
    int i;
    TimersArray *head = xprof_Timers;
    TimersArray *hist;
    hrtime_t now;
    hrtime_t keep;
    int doavg = (xprof_events % secs);

    if (!*list)
        *list = (TimersArray *)xcalloc(XPROF_LAST, sizeof(xprof_stats_node));

    hist = *list;

    now = get_tick();

    for (i = 0; i < XPROF_LAST; ++i) {
        hist[i]->name = head[i]->name;
        hist[i]->accu.summ += head[i]->accu.summ;
        hist[i]->accu.count += head[i]->accu.count; /* accumulate multisec */

        if (!hist[i]->accu.best)
            hist[i]->accu.best = head[i]->accu.best;

        if (hist[i]->accu.best > head[i]->accu.best)
            hist[i]->accu.best = head[i]->accu.best;

        if (hist[i]->accu.worst < head[i]->accu.worst)
            hist[i]->accu.worst = head[i]->accu.worst;

        hist[i]->accu.delta += xprof_delta;

        if (!doavg) {
            /* we have X seconds accumulated */
            xprof_move(&hist[i]->accu, &hist[i]->hist);
            xprof_reset(&hist[i]->accu);

            hist[i]->accu.start = now;
        }

        /* reset 0sec counters */
        if (secs == 1) {
            keep = head[i]->accu.start;
            xprof_move(&head[i]->accu, &head[i]->hist);
            xprof_reset(&head[i]->accu);
            hist[i]->accu.delta = 0;
            head[i]->accu.start = keep;
        }
    }
}