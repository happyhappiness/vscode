
            if (sop->type == REDIS_SORT_GET) {
                if (!val || val->type != REDIS_STRING) {
                    addReply(c,shared.nullbulk);
                } else {
                    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                        sdslen(val->ptr)));
