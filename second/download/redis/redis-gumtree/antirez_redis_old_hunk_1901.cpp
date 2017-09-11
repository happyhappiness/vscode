void pingCommand(redisClient *c) {
    /* The command takes zero or one arguments. */
    if (c->argc > 2) {
        addReply(c,shared.syntaxerr);
        return;
    }

