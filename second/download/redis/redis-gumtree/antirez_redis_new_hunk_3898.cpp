    }

    /* Return the result in form of a multi-bulk reply */
    addReplyMultiBulkLen(c,withscores ? (rangelen*2) : rangelen);
    for (j = 0; j < rangelen; j++) {
        ele = ln->obj;
        addReplyBulk(c,ele);
