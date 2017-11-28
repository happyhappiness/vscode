void
memDataInit(mem_type type, const char *name, size_t size, int max_pages_notused, bool zeroOnPush)
{
    assert(name && size);
    assert(MemPools[type] == NULL);
    MemPools[type] = memPoolCreate(name, size);
    MemPools[type]->zeroOnPush(zeroOnPush);
}