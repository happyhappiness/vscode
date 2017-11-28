uint64_t
Store::Disk::minSize() const
{
    // XXX: Not all disk stores use Config.Swap.lowWaterMark
    return ((maxSize() * Config.Swap.lowWaterMark) / 100);
}