
    /* Compute how much memory we need to free. */
    mem_tofree = mem_used - server.maxmemory;
    printf("USED: %zu, TOFREE: %zu\n", mem_used, mem_tofree);
    mem_freed = 0;
    while (mem_freed < mem_tofree) {
        int j, k, keys_freed = 0;
