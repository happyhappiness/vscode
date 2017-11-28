int
memInUse(mem_type type)
{
    return memPoolInUseCount(MemPools[type]);
}