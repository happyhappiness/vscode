int
MemPoolMalloc::getInUseCount()
{
    return meter.inuse.currentLevel();
}