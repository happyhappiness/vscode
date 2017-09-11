
        /* We know for sure there is a whole line since newline != NULL,
         * so go ahead and find out the multi bulk length. */
        redisAssert(c->querybuf[0] == '*');
        ok = string2ll(c->querybuf+1,newline-(c->querybuf+1),&ll);
        if (!ok || ll > 1024*1024) {
            addReplyError(c,"Protocol error: invalid multibulk length");
