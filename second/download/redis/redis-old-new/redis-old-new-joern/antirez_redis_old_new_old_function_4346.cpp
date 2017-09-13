static void sortCommand(redisClient *c) {
    list *operations;
    int outputlen = 0;
    int desc = 0, alpha = 0;
    int limit_start = 0, limit_count = -1, start, end;
    int j, dontsort = 0, vectorlen;
    int getop = 0; /* GET operation counter */
    robj *sortval, *sortby = NULL;
    redisSortObject *vector; /* Resulting vector to sort */

    /* Lookup the key to sort. It must be of the right types */
    sortval = lookupKeyRead(c->db,c->argv[1]);
    if (sortval == NULL) {
        addReply(c,shared.nokeyerr);
        return;
    }
    if (sortval->type != REDIS_SET && sortval->type != REDIS_LIST) {
        addReply(c,shared.wrongtypeerr);
        return;
    }

    /* Create a list of operations to perform for every sorted element.
     * Operations can be GET/DEL/INCR/DECR */
    operations = listCreate();
    listSetFreeMethod(operations,zfree);
    j = 2;

    /* Now we need to protect sortval incrementing its count, in the future
     * SORT may have options able to overwrite/delete keys during the sorting
     * and the sorted key itself may get destroied */
    incrRefCount(sortval);

    /* The SORT command has an SQL-alike syntax, parse it */
    while(j < c->argc) {
        int leftargs = c->argc-j-1;
        if (!strcasecmp(c->argv[j]->ptr,"asc")) {
            desc = 0;
        } else if (!strcasecmp(c->argv[j]->ptr,"desc")) {
            desc = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"alpha")) {
            alpha = 1;
        } else if (!strcasecmp(c->argv[j]->ptr,"limit") && leftargs >= 2) {
            limit_start = atoi(c->argv[j+1]->ptr);
            limit_count = atoi(c->argv[j+2]->ptr);
            j+=2;
        } else if (!strcasecmp(c->argv[j]->ptr,"by") && leftargs >= 1) {
            sortby = c->argv[j+1];
            /* If the BY pattern does not contain '*', i.e. it is constant,
             * we don't need to sort nor to lookup the weight keys. */
            if (strchr(c->argv[j+1]->ptr,'*') == NULL) dontsort = 1;
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
            listAddNodeTail(operations,createSortOperation(
                REDIS_SORT_GET,c->argv[j+1]));
            getop++;
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"del") && leftargs >= 1) {
            listAddNodeTail(operations,createSortOperation(
                REDIS_SORT_DEL,c->argv[j+1]));
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"incr") && leftargs >= 1) {
            listAddNodeTail(operations,createSortOperation(
                REDIS_SORT_INCR,c->argv[j+1]));
            j++;
        } else if (!strcasecmp(c->argv[j]->ptr,"get") && leftargs >= 1) {
            listAddNodeTail(operations,createSortOperation(
                REDIS_SORT_DECR,c->argv[j+1]));
            j++;
        } else {
            decrRefCount(sortval);
            listRelease(operations);
            addReply(c,shared.syntaxerr);
            return;
        }
        j++;
    }

    /* Load the sorting vector with all the objects to sort */
    vectorlen = (sortval->type == REDIS_LIST) ?
        listLength((list*)sortval->ptr) :
        dictSize((dict*)sortval->ptr);
    vector = zmalloc(sizeof(redisSortObject)*vectorlen);
    j = 0;
    if (sortval->type == REDIS_LIST) {
        list *list = sortval->ptr;
        listNode *ln;

        listRewind(list);
        while((ln = listYield(list))) {
            robj *ele = ln->value;
            vector[j].obj = ele;
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
        }
    } else {
        dict *set = sortval->ptr;
        dictIterator *di;
        dictEntry *setele;

        di = dictGetIterator(set);
        while((setele = dictNext(di)) != NULL) {
            vector[j].obj = dictGetEntryKey(setele);
            vector[j].u.score = 0;
            vector[j].u.cmpobj = NULL;
            j++;
        }
        dictReleaseIterator(di);
    }
    assert(j == vectorlen);

    /* Now it's time to load the right scores in the sorting vector */
    if (dontsort == 0) {
        for (j = 0; j < vectorlen; j++) {
            if (sortby) {
                robj *byval;

                byval = lookupKeyByPattern(c->db,sortby,vector[j].obj);
                if (!byval || byval->type != REDIS_STRING) continue;
                if (alpha) {
                    if (byval->encoding == REDIS_ENCODING_RAW) {
                        vector[j].u.cmpobj = byval;
                        incrRefCount(byval);
                    } else {
                        vector[j].u.cmpobj = getDecodedObject(byval);
                    }
                } else {
                    if (byval->encoding == REDIS_ENCODING_RAW) {
                        vector[j].u.score = strtod(byval->ptr,NULL);
                    } else {
                        if (byval->encoding == REDIS_ENCODING_INT) {
                            vector[j].u.score = (long)byval->ptr;
                        } else
                            assert(1 != 1);
                    }
                }
            } else {
                if (!alpha) {
                    if (vector[j].obj->encoding == REDIS_ENCODING_RAW)
                        vector[j].u.score = strtod(vector[j].obj->ptr,NULL);
                    else {
                        if (vector[j].obj->encoding == REDIS_ENCODING_INT)
                            vector[j].u.score = (long) vector[j].obj->ptr;
                        else
                            assert(1 != 1);
                    }
                }
            }
        }
    }

    /* We are ready to sort the vector... perform a bit of sanity check
     * on the LIMIT option too. We'll use a partial version of quicksort. */
    start = (limit_start < 0) ? 0 : limit_start;
    end = (limit_count < 0) ? vectorlen-1 : start+limit_count-1;
    if (start >= vectorlen) {
        start = vectorlen-1;
        end = vectorlen-2;
    }
    if (end >= vectorlen) end = vectorlen-1;

    if (dontsort == 0) {
        server.sort_desc = desc;
        server.sort_alpha = alpha;
        server.sort_bypattern = sortby ? 1 : 0;
        if (sortby && (start != 0 || end != vectorlen-1))
            pqsort(vector,vectorlen,sizeof(redisSortObject),sortCompare, start,end);
        else
            qsort(vector,vectorlen,sizeof(redisSortObject),sortCompare);
    }

    /* Send command output to the output buffer, performing the specified
     * GET/DEL/INCR/DECR operations if any. */
    outputlen = getop ? getop*(end-start+1) : end-start+1;
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",outputlen));
    for (j = start; j <= end; j++) {
        listNode *ln;
        if (!getop) {
            addReplyBulkLen(c,vector[j].obj);
            addReply(c,vector[j].obj);
            addReply(c,shared.crlf);
        }
        listRewind(operations);
        while((ln = listYield(operations))) {
            redisSortOperation *sop = ln->value;
            robj *val = lookupKeyByPattern(c->db,sop->pattern,
                vector[j].obj);

            if (sop->type == REDIS_SORT_GET) {
                if (!val || val->type != REDIS_STRING) {
                    addReply(c,shared.nullbulk);
                } else {
                    addReplyBulkLen(c,val);
                    addReply(c,val);
                    addReply(c,shared.crlf);
                }
            } else if (sop->type == REDIS_SORT_DEL) {
                /* TODO */
            }
        }
    }

    /* Cleanup */
    decrRefCount(sortval);
    listRelease(operations);
    for (j = 0; j < vectorlen; j++) {
        if (sortby && alpha && vector[j].u.cmpobj)
            decrRefCount(vector[j].u.cmpobj);
    }
    zfree(vector);
}