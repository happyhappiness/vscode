
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        type = "+none";
    } else {
        switch(o->type) {
        case REDIS_STRING: type = "+string"; break;
        case REDIS_LIST: type = "+list"; break;
        case REDIS_SET: type = "+set"; break;
        case REDIS_ZSET: type = "+zset"; break;
        case REDIS_HASH: type = "+hash"; break;
        default: type = "+unknown"; break;
        }
    }
    addReplySds(c,sdsnew(type));
    addReply(c,shared.crlf);
}

void saveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1) {
        addReplySds(c,sdsnew("-ERR background save in progress\r\n"));
        return;
    }
    if (rdbSave(server.dbfilename) == REDIS_OK) {
