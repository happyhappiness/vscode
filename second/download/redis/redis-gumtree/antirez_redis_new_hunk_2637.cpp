    return;
}

/* RESTORE key ttl serialized-value [REPLACE] */
void restoreCommand(redisClient *c) {
    long ttl;
    rio payload;
    int j, type, replace = 0;
    robj *obj;

    /* Parse additional options */
    for (j = 4; j < c->argc; j++) {
        if (!strcasecmp(c->argv[j]->ptr,"replace")) {
            replace = 1;
        } else {
            addReply(c,shared.syntaxerr);
            return;
        }
    }

    /* Make sure this key does not already exist here... */
    if (!replace && lookupKeyWrite(c->db,c->argv[1]) != NULL) {
        addReplyError(c,"Target key name is busy.");
        return;
    }
