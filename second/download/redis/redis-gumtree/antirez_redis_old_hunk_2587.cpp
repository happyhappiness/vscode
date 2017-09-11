    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        /* Correct for 1-based rank. */
        zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
        if (zzlLength(zobj->ptr) == 0) dbDelete(c->db,key);
    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;

        /* Correct for 1-based rank. */
        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        if (dictSize(zs->dict) == 0) dbDelete(c->db,key);
    } else {
        redisPanic("Unknown sorted set encoding");
    }

    if (deleted) signalModifiedKey(c->db,key);
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}
