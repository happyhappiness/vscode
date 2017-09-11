    }

    if (deleted) {
        notifyKeyspaceEvent("zrem",key,c->db->id);
        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
        signalModifiedKey(c->db,key);
        server.dirty += deleted;
    }
