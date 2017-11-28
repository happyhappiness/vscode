void
DelayTaggedStatsWalkee(DelayTaggedBucket::Pointer const &current, void *state)
{
    current->stats ((StoreEntry *)state);
}