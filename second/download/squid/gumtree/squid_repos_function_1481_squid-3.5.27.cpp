void
DelayUser::stats(StoreEntry * sentry)
{
    spec.stats (sentry, "Per User");

    if (spec.restore_bps == -1)
        return;

    storeAppendPrintf(sentry, "\t\tCurrent: ");

    if (buckets.empty()) {
        storeAppendPrintf (sentry, "Not used yet.\n\n");
        return;
    }

    DelayUserStatsVisitor visitor(sentry);
    buckets.visit(visitor);
    storeAppendPrintf(sentry, "\n\n");
}