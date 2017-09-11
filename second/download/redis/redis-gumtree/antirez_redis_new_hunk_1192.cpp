    }
}

void getCommand(client *c) {
    getGenericCommand(c);
}

void getsetCommand(client *c) {
    if (getGenericCommand(c) == REDIS_ERR) return;
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    setKey(c->db,c->argv[1],c->argv[2]);
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
    server.dirty++;
}

void setrangeCommand(client *c) {
    robj *o;
    long offset;
    sds value = c->argv[3]->ptr;
