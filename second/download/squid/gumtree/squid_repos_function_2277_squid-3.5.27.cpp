static void
xprof_reset(xprof_stats_data * head)
{
    head->summ = 0;
    head->count = 0;
    head->delta = 0;
    head->best = XP_NOBEST;
    head->worst = 0;
    head->start = 0;
    head->stop = 0;
}