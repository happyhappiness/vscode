static void
free_time_t(time_t * var)
{
    *var = 0;
}

#if !USE_DNSHELPER
static void
dump_time_msec(StoreEntry * entry, const char *name, time_msec_t var)
{
    if (var % 1000)
        storeAppendPrintf(entry, "%s %" PRId64 " milliseconds\n", name, var);
    else
