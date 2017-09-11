int freeMemoryIfNeeded(void) {
    size_t mem_used, mem_tofree, mem_freed;
    int slaves = listLength(server.slaves);
    static time_t xt;
    int debug = 0;

    if (xt != time(NULL)) {
        debug = 1;
        xt = time(NULL);
    }

    /* Remove the size of slaves output buffers and AOF buffer from the
     * count of used memory. */
    mem_used = zmalloc_used_memory();
    if (debug) printf("used_full: %zu\n", mem_used);
    if (slaves) {
        listIter li;
        listNode *ln;
