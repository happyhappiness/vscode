    int withscores = 0;
    unsigned long rangelen = 0;
    void *replylen = NULL;

    /* Parse the range arguments. */
    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
        addReplyError(c,"min or max is not a double");
        return;
    }
