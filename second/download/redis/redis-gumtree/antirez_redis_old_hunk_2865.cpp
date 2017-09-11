    /* Compute how much memory we need to free. */
    mem_tofree = mem_used - server.maxmemory;
    mem_freed = 0;
    if (debug) printf("tofree: %zu\n", mem_tofree);
    while (mem_freed < mem_tofree) {
        int j, k, keys_freed = 0;

