    if (aeCreateFileEvent(server.el, server.io_ready_pipe_read, AE_READABLE,
        vmThreadedIOCompletedJob, NULL) == AE_ERR)
        oom("creating file event");

    /* Spawn our I/O thread */
    spawnIOThread();
}

/* Compute how good candidate the specified object is for eviction.
 * An higher number means a better candidate. */
double computeObjectSwappability(robj *o) {
    /* actual age can be >= minage, but not < minage. As we use wrapping
     * 21 bit clocks with minutes resolution for the LRU. */
    return (double) estimateObjectIdleTime(o);
}

/* Try to free one entry from the diskstore object cache */
int cacheFreeOneEntry(void) {
    int j, i;
    struct dictEntry *best = NULL;
    double best_swappability = 0;
