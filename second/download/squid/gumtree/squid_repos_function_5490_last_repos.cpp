void
MemPoolMalloc::clean(time_t)
{
    while (!freelist.empty()) {
        void *obj = freelist.top();
        freelist.pop();
        --meter.idle;
        --meter.alloc;
        xfree(obj);
    }
}