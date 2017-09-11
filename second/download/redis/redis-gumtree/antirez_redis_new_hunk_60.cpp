    return totlen;
}

void redisFreeCommand(char *cmd) {
    free(cmd);
}

void __redisSetError(redisContext *c, int type, const char *str) {
    size_t len;

