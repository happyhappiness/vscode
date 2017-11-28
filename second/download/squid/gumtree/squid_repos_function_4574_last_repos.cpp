int64_t
Store::Controller::accumulateMore(StoreEntry &entry) const
{
    return swapDir ? swapDir->accumulateMore(entry) : 0;
    // The memory cache should not influence for-swapout accumulation decision.
}