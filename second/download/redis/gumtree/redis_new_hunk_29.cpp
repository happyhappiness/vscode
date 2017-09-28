            flags |= REDIS_SHUTDOWN_SAVE;
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }
    /* SHUTDOWN can be called even while the server is in "loading" state.
     * When this happens we need to make sure no attempt is performed to save
     * the dataset on shutdown (otherwise it could overwrite the current DB
     * with half-read data). */
    if (server.loading)
        flags = (flags & ~REDIS_SHUTDOWN_SAVE) | REDIS_SHUTDOWN_NOSAVE;
    if (prepareForShutdown(flags) == REDIS_OK) exit(0);
    addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
}

void renameGenericCommand(redisClient *c, int nx) {
    robj *o;
