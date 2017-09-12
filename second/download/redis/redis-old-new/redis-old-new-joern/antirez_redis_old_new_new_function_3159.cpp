int dsDel(redisDb *db, robj *key) {
    char buf[1024];

    dsKeyToPath(db,buf,key);
    if (unlink(buf) == -1) {
        if (errno == ENOENT) {
            return REDIS_ERR;
        } else {
            redisLog(REDIS_WARNING,"Disk store can't remove %s: %s",
                buf, strerror(errno));
            redisPanic("Unrecoverable Disk store errore. Existing.");
            return REDIS_ERR; /* unreached */
        }
    } else {
        return REDIS_OK;
    }
}