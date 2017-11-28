
DelayTagged::DelayTagged()
{
    DelayPools::registerForUpdates (this);
}

static Splay<DelayTaggedBucket::Pointer>::SPLAYFREE DelayTaggedFree;

DelayTagged::~DelayTagged()
{
    DelayPools::deregisterForUpdates (this);
    buckets.destroy(DelayTaggedFree);
}

static Splay<DelayTaggedBucket::Pointer>::SPLAYCMP DelayTaggedCmp;

int
DelayTaggedCmp(DelayTaggedBucket::Pointer const &left, DelayTaggedBucket::Pointer const &right)
{
    /* for rate limiting, case insensitive */
    return left->tag.caseCmp(right->tag);
}

void
DelayTaggedFree(DelayTaggedBucket::Pointer &)
{}

struct DelayTaggedStatsVisitor {
    StoreEntry *sentry;
    explicit DelayTaggedStatsVisitor(StoreEntry *se): sentry(se) {}
    void operator() (DelayTaggedBucket::Pointer const &current) {
        current->stats(sentry);
    }
};

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

void
DelayTagged::dump(StoreEntry *entry) const
{
