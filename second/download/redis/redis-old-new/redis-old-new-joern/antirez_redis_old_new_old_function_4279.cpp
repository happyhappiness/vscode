static void infoCommand(redisClient *c) {
    sds info = genRedisInfoString();
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}