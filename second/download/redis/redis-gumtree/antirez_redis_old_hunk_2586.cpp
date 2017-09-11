
    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        zobj->ptr = zzlDeleteRangeByScore(zobj->ptr,range,&deleted);
        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;
        deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
    } else {
        redisPanic("Unknown sorted set encoding");
    }

    if (deleted) signalModifiedKey(c->db,key);
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}
