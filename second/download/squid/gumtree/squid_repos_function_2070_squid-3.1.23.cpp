static void
xprof_move(xprof_stats_data * head, xprof_stats_data * hist)
{
    memcpy(hist, head, sizeof(xprof_stats_data));
}