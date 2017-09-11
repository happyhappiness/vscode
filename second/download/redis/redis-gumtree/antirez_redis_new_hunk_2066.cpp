    /* If this is a string representing an HLL, the size should match
     * exactly. */
    if (stringObjectLen(o) != REDIS_HLL_SIZE) {
        addReplySds(c,
            sdsnew("-WRONGTYPE Key is not a valid "
                   "HyperLogLog string value.\r\n"));
        return REDIS_ERR;
    }
    return REDIS_OK;
