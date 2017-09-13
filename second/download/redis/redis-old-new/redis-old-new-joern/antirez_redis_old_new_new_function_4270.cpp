static void execCommand(redisClient *c) {
    int j;
    robj **orig_argv;
    int orig_argc;

    if (!(c->flags & REDIS_MULTI)) {
        addReplySds(c,sdsnew("-ERR EXEC without MULTI\r\n"));
        return;
    }

    orig_argv = c->argv;
    orig_argc = c->argc;
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->mstate.count));
    for (j = 0; j < c->mstate.count; j++) {
        c->argc = c->mstate.commands[j].argc;
        c->argv = c->mstate.commands[j].argv;
        call(c,c->mstate.commands[j].cmd);
    }
    c->argv = orig_argv;
    c->argc = orig_argc;
    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= (~REDIS_MULTI);
}