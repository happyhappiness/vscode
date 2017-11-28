void *operator new[] (size_t size) throw (std::bad_alloc)
{
    return xmalloc(size);
}