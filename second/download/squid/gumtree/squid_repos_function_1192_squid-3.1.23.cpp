void
memFree(void *p, int type)
{
    MemPools[type]->free(p);
}