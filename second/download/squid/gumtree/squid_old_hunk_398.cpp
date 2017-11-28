DelayTaggedBucket::~DelayTaggedBucket()
{
    debugs(77, 3, "DelayTaggedBucket::~DelayTaggedBucket");
}

void
DelayTaggedBucket::stats (StoreEntry *entry) const
{
    storeAppendPrintf(entry, " :" SQUIDSTRINGPH , SQUIDSTRINGPRINT(tag));
    theBucket.stats (entry);
}

DelayTagged::Id::Id(DelayTagged::Pointer aDelayTagged, String &aTag) : theTagged(aDelayTagged)
{
    theBucket = new DelayTaggedBucket(aTag);
    DelayTaggedBucket::Pointer const *existing = theTagged->buckets.find(theBucket, DelayTaggedCmp);
