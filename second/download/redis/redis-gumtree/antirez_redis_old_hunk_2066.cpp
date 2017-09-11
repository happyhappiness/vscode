    /* If this is a string representing an HLL, the size should match
     * exactly. */
    if (stringObjectLen(o) != REDIS_HLL_SIZE) {
        addReplyErrorFormat(c, "Key is not a valid HyperLogLog string value.");
        return REDIS_ERR;
    }
    return REDIS_OK;
