void
DelayUserStatsWalkee(DelayUserBucket::Pointer const &current, void *state)
{
    current->stats ((StoreEntry *)state);
}