void
DelayUser::stats(StoreEntry * sentry)
{
    spec.stats (sentry, "Per User");

    if (spec.restore_bps == -1)
        return;

    storeAppendPrintf(sentry, "\t\tCurrent: ");

    if (!buckets.head) {
        storeAppendPrintf (sentry, "Not used yet.\n\n");
        return;
    }

    buckets.head->walk(DelayUserStatsWalkee, sentry);
    storeAppendPrintf(sentry, "\n\n");
}