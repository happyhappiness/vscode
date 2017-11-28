void
squidaio_xfree(void *p, int size)
{
    MemAllocator *pool;

    if ((pool = squidaio_get_pool(size)) != NULL) {
        pool->free(p);
    } else
        xfree(p);
}