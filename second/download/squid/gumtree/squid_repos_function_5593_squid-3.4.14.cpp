static MemAllocator *
squidaio_get_pool(int size)
{
    if (size <= AIO_LARGE_BUFS) {
        if (size <= AIO_MICRO_BUFS)
            return squidaio_micro_bufs;
        else if (size <= AIO_TINY_BUFS)
            return squidaio_tiny_bufs;
        else if (size <= AIO_SMALL_BUFS)
            return squidaio_small_bufs;
        else if (size <= AIO_MEDIUM_BUFS)
            return squidaio_medium_bufs;
        else
            return squidaio_large_bufs;
    }

    return NULL;
}