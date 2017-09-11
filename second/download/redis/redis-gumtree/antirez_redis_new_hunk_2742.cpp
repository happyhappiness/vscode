        if (slave->slaveseldb != dictid) {
            robj *selectcmd;

            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
                incrRefCount(shared.select[dictid]);
                selectcmd = shared.select[dictid];
            } else {
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
            }
            addReply(slave,selectcmd);
            decrRefCount(selectcmd);
            slave->slaveseldb = dictid;
        }
        addReplyMultiBulkLen(slave,argc);
