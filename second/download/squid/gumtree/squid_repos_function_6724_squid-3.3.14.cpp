MemImplementingAllocator *
MemPools::create(const char *label, size_t obj_size)
{
    ++poolCount;
    if (defaultIsChunked)
        return new MemPoolChunked (label, obj_size);
    else
        return new MemPoolMalloc (label, obj_size);
}