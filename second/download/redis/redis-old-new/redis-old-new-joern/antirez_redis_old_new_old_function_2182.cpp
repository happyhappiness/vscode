void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire, int unit) {
    long long milliseconds = 0; /* initialized to avoid any harmness warning */

    if (expire) {
        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
            return;
        if (milliseconds <= 0) {
            addReplyError(c,"invalid expire time in SETEX");
            return;
        }
        if (unit == UNIT_SECONDS) milliseconds *= 1000;
    }

    if (nx && lookupKeyWrite(c->db,key) != NULL) {
        addReply(c,shared.czero);
        return;
    }
    setKey(c->db,key,val);
    server.dirty++;
    if (expire) setExpire(c->db,key,mstime()+milliseconds);
    notifyKeyspaceEvent("set",key,c->db->id);
    if (expire) notifyKeyspaceEvent("expire",key,c->db->id);
    addReply(c, nx ? shared.cone : shared.ok);
}