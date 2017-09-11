        c->argv[j] = tryObjectEncoding(c->argv[j]);
        if (setTypeAdd(set,c->argv[j])) added++;
    }
    if (added) signalModifiedKey(c->db,c->argv[1]);
    server.dirty += added;
    addReplyLongLong(c,added);
}

void sremCommand(redisClient *c) {
    robj *set;
    int j, deleted = 0;

    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,set,REDIS_SET)) return;
