size_t
memStringCount()
{
    size_t result = 0;

    for (int counter = 0; counter < mem_str_pool_count; ++counter)
        result += memPoolInUseCount(StrPools[counter].pool);

    return result;
}