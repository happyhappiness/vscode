        addReply(c,shared.syntaxerr);
        return;
    }
    sds info = genRedisInfoString(section);
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
        (unsigned long)sdslen(info)));
    addReplySds(c,info);
    addReply(c,shared.crlf);
}

void monitorCommand(redisClient *c) {
