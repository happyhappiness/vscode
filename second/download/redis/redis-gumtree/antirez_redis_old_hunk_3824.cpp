
    /* Output the content of the resulting set, if not in STORE mode */
    if (!dstkey) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
        si = setTypeInitIterator(dstset);
        while((ele = setTypeNext(si)) != NULL) {
            addReplyBulk(c,ele);
