void
VectorPool::stats(StoreEntry * sentry)
{
    rate()->stats (sentry, label());

    if (rate()->restore_bps == -1) {
        storeAppendPrintf(sentry, "\n\n");
        return;
    }

    storeAppendPrintf(sentry, "\t\tCurrent:");

    for (unsigned int i = 0; i < buckets.size(); ++i) {
        storeAppendPrintf(sentry, " %d:", buckets.key_map[i]);
        buckets.values[i].stats(sentry);
    }

    if (!buckets.size())
        storeAppendPrintf(sentry, " Not used yet.");

    storeAppendPrintf(sentry, "\n\n");
}