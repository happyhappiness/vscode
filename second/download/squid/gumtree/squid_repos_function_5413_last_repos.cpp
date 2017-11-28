static MemAllocator *&
GetPool(size_t type)
{
    static MemAllocator *pools[MEM_MAX];
    static bool initialized = false;

    if (!initialized) {
        memset(pools, '\0', sizeof(pools));
        initialized = true;
        // Mem::Init() makes use of GetPool(type) to initialize
        // the actual pools. So must come after the flag is true
        Mem::Init();
    }

    return pools[type];
}