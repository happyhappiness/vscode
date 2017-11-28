bool
MemPoolChunked::idleTrigger(int shift) const
{
    return meter.idle.level > (chunk_capacity << shift);
}