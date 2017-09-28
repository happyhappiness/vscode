
        addReplyLongLong(c,redisPopcount(p+start,bytes));
    }
}

/* BITPOS key bit [start [end]] */
void bitposCommand(redisClient *c) {
    robj *o;
    long bit, start, end, strlen;
    unsigned char *p;
    char llbuf[32];
    int end_given = 0;

    /* Parse the bit argument to understand what we are looking for, set
     * or clear bits. */
    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != REDIS_OK)
        return;
    if (bit != 0 && bit != 1) {
        addReplyError(c, "The bit argument must be 1 or 0.");
        return;
    }

