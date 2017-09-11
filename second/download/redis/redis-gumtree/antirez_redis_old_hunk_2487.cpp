        /* Feed slaves that are waiting for the initial SYNC (so these commands
         * are queued in the output buffer until the initial SYNC completes),
         * or are already in sync with the master. */
        if (server.slaveseldb != dictid) {
            robj *selectcmd;

            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
                selectcmd = shared.select[dictid];
                incrRefCount(selectcmd);
            } else {
                char dictid_str[64];
                int dictid_len;

                dictid_len = ll2string(dictid_str,sizeof(dictid_str),dictid);
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),
                        "*2\r\n$6\r\nSELECT\r\n$%d\r\n%s\r\n",
                        dictid_len, dictid_str));
            }
            addReply(slave,selectcmd);
            decrRefCount(selectcmd);
        }
        addReplyMultiBulkLen(slave,argc);
        for (j = 0; j < argc; j++) addReplyBulk(slave,argv[j]);
    }
    server.slaveseldb = dictid;
}

void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
