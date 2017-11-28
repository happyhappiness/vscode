void
memFree(void *p, int type)
{
    assert(MemPools[type]);
    MemPools[type]->freeOne(p);
}