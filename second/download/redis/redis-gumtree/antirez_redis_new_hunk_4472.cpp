                if (!val || val->type != REDIS_STRING) {
                    addReply(c,shared.nullbulk);
                } else {
                    addReplyBulkLen(c,val);
                    addReply(c,val);
                    addReply(c,shared.crlf);
                }
