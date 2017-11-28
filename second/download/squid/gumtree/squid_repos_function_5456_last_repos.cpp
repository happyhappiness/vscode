void *
MemPoolChunked::allocate()
{
    void *p = get();
    assert(meter.idle.currentLevel() > 0);
    --meter.idle;
    ++meter.inuse;
    return p;
}