void
MemPoolChunked::deallocate(void *obj, bool)
{
    push(obj);
    assert(meter.inuse.currentLevel() > 0);
    --meter.inuse;
    ++meter.idle;
}