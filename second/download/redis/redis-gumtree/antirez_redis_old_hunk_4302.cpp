        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
        for (j = start; j <= end; j++) {
            listNode *ln;
            if (!getop) {
                addReplyBulkLen(c,vector[j].obj);
                addReply(c,vector[j].obj);
                addReply(c,shared.crlf);
            }
            listRewind(operations);
            while((ln = listYield(operations))) {
                redisSortOperation *sop = ln->value;
                robj *val = lookupKeyByPattern(c->db,sop->pattern,
                    vector[j].obj);
