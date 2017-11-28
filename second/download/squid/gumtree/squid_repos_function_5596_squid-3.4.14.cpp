void
squidaio_xfree(void *p, int size)
{
    MemAllocator *pool;

    if ((pool = squidaio_get_pool(size)) != NULL) {
        pool->freeOne(p);
    } else
        xfree(p);
}