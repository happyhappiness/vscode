void
MemPoolMalloc::clean(time_t maxage)
{
    while (!freelist.empty()) {
        void *obj = freelist.top();
        freelist.pop();
        memMeterDec(meter.idle);
        memMeterDec(meter.alloc);
        xfree(obj);
    }
}