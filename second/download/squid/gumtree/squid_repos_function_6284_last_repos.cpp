void *
squidaio_xmalloc(int size)
{
    void *p;
    MemAllocator *pool;

    if ((pool = squidaio_get_pool(size)) != NULL) {
        p = pool->alloc();
    } else
        p = xmalloc(size);

    return p;
}