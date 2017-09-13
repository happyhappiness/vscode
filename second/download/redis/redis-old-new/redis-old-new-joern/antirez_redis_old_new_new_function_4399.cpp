static void getCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);

    if (o == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
        } else {
            addReplyBulkLen(c,o);
            addReply(c,o);
            addReply(c,shared.crlf);
        }
    }
}