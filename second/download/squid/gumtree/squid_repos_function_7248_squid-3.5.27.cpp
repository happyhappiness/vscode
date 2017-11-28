void *
MemPoolChunked::allocate()
{
    void *p = get();
    assert(meter.idle.level > 0);
    memMeterDec(meter.idle);
    memMeterInc(meter.inuse);
    return p;
}