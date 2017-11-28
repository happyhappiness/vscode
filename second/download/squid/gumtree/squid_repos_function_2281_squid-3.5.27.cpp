static void
xprof_show_item(StoreEntry * sentry, const char *name, xprof_stats_data * hist)
{
    storeAppendPrintf(sentry,
                      "%s\t %" PRIu64 "\t %" PRIu64 "\t %" PRIu64 "\t %" PRIu64 "\t %" PRIu64 "\t %.2f\t %6.3f\t\n",
                      name,
                      hist->count,
                      hist->summ,
                      (hist->best != XP_NOBEST ? hist->best : 0),
                      hist->count ? hist->summ / hist->count : 0,
                      hist->worst,
                      hist->count / time_frame,
                      Math::doublePercent((double) hist->summ, (double) hist->delta));
}