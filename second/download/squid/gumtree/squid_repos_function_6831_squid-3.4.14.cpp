void *
MemPoolMalloc::allocate()
{
    void *obj = freelist.pop();
    if (obj) {
        memMeterDec(meter.idle);
        ++saved_calls;
    } else {
        if (doZero)
            obj = xcalloc(1, obj_size);
        else
            obj = xmalloc(obj_size);
        memMeterInc(meter.alloc);
    }
    memMeterInc(meter.inuse);
    return obj;
}