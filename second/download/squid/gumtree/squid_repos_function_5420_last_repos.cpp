void *
memAllocate(mem_type type)
{
    assert(GetPool(type));
    return GetPool(type)->alloc();
}