    }

cleanup:
    zfree(scores);
    if (added || updated) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(NOTIFY_ZSET,
            incr ? "zincr" : "zadd", key, c->db->id);
    }
}

void zaddCommand(client *c) {
    zaddGenericCommand(c,ZADD_NONE);
}

void zincrbyCommand(client *c) {
    zaddGenericCommand(c,ZADD_INCR);
}

void zremCommand(client *c) {
    robj *key = c->argv[1];
    robj *zobj;
    int deleted = 0, keyremoved = 0, j;

    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
        checkType(c,zobj,OBJ_ZSET)) return;

    if (zobj->encoding == OBJ_ENCODING_ZIPLIST) {
        unsigned char *eptr;

        for (j = 2; j < c->argc; j++) {
            if ((eptr = zzlFind(zobj->ptr,c->argv[j],NULL)) != NULL) {
                deleted++;
                zobj->ptr = zzlDelete(zobj->ptr,eptr);
