void
MemPoolMalloc::deallocate(void *obj, bool aggressive)
{
    memMeterDec(meter.inuse);
    if (aggressive) {
        xfree(obj);
        memMeterDec(meter.alloc);
    } else {
        if (doZero)
            memset(obj, 0, obj_size);
        memMeterInc(meter.idle);
        freelist.push(obj);
    }
}