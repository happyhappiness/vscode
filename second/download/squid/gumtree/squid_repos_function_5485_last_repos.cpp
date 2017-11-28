void *
MemPoolMalloc::allocate()
{
    void *obj = NULL;
    if (!freelist.empty()) {
        obj = freelist.top();
        freelist.pop();
    }
    if (obj) {
        --meter.idle;
        ++saved_calls;
    } else {
        if (doZero)
            obj = xcalloc(1, obj_size);
        else
            obj = xmalloc(obj_size);
        ++meter.alloc;
    }
    ++meter.inuse;
    return obj;
}