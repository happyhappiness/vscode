void *
memAllocate(mem_type type)
{
    assert(MemPools[type]);
    return MemPools[type]->alloc();
}