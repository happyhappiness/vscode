                selectcmd = shared.select[dictid];
                incrRefCount(selectcmd);
            } else {
                selectcmd = createObject(REDIS_STRING,
                    sdscatprintf(sdsempty(),"select %d\r\n",dictid));
            }
            addReply(slave,selectcmd);
            decrRefCount(selectcmd);
