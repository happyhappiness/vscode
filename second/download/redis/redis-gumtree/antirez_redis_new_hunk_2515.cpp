    update = hashTypeSet(o,c->argv[2],c->argv[3]);
    addReply(c, update ? shared.czero : shared.cone);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent(REDIS_NOTIFY_HASH,"hset",c->argv[1],c->db->id);
    server.dirty++;
}

