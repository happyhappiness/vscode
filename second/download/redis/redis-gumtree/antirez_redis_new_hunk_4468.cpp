            continue; /* at least one set does not contain the member */
        ele = dictGetEntryKey(de);
        if (!dstkey) {
            addReplyBulkLen(c,ele);
            addReply(c,ele);
            addReply(c,shared.crlf);
            cardinality++;
