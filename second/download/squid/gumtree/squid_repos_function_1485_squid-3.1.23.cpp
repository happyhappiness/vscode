void
ClassCBucket::stats(StoreEntry *sentry)const
{
    for (unsigned int j = 0; j < individuals.size(); ++j) {
        assert (individualUsed (j));
        storeAppendPrintf(sentry, " %d:",individuals.key_map[j]);
        individuals.values[j].stats (sentry);
    }
}