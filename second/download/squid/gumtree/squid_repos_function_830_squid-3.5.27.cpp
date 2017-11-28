void *operator new(size_t size, const std::nothrow_t &tag)
{
    return xmalloc(size);
}