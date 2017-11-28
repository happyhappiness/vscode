void
MemPoolMalloc::deallocate(void *obj, bool aggressive)
{
    --meter.inuse;
    if (aggressive) {
        xfree(obj);
        --meter.alloc;
    } else {
        if (doZero)
            memset(obj, 0, obj_size);
        ++meter.idle;
        freelist.push(obj);
    }
}