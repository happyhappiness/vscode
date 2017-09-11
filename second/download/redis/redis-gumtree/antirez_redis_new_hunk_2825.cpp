    long elements;
    int root = 0;

    /* Set error for nested multi bulks with depth > 2 */
    if (r->ridx == 3) {
        __redisReaderSetError(r,REDIS_ERR_PROTOCOL,
            "No support for nested multi bulk replies with depth > 2");
        return REDIS_ERR;
    }

    if ((p = readLine(r,NULL)) != NULL) {
