    return diff; /* If zero strings are the same. */
}

void authCommand(redisClient *c) {
    if (!server.requirepass) {
        addReplyError(c,"Client sent AUTH, but no password is set");
    } else if (!time_independent_strcmp(c->argv[1]->ptr, server.requirepass)) {
