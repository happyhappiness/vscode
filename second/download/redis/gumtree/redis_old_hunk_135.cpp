    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
        (unsigned long)sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}

/* SENTINEL SET <mastername> [<option> <value> ...] */
void sentinelSetCommand(redisClient *c) {
    sentinelRedisInstance *ri;
    int j, changes = 0;
    char *option, *value;

