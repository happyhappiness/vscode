void
Aggregate::stats(StoreEntry * sentry)
{
    rate()->stats (sentry, "Aggregate");

    if (rate()->restore_bps == -1)
        return;

    storeAppendPrintf(sentry, "\t\tCurrent: ");

    theBucket.stats(sentry);

    storeAppendPrintf(sentry, "\n\n");
}