    void *replylen = NULL;

    /* Parse the range arguments. */
    zslParseRange(c->argv[2],c->argv[3],&range);

    /* Parse optional extra arguments. Note that ZCOUNT will exactly have
     * 4 arguments, so we'll never enter the following code path. */
