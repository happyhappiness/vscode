    zfree(scores);
    if (added || updated) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(incr ? "zincr" : "zadd", key, c->db->id);
    }
}

