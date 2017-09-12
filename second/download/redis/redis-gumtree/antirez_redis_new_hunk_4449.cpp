    if (outv != static_outv) zfree(outv);
}

static void processInputBuffer(redisClient *c) {
again:
    if (c->bulklen == -1) {
        /* Read the first line of the query */
