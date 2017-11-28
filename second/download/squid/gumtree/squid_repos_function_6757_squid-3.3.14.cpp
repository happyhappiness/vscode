bool
MemPoolMalloc::idleTrigger(int shift) const
{
    return freelist.count >> (shift ? 8 : 0);
}