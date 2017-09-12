            continue; /* at least one set does not contain the member */
        ele = dictGetEntryKey(de);
        if (!dstkey) {
            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
            cardinality++;
