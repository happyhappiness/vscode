void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
    listNode *ln;
    listIter li;
    int j;

    listRewind(slaves,&li);
    while((ln = listNext(&li))) {
        redisClient *slave = ln->value;

        /* Don't feed slaves that are still waiting for BGSAVE to start */
        if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;

        /* Feed slaves that are waiting for the initial SYNC (so these commands
         * are queued in the output buffer until the initial SYNC completes),
         * or are already in sync with the master. */
        if (server.slaveseldb != dictid) {
            robj *selectcmd;

            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
                selectcmd = shared.select[dictid];
                incrRefCount(selectcmd);
            } else {
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
            }
            addReply(slave,selectcmd);
            decrRefCount(selectcmd);
        }
        addReplyMultiBulkLen(slave,argc);
        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
    }
    server.slaveseldb = dictid;
}