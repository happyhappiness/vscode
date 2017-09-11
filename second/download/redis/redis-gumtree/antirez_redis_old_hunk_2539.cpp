    setKey(c->db,key,val);
    server.dirty++;
    if (expire) setExpire(c->db,key,mstime()+milliseconds);
    notifyKeyspaceEvent("set",key,c->db->id);
    if (expire) notifyKeyspaceEvent("expire",key,c->db->id);
    addReply(c, nx ? shared.cone : shared.ok);
}

