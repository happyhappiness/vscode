    for (j = start; j <= end; j++) {
        listNode *ln;
        if (!getop) {
            addReplyBulkLen(c,vector[j].obj);
            addReply(c,vector[j].obj);
            addReply(c,shared.crlf);
        }
