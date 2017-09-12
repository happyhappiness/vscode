void execCommand(redisClient *c) {
    int j;
    robj **orig_argv;
    int orig_argc;

    if (!(c->flags & REDIS_MULTI)) {
        addReplySds(c,sdsnew("-ERR EXEC without MULTI\r\n"));
        return;
    }

    /* Check if we need to abort the EXEC if some WATCHed key was touched.
     * A failed EXEC will return a multi bulk nil object. */
    if (c->flags & REDIS_DIRTY_CAS) {
        freeClientMultiState(c);
        initClientMultiState(c);
        c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);
        unwatchAllKeys(c);
        addReply(c,shared.nullmultibulk);
        return;
    }

    /* Replicate a MULTI request now that we are sure the block is executed.
     * This way we'll deliver the MULTI/..../EXEC block as a whole and
     * both the AOF and the replication link will have the same consistency
     * and atomicity guarantees. */
    execCommandReplicateMulti(c);

    /* Exec all the queued commands */
    unwatchAllKeys(c); /* Unwatch ASAP otherwise we'll waste CPU cycles */
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
    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);
    /* Make sure the EXEC command is always replicated / AOF, since we
     * always send the MULTI command (we can't know beforehand if the
     * next operations will contain at least a modification to the DB). */
    server.dirty++;
}