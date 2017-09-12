
    /* Iterate all the elements of all the sets, add every element a single
     * time to the result set */
    for (j = 0; j < setnum; j++) {
        if (op == REDIS_OP_DIFF && j == 0 && !sets[j]) break; /* result set is empty */
        if (!sets[j]) continue; /* non existing keys are like empty sets */

        si = setTypeInitIterator(sets[j]);
        while((ele = setTypeNext(si)) != NULL) {
            if (op == REDIS_OP_UNION || j == 0) {
                if (setTypeAdd(dstset,ele)) {
                    cardinality++;
                }
            } else if (op == REDIS_OP_DIFF) {
                if (setTypeRemove(dstset,ele)) {
                    cardinality--;
                }
            }
            decrRefCount(ele);
        }
        setTypeReleaseIterator(si);

        /* Exit when result set is empty. */
        if (op == REDIS_OP_DIFF && cardinality == 0) break;
    }

    /* Output the content of the resulting set, if not in STORE mode */
    if (!dstkey) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
        si = setTypeInitIterator(dstset);
        while((ele = setTypeNext(si)) != NULL) {
            addReplyBulk(c,ele);
            decrRefCount(ele);
        }
        setTypeReleaseIterator(si);
        decrRefCount(dstset);
    } else {
        /* If we have a target key where to store the resulting set
         * create this key with the result set inside */
        dbDelete(c->db,dstkey);
        if (setTypeSize(dstset) > 0) {
            dbAdd(c->db,dstkey,dstset);
            addReplyLongLong(c,setTypeSize(dstset));
        } else {
            decrRefCount(dstset);
            addReply(c,shared.czero);
        }
        server.dirty++;
    }
    zfree(sets);
}

static void sunionCommand(redisClient *c) {
