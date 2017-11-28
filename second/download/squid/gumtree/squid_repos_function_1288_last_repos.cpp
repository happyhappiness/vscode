void
ClassCHostPool::stats(StoreEntry * sentry)
{
    rate()->stats (sentry, label());

    if (rate()->restore_bps == -1) {
        storeAppendPrintf(sentry, "\n\n");
        return;
    }

    for (unsigned int index = 0; index < buckets.size(); ++index) {
        storeAppendPrintf(sentry, "\t\tCurrent [Network %d]:", buckets.key_map[index]);
        buckets.values[index].stats (sentry);
        storeAppendPrintf(sentry, "\n");
    }

    if (!buckets.size())
        storeAppendPrintf(sentry, "\t\tCurrent [All networks]: Not used yet.\n");

    storeAppendPrintf(sentry, "\n\n");
}