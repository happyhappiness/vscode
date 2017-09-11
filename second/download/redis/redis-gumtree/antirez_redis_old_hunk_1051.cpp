    setKey(c->db,key,val);
    server.dirty++;
    if (expire) setExpire(c->db,key,mstime()+milliseconds);
    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
    if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
        "expire",key,c->db->id);
    addReply(c, ok_reply ? ok_reply : shared.ok);
}
