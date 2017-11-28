uint64_t
SwapDir::minSize() const
{
    return ((maxSize() * Config.Swap.lowWaterMark) / 100);
}