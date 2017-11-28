void
memDataInit(mem_type type, const char *name, size_t size, int max_pages_notused, bool zeroOnPush)
{
    assert(name && size);

    if (MemPools[type] != NULL)
        return;

    MemPools[type] = memPoolCreate(name, size);
    MemPools[type]->zeroOnPush(zeroOnPush);
}