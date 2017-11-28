bool
MemPoolChunked::idleTrigger(int shift) const
{
    return meter.idle.currentLevel() > (chunk_capacity << shift);
}