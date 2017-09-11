        hashTypeSet(o,c->argv[2],c->argv[3]);
        addReply(c, shared.cone);
        signalModifiedKey(c->db,c->argv[1]);
        notifyKeyspaceEvent("hset",c->argv[1],c->db->id);
        server.dirty++;
    }
}
