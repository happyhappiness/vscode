void *
MemPoolMalloc::allocate()
{
    void *obj = freelist.pop();
    if (obj) {
        memMeterDec(meter.idle);
        saved_calls++;
    } else {
        obj = xcalloc(1, obj_size);
        memMeterInc(meter.alloc);
    }
    memMeterInc(meter.inuse);
    return obj;
}