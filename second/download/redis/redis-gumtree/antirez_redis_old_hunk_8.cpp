    bc->dbid = c->db->id;
    c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;

    blockClient(c,BLOCKED_MODULE);
    return bc;
}

