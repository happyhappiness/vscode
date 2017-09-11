            robj *selectcmd;

            if (dictid >= 0 && dictid < REDIS_SHARED_SELECT_CMDS) {
                selectcmd = shared.select[dictid];
                incrRefCount(selectcmd);
            } else {
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
