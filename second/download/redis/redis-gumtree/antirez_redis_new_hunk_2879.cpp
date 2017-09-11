/* ============================ Maxmemory directive  ======================== */

/* This function gets called when 'maxmemory' is set on the config file to limit
 * the max memory used by the server, before processing a command.
 *
 * The goal of the function is to free enough memory to keep Redis under the
 * configured memory limit.
 *
 * The function starts calculating how many bytes should be freed to keep
 * Redis under the limit, and enters a loop selecting the best keys to
 * evict accordingly to the configured policy.
 *
 * If all the bytes needed to return back under the limit were freed the
 * function returns REDIS_OK, otherwise REDIS_ERR is returned, and the caller
 * should block the execution of commands that will result in more memory
 * used by the server.
 */
int freeMemoryIfNeeded(void) {
    size_t mem_used, mem_tofree, mem_freed;
    int slaves = listLength(server.slaves);

    /* Remove the size of slaves output buffers from the count of used
     * memory. */
    mem_used = zmalloc_used_memory();
    if (slaves) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            redisClient *slave = listNodeValue(ln);
            unsigned long obuf_bytes = getClientOutputBufferMemoryUsage(slave);
            if (obuf_bytes > mem_used)
                mem_used = 0;
            else
                mem_used -= obuf_bytes;
        }
    }

    /* Check if we are over the memory limit. */
    if (mem_used <= server.maxmemory) return REDIS_OK;

    if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION)
        return REDIS_ERR; /* We need to free memory, but policy forbids. */

    /* Compute how much memory we need to free. */
    mem_tofree = mem_used - server.maxmemory;
    printf("USED: %zu, TOFREE: %zu\n", mem_used, mem_tofree);
    mem_freed = 0;
    while (mem_freed < mem_tofree) {
        int j, k, keys_freed = 0;

        for (j = 0; j < server.dbnum; j++) {
            long bestval = 0; /* just to prevent warning */
