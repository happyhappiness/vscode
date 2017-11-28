void *
memAllocate(mem_type type)
{
    return MemPools[type]->alloc();
}