    setKey(c->db,key,val);
    server.dirty++;
    if (expire) setExpire(c->db,key,mstime()+milliseconds);
    addReply(c, nx ? shared.cone : shared.ok);
}

