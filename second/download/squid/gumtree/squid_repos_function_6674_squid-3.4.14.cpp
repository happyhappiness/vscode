int
MemPoolChunked::getInUseCount()
{
    return meter.inuse.level;
}