void *operator new(size_t size)
{
    return xmalloc(size);
}