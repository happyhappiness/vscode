void
xprof_event(void *data)
{
    now = get_tick();
    xprof_Init();
    xprof_delta = now - xprof_start_t;
    xprof_start_t = now;
    ++xprof_events;

    if (!xprof_average_delta)
        xprof_average_delta = xprof_delta;

    if (xprof_average_delta > (xprof_delta >> 1))
        xprof_average_delta = xprof_average_delta - (xprof_average_delta >> 8) + (xprof_delta >> 8);

    xprof_chk_overhead(2);

    xprof_average(&xprof_stats_avg24hour, 24 * 3600);

    xprof_average(&xprof_stats_avg5hour, 5 * 3600);

    xprof_average(&xprof_stats_avg1hour, 3600);

    xprof_average(&xprof_stats_avg30min, 1800);

    xprof_average(&xprof_stats_avg5min, 300);

    xprof_average(&xprof_stats_avg1min, 60);

    xprof_average(&xprof_stats_avg30sec, 30);

    xprof_average(&xprof_stats_avg5sec, 5);

    xprof_average(&xprof_stats_avg1sec, 1);

    xprof_chk_overhead(30);

    eventAdd("cpuProfiling", xprof_event, NULL, 1.0, 1);
}