static void
dump_time_msec(StoreEntry * entry, const char *name, time_msec_t var)
{
    if (var % 1000)
        storeAppendPrintf(entry, "%s %" PRId64 " milliseconds\n", name, var);
    else
        storeAppendPrintf(entry, "%s %d seconds\n", name, (int)(var/1000) );
}