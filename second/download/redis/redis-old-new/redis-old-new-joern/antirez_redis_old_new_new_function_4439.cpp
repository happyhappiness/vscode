static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey, int op) {
    dict **dv = zmalloc(sizeof(dict*)*setsnum);
    dictIterator *di;
    dictEntry *de;
    robj *dstset = NULL;
    int j, cardinality = 0;

    if (!dv) oom("sunionDiffGenericCommand");
    for (j = 0; j < setsnum; j++) {
        robj *setobj;

        setobj = dstkey ?
                    lookupKeyWrite(c->db,setskeys[j]) :
                    lookupKeyRead(c->db,setskeys[j]);
        if (!setobj) {
            dv[j] = NULL;
            continue;
        }
        if (setobj->type != REDIS_SET) {
            zfree(dv);
            addReply(c,shared.wrongtypeerr);
            return;
        }
        dv[j] = setobj->ptr;
    }

    /* We need a temp set object to store our union. If the dstkey
     * is not NULL (that is, we are inside an SUNIONSTORE operation) then
     * this set object will be the resulting object to set into the target key*/
    dstset = createSetObject();

    /* The first thing we should output is the total number of elements...
     * since this is a multi-bulk write, but at this stage we don't know
     * the intersection set size, so we use a trick, append an empty object
     * to the output list and save the pointer to later modify it with the
     * right length */
    if (dstkey) {
        /* If we have a target key where to store the resulting set
         * create this key with an empty set inside */
        deleteKey(c->db,dstkey);
        dictAdd(c->db->dict,dstkey,dstset);
        incrRefCount(dstkey);
        server.dirty++;
    }

    /* Iterate all the elements of all the sets, add every element a single
     * time to the result set */
    for (j = 0; j < setsnum; j++) {
        if (!dv[j]) continue; /* non existing keys are like empty sets */

        di = dictGetIterator(dv[j]);
        if (!di) oom("dictGetIterator");

        while((de = dictNext(di)) != NULL) {
            robj *ele;

            /* dictAdd will not add the same element multiple times */
            ele = dictGetEntryKey(de);
            if (op == REDIS_OP_UNION || j == 0) {
                if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
                    incrRefCount(ele);
                    cardinality++;
                }
            } else if (op == REDIS_OP_DIFF) {
                if (dictDelete(dstset->ptr,ele) == DICT_OK) {
                    cardinality--;
                }
            }
        }
        dictReleaseIterator(di);
    }

    /* Output the content of the resulting set, if not in STORE mode */
    if (!dstkey) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
        di = dictGetIterator(dstset->ptr);
        if (!di) oom("dictGetIterator");
        while((de = dictNext(di)) != NULL) {
            robj *ele;

            ele = dictGetEntryKey(de);
            addReplySds(c,sdscatprintf(sdsempty(),
                    "$%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
        }
        dictReleaseIterator(di);
    }

    /* Cleanup */
    if (!dstkey) {
        decrRefCount(dstset);
    } else {
        addReply(c,shared.ok);
        server.dirty++;
    }
    zfree(dv);
}