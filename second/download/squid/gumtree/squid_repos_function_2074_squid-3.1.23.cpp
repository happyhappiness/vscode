static void
xprof_summary_item(StoreEntry * sentry, char const *descr, TimersArray * list)
{
    int i;
    xprof_stats_node **hist;
    xprof_stats_data *show;
    xprof_reset(&Totals);
    xprof_sorthist(list);
    hist = &sortlist[0];

    show = &hist[0]->hist;

    if (!hist[0]->hist.delta)
        show = &hist[0]->accu;

    time_frame = (double) show->delta / (double) xprof_average_delta;

    storeAppendPrintf(sentry, "\n%s:", descr);

    storeAppendPrintf(sentry, " (Cumulated time: %" PRIu64 ", %.2f sec)\n",
                      show->delta,
                      time_frame
                     );

    storeAppendPrintf(sentry,
                      "Probe Name\t  Events\t cumulated time \t best case \t average \t worst case\t Rate / sec \t %% in int\n");

    for (i = 0; i < XPROF_LAST; i++) {
        if (!hist[i]->name)
            continue;

        show = &hist[i]->hist;

        if (!show->count)
            continue;

        xprof_show_item(sentry, hist[i]->name, show);

        Totals.count += show->count;

        Totals.summ += show->summ;

        Totals.best += (show->best != XP_NOBEST ? show->best : 0);

        Totals.worst += show->worst;

        Totals.delta = (show->delta > Totals.delta ? show->delta : Totals.delta);
    }

    xprof_show_item(sentry, "TOTALS", &Totals);
}