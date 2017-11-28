void
MemPoolMalloc::clean(time_t maxage)
{
    while (void *obj = freelist.pop()) {
        memMeterDec(meter.idle);
        memMeterDec(meter.alloc);
        xfree(obj);
    }
}