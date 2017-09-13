static void echoCommand(redisClient *c) {
    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
        (int)sdslen(c->argv[1]->ptr)));
    addReply(c,c->argv[1]);
    addReply(c,shared.crlf);
}