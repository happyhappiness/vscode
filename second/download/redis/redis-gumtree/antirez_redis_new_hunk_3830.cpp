    /* expect setnum input keys to be given */
    setnum = atoi(c->argv[2]->ptr);
    if (setnum < 1) {
        addReplyError(c,
            "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
        return;
    }

