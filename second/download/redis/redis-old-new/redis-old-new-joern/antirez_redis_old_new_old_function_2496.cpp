void __redisSetError(redisContext *c, int type, const sds errstr) {
    c->err = type;
    if (errstr != NULL) {
        c->errstr = errstr;
    } else {
        /* Only REDIS_ERR_IO may lack a description! */
        assert(type == REDIS_ERR_IO);
        c->errstr = sdsnew(strerror(errno));
    }
}