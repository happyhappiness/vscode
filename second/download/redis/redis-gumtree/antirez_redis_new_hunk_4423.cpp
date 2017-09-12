    /* Send command output to the output buffer, performing the specified
     * GET/DEL/INCR/DECR operations if any. */
    outputlen = getop ? getop*(end-start+1) : end-start+1;
    if (storekey == NULL) {
        /* STORE option not specified, sent the sorting result to client */
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

                if (sop->type == REDIS_SORT_GET) {
                    if (!val || val->type != REDIS_STRING) {
                        addReply(c,shared.nullbulk);
                    } else {
                        addReplyBulkLen(c,val);
                        addReply(c,val);
                        addReply(c,shared.crlf);
                    }
                } else {
                    assert(sop->type == REDIS_SORT_GET); /* always fails */
                }
            }
        }
    } else {
        robj *listObject = createListObject();
        list *listPtr = (list*) listObject->ptr;

        /* STORE option specified, set the sorting result as a List object */
        for (j = start; j <= end; j++) {
            listNode *ln;
            if (!getop) {
                listAddNodeTail(listPtr,vector[j].obj);
                incrRefCount(vector[j].obj);
            }
            listRewind(operations);
            while((ln = listYield(operations))) {
                redisSortOperation *sop = ln->value;
                robj *val = lookupKeyByPattern(c->db,sop->pattern,
                    vector[j].obj);

                if (sop->type == REDIS_SORT_GET) {
                    if (!val || val->type != REDIS_STRING) {
                        listAddNodeTail(listPtr,createStringObject("",0));
                    } else {
                        listAddNodeTail(listPtr,val);
                        incrRefCount(val);
                    }
                } else {
                    assert(sop->type == REDIS_SORT_GET); /* always fails */
                }
            }
        }
        dictReplace(c->db->dict,storekey,listObject);
        /* Note: we add 1 because the DB is dirty anyway since even if the
         * SORT result is empty a new key is set and maybe the old content
         * replaced. */
        server.dirty += 1+outputlen;
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
    }

    /* Cleanup */
