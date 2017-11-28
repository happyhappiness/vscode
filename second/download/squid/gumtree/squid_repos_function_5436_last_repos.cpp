int
memInUse(mem_type type)
{
    return GetPool(type)->inUseCount();
}