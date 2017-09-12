void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    long long lltimeout;
    time_t timeout;
    int j;

    /* Make sure timeout is an integer value */
    if (getLongLongFromObjectOrReply(c,c->argv[c->argc-1],&lltimeout,
            "timeout is not an integer") != REDIS_OK) return;

    /* Make sure the timeout is not negative */
    if (lltimeout < 0) {
        addReplyError(c,"timeout is negative");
        return;
    }

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
        if (o != NULL) {
            if (o->type != REDIS_LIST) {
                addReply(c,shared.wrongtypeerr);
                return;
            } else {
                if (listTypeLength(o) != 0) {
                    /* If the list contains elements fall back to the usual
                     * non-blocking POP operation */
                    robj *argv[2], **orig_argv;
                    int orig_argc;

                    if (c->bstate.target == NULL) {
                      /* We need to alter the command arguments before to call
                       * popGenericCommand() as the command takes a single key. */
                      orig_argv = c->argv;
                      orig_argc = c->argc;
                      argv[1] = c->argv[j];
                      c->argv = argv;
                      c->argc = 2;

                      /* Also the return value is different, we need to output
                       * the multi bulk reply header and the key name. The
                       * "real" command will add the last element (the value)
                       * for us. If this souds like an hack to you it's just
                       * because it is... */
                      addReplyMultiBulkLen(c,2);
                      addReplyBulk(c,argv[1]);

                      popGenericCommand(c,where);

                      /* Fix the client structure with the original stuff */
                      c->argv = orig_argv;
                      c->argc = orig_argc;
                    }
                    else {
                      c->argv[2] = c->bstate.target;
                      c->bstate.target = NULL;

                      rpoplpushCommand(c);
                    }

                    return;
                }
            }
        }
    }

    /* If we are inside a MULTI/EXEC and the list is empty the only thing
     * we can do is treating it as a timeout (even with timeout 0). */
    if (c->flags & REDIS_MULTI) {
        addReply(c,shared.nullmultibulk);
        return;
    }

    /* If the list is empty or the key does not exists we must block */
    timeout = lltimeout;
    if (timeout > 0) timeout += time(NULL);
    blockForKeys(c,c->argv+1,c->argc-2,timeout);
}