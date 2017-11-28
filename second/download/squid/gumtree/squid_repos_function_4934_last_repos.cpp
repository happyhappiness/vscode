int64_t
Rock::SwapDir::slotLimitActual() const
{
    const int64_t sWanted = (maxSize() - HeaderSize)/slotSize;
    const int64_t sLimitLo = map ? map->sliceLimit() : 0; // dynamic shrinking unsupported
    const int64_t sLimitHi = slotLimitAbsolute();
    return min(max(sLimitLo, sWanted), sLimitHi);
}