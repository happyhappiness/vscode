
    /* Parse the bit argument to understand what we are looking for, set
     * or clear bits. */
    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != REDIS_OK)
        return;
    if (bit != 0 && bit != 1) {
        addReplyError(c, "The bit argument must be 1 or 0.");
