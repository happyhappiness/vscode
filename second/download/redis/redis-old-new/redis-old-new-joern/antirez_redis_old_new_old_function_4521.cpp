static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
    dict **dv = zmalloc(sizeof(dict*)*setsnum);
    dictIterator *di;
    dictEntry *de;
    robj *lenobj = NULL, *dstset = NULL;
    int j, cardinality = 0;

    if (!dv) oom("sinterCommand");
    for (j = 0; j < setsnum; j++) {
        robj *setobj;
        dictEntry *de;
        
        de = dictFind(c->dict,setskeys[j]);
        if (!de) {
            zfree(dv);
            addReply(c,dstkey ? shared.nokeyerr : shared.nil);
            return;
        }
        setobj = dictGetEntryVal(de);
        if (setobj->type != REDIS_SET) {
            zfree(dv);
            addReply(c,dstkey ? shared.wrongtypeerr : shared.wrongtypeerrbulk);
            return;
        }
        dv[j] = setobj->ptr;
    }
    /* Sort sets from the smallest to largest, this will improve our
     * algorithm's performace */
    qsort(dv,setsnum,sizeof(dict*),qsortCompareSetsByCardinality);

    /* The first thing we should output is the total number of elements...
     * since this is a multi-bulk write, but at this stage we don't know
     * the intersection set size, so we use a trick, append an empty object
     * to the output list and save the pointer to later modify it with the
     * right length */
    if (!dstkey) {
        lenobj = createObject(REDIS_STRING,NULL);
        addReply(c,lenobj);
        decrRefCount(lenobj);
    } else {
        /* If we have a target key where to store the resulting set
         * create this key with an empty set inside */
        dstset = createSetObject();
        dictDelete(c->dict,dstkey);
        dictAdd(c->dict,dstkey,dstset);
        incrRefCount(dstkey);
    }

    /* Iterate all the elements of the first (smallest) set, and test
     * the element against all the other sets, if at least one set does
     * not include the element it is discarded */
    di = dictGetIterator(dv[0]);
    if (!di) oom("dictGetIterator");

    while((de = dictNext(di)) != NULL) {
        robj *ele;

        for (j = 1; j < setsnum; j++)
            if (dictFind(dv[j],dictGetEntryKey(de)) == NULL) break;
        if (j != setsnum)
            continue; /* at least one set does not contain the member */
        ele = dictGetEntryKey(de);
        if (!dstkey) {
            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
            cardinality++;
        } else {
            dictAdd(dstset->ptr,ele,NULL);
            incrRefCount(ele);
        }
    }
    dictReleaseIterator(di);

    if (!dstkey)
        lenobj->ptr = sdscatprintf(sdsempty(),"%d\r\n",cardinality);
    else
        addReply(c,shared.ok);
    zfree(dv);
}