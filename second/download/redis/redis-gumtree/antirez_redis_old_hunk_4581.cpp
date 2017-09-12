    );
    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(info)));
    addReplySds(c,info);
}

/* =============================== Replication  ============================= */
