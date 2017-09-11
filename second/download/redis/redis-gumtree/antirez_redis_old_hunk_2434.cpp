    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
    if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
        "expire",key,c->db->id);
    addReply(c, nx ? shared.cone : shared.ok);
}

void setCommand(redisClient *c) {
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    setGenericCommand(c,0,c->argv[1],c->argv[2],NULL,0);
}

void setnxCommand(redisClient *c) {
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    setGenericCommand(c,1,c->argv[1],c->argv[2],NULL,0);
}

void setexCommand(redisClient *c) {
    c->argv[3] = tryObjectEncoding(c->argv[3]);
    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS);
}

void psetexCommand(redisClient *c) {
    c->argv[3] = tryObjectEncoding(c->argv[3]);
    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS);
}

int getGenericCommand(redisClient *c) {
