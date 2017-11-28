static MemAllocator &
GetStrPool(size_t type)
{
    static MemAllocator *strPools[mem_str_pool_count];
    static bool initialized = false;

    static const PoolMeta PoolAttrs[mem_str_pool_count] = {
        {"Short Strings", MemAllocator::RoundedSize(36)},      /* to fit rfc1123 and similar */
        {"Medium Strings", MemAllocator::RoundedSize(128)},    /* to fit most urls */
        {"Long Strings", MemAllocator::RoundedSize(512)},
        {"1KB Strings", MemAllocator::RoundedSize(1024)},
        {"4KB Strings", MemAllocator::RoundedSize(4*1024)},
        {"16KB Strings", MemAllocator::RoundedSize(16*1024)}
    };

    if (!initialized) {
        memset(strPools, '\0', sizeof(strPools));

        /** Lastly init the string pools. */
        for (int i = 0; i < mem_str_pool_count; ++i) {
            strPools[i] = memPoolCreate(PoolAttrs[i].name, PoolAttrs[i].obj_size);
            strPools[i]->zeroBlocks(false);

            if (strPools[i]->objectSize() != PoolAttrs[i].obj_size)
                debugs(13, DBG_IMPORTANT, "NOTICE: " << PoolAttrs[i].name <<
                       " is " << strPools[i]->objectSize() <<
                       " bytes instead of requested " <<
                       PoolAttrs[i].obj_size << " bytes");
        }

        initialized = true;
    }

    return *strPools[type];
}