void
DelayTagged::stats(StoreEntry * sentry)
{
    spec.stats (sentry, "Per Tag");

    if (spec.restore_bps == -1)
        return;

    storeAppendPrintf(sentry, "\t\tCurrent: ");

    if (buckets.empty()) {
        storeAppendPrintf (sentry, "Not used yet.\n\n");
        return;
    }

    DelayTaggedStatsVisitor visitor(sentry);
    buckets.visit(visitor);
    storeAppendPrintf(sentry, "\n\n");
}