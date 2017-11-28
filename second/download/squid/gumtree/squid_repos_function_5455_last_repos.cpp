int
MemPoolChunked::getInUseCount()
{
    return meter.inuse.currentLevel();
}