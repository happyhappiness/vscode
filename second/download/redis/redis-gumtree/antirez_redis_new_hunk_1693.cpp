        addReply(c,shared.syntaxerr);
        return;
    }
    addReplyBulkSds(c, genRedisInfoString(section));
}

void monitorCommand(redisClient *c) {
