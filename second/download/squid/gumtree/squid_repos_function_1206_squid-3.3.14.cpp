void
DelayBucket::stats(StoreEntry *entry)const
{
    storeAppendPrintf(entry, "%d", level());
}