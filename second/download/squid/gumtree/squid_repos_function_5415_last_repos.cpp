static mem_type
memFindStringSizeType(size_t net_size, bool fuzzy)
{
    mem_type type = MEM_NONE;
    for (unsigned int i = 0; i < mem_str_pool_count; ++i) {
        auto &pool = GetStrPool(i);
        if (fuzzy && net_size < pool.objectSize()) {
            type = static_cast<mem_type>(i);
            break;
        } else if (net_size == pool.objectSize()) {
            type = static_cast<mem_type>(i);
            break;
        }
    }

    return type;
}