void
DelayTaggedBucket::stats(StoreEntry *entry) const
{
    storeAppendPrintf(entry, " " SQUIDSTRINGPH ":", SQUIDSTRINGPRINT(tag));
    theBucket.stats(entry);
}