size_t
memStringCount()
{
    size_t result = 0;

    for (int counter = 0; counter < mem_str_pool_count; ++counter)
        result += GetStrPool(counter).inUseCount();

    return result;
}