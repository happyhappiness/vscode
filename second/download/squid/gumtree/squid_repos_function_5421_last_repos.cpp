void
memFree(void *p, int type)
{
    assert(GetPool(type));
    GetPool(type)->freeOne(p);
}