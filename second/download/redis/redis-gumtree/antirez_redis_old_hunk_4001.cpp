    rangelen = (end-start)+1;

    /* Return the result in form of a multi-bulk reply */
    ln = listIndex(list, start);
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
    for (j = 0; j < rangelen; j++) {
        ele = listNodeValue(ln);
        addReplyBulk(c,ele);
        ln = ln->next;
    }
}

static void ltrimCommand(redisClient *c) {
