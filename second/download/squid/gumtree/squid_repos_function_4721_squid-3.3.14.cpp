void *
memAllocString(size_t net_size, size_t * gross_size)
{
    *gross_size=net_size;
    return xmalloc(net_size);
}