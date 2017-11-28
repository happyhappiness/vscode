void *
MemPoolMalloc::allocate()
{
    void *obj = NULL;
    if (!freelist.empty()) {
        obj = freelist.top();
        freelist.pop();
    }
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