    if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
        badsyntax = 1;
    if (badsyntax) {
        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
        return;
    }

