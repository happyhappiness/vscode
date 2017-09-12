    /* Send command output to the output buffer, performing the specified
     * GET/DEL/INCR/DECR operations if any. */
    outputlen = getop ? getop*(end-start+1) : end-start+1;
    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",outputlen));
    for (j = start; j <= end; j++) {
        listNode *ln = operations->head;
        if (!getop) {
            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",
                sdslen(vector[j].obj->ptr)));
            addReply(c,vector[j].obj);
            addReply(c,shared.crlf);
