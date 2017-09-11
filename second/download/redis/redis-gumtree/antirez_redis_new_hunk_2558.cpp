    }
    addReply(c, shared.ok);
    signalModifiedKey(c->db,c->argv[1]);
    notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
    server.dirty++;
}

