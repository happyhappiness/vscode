    return totlen;
}

void __redisSetError(redisContext *c, int type, const char *str) {
    size_t len;

