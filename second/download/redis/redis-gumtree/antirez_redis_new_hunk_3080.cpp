    int root = 0;

    /* Set error for nested multi bulks with depth > 1 */
    if (r->ridx == 8) {
        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "No support for nested multi bulk replies with depth > 7"));
        return -1;
    }

