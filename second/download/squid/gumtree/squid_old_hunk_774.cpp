
DelayTagged::DelayTagged()
{
    DelayPools::registerForUpdates (this);
}

static SplayNode<DelayTaggedBucket::Pointer>::SPLAYFREE DelayTaggedFree;

DelayTagged::~DelayTagged()
{
    DelayPools::deregisterForUpdates (this);
    buckets.head->destroy (DelayTaggedFree);
}

static SplayNode<DelayTaggedBucket::Pointer>::SPLAYCMP DelayTaggedCmp;

int
DelayTaggedCmp(DelayTaggedBucket::Pointer const &left, DelayTaggedBucket::Pointer const &right)
{
    /* for rate limiting, case insensitive */
    return left->tag.caseCmp(right->tag);
}

void
DelayTaggedFree(DelayTaggedBucket::Pointer &)
{}

void
DelayTaggedStatsWalkee(DelayTaggedBucket::Pointer const &current, void *state)
{
    current->stats ((StoreEntry *)state);
}

void
DelayTagged::stats(StoreEntry * sentry)
{
    spec.stats (sentry, "Per Tag");

    if (spec.restore_bps == -1)
        return;

    storeAppendPrintf(sentry, "\t\tCurrent: ");

    if (!buckets.head) {
        storeAppendPrintf (sentry, "Not used yet.\n\n");
        return;
    }

    buckets.head->walk(DelayTaggedStatsWalkee, sentry);
    storeAppendPrintf(sentry, "\n\n");
}

void
DelayTagged::dump(StoreEntry *entry) const
{
