                if (!val || val->type != REDIS_STRING) {
                    addReply(c,shared.nullbulk);
                } else {
                    addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                        sdslen(val->ptr)));
                    addReply(c,val);
                    addReply(c,shared.crlf);
                }
