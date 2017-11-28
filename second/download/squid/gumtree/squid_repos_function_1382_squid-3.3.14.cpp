void
DelayUserBucket::stats (StoreEntry *entry) const
{
    storeAppendPrintf(entry, " %s:", authUser->username());
    theBucket.stats(entry);
}