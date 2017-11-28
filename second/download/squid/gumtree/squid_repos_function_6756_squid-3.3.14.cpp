int
MemPoolMalloc::getInUseCount()
{
    return meter.inuse.level;
}