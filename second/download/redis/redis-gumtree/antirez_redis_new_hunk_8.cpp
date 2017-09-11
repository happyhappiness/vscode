    bc->dbid = c->db->id;
    c->bpop.timeout = timeout_ms ? (mstime()+timeout_ms) : 0;

    if (islua) {
        c->bpop.module_blocked_handle = NULL;
        addReplyError(c,"Blocking module command called from Lua script");
    } else {
        blockClient(c,BLOCKED_MODULE);
    }
    return bc;
}

