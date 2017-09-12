    for (j = start; j <= end; j++) {
        listNode *ln;
        if (!getop) {
            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",
                sdslen(vector[j].obj->ptr)));
            addReply(c,vector[j].obj);
            addReply(c,shared.crlf);
        }
