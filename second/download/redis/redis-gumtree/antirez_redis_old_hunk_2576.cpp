    decrRefCount(aux);

    addReplyBulk(c,ele);
    if (setTypeSize(set) == 0) dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
}
