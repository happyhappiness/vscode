static void
squidaio_xstrfree(char *str)
{
    MemAllocator *pool;
    int len = strlen(str) + 1;

    if ((pool = squidaio_get_pool(len)) != NULL) {
        pool->freeOne(str);
    } else
        xfree(str);
}