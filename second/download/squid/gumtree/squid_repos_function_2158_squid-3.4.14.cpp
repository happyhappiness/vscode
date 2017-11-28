void
xprof_summary(StoreEntry * sentry)
{
    hrtime_t now = get_tick();

    storeAppendPrintf(sentry, "CPU Profiling Statistics:\n");
    storeAppendPrintf(sentry,
                      "  (CPU times are in arbitrary units, most probably in CPU clock ticks)\n");
    storeAppendPrintf(sentry,
                      "Probe Name\t Event Count\t last Interval \t Avg Interval \t since squid start \t (since system boot) \n");
    storeAppendPrintf(sentry, "Total\t %lu\t %" PRIu64 " \t %" PRIu64 " \t %" PRIu64 " \t %" PRIu64 "\n",
                      (long unsigned) xprof_events,
                      xprof_delta,
                      xprof_average_delta,
                      now - xprof_verystart,
                      now);

    xprof_summary_item(sentry, "Last 1 sec averages", xprof_stats_avg1sec);
    xprof_summary_item(sentry, "Last 5 sec averages", xprof_stats_avg5sec);
    xprof_summary_item(sentry, "Last 30 sec averages", xprof_stats_avg30sec);
    xprof_summary_item(sentry, "Last 1 min averages", xprof_stats_avg1min);
    xprof_summary_item(sentry, "Last 5 min averages", xprof_stats_avg5min);
    xprof_summary_item(sentry, "Last 30 min averages", xprof_stats_avg30min);
    xprof_summary_item(sentry, "Last 1 hour averages", xprof_stats_avg1hour);
    xprof_summary_item(sentry, "Last 5 hour averages", xprof_stats_avg5hour);
    xprof_summary_item(sentry, "Last 24 hour averages", xprof_stats_avg24hour);
}