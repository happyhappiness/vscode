int64_t
Rock::SwapDir::entryLimitAllowed() const
{
    const int64_t eLimitLo = map ? map->entryLimit() : 0; // dynamic shrinking unsupported
    const int64_t eWanted = (maxSize() - HeaderSize)/maxObjectSize();
    return min(max(eLimitLo, eWanted), entryLimitHigh());
}