void zremCommand(redisClient *c) {
    robj *key = c->argv[1];
    robj *zobj;
    int deleted = 0, j;

    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
        checkType(c,zobj,REDIS_ZSET)) return;

    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        unsigned char *eptr;

        for (j = 2; j < c->argc; j++) {
            if ((eptr = zzlFind(zobj->ptr,c->argv[j],NULL)) != NULL) {
                deleted++;
                zobj->ptr = zzlDelete(zobj->ptr,eptr);
                if (zzlLength(zobj->ptr) == 0) {
                    dbDelete(c->db,key);
                    break;
                }
            }
        }
    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;
        dictEntry *de;
        double score;

        for (j = 2; j < c->argc; j++) {
            de = dictFind(zs->dict,c->argv[j]);
            if (de != NULL) {
                deleted++;

                /* Delete from the skiplist */
                score = *(double*)dictGetVal(de);
                redisAssertWithInfo(c,c->argv[j],zslDelete(zs->zsl,score,c->argv[j]));

                /* Delete from the hash table */
                dictDelete(zs->dict,c->argv[j]);
                if (htNeedsResize(zs->dict)) dictResize(zs->dict);
                if (dictSize(zs->dict) == 0) {
                    dbDelete(c->db,key);
                    break;
                }
            }
        }
    } else {
        redisPanic("Unknown sorted set encoding");
    }

    if (deleted) {
        signalModifiedKey(c->db,key);
        server.dirty += deleted;
    }
    addReplyLongLong(c,deleted);
}