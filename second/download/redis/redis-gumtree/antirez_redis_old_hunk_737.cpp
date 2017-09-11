    sigset_t sigset;

    /* Check that the type is within the right interval. */
    if (type >= REDIS_BIO_NUM_OPS) {
        serverLog(LL_WARNING,
            "Warning: bio thread started with wrong type %lu",type);
        return NULL;
