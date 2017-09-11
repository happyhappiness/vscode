    addReplyLongLong(c,setTypeSize(o));
}

/* handle the "SPOP key <count>" variant. The normal version of the
 * command is handled by the spopCommand() function itself. */

void spopWithCountCommand(redisClient *c) {
    long l;
    unsigned long count, size;
    int elements_returned;
    robj *set, *aux, *aux_set;
    int64_t llele;

    /* Get the count argument */
    if (getLongFromObjectOrReply(c,c->argv[2],&l,NULL) != REDIS_OK) return;
    if (l >= 0) {
        count = (unsigned) l;
    } else {
        addReply(c,shared.outofrangeerr);
        return;
    }

    /* Make sure a key with the name inputted exists, and that it's type is 
       indeed a set. Otherwise, return nil */
    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk))
        == NULL || checkType(c,set,REDIS_SET)) return;

    /* If count is zero, serve an empty multibulk ASAP to avoid special 
       cases later. */
    if (count == 0) {
        addReply(c,shared.emptymultibulk);
        return;
    }

    /* Get the size of the set. It is always > 0, as empty sets get
       deleted.  */
    size = setTypeSize(set);

    /* Generate an SPOP keyspace notification */
    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);

    /* CASE 1:
     * The number of requested elements is greater than or equal to 
     * the number of elements inside the set: simply return the whole set. */
    if (count >= size) {

        /* We just return the entire set */ 
        sunionDiffGenericCommand(c,c->argv+1,1,NULL,REDIS_OP_UNION);

        /* Delete the set as it is now empty */
        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);

        /* Replicate/AOF this command as an SREM operation */
        aux = createStringObject("DEL",3);
        rewriteClientCommandVector(c,2,aux,c->argv[1]);
        decrRefCount(aux);

        return;
    }

    /* CASE 2:
     * The number of requested elements is less than the number
     * of elements inside the set. */

    /* We need an auxiliary set. Optimistically, we create a set using an 
       Intset internally. */
    aux = createStringObjectFromLongLong(0);
    aux_set = setTypeCreate(aux);
    decrRefCount(aux);

    /* Get the count requested of random elements from the set into our 
       auxiliary set. */
    elements_returned = setTypeRandomElements(set, count, aux_set);
    redisAssert(elements_returned == count);

    {
        setTypeIterator *si;
        robj *objele;
        int element_encoding;

        addReplyMultiBulkLen(c, elements_returned);

        /* Replicate/AOF this command as an SREM operation */
        aux = createStringObject("SREM",4);

        si = setTypeInitIterator(aux_set);
        while ((element_encoding = setTypeNext(si, &objele, &llele)) != -1) {
            if (element_encoding == REDIS_ENCODING_HT) {

                addReplyBulk(c, objele);

                /* Replicate/AOF this command as an SREM commands */
                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
                setTypeRemove(set, objele);
            }
            else if (element_encoding == REDIS_ENCODING_INTSET) {
                /* TODO: setTypeRemove() forces us to convert all of the ints 
                         to string... isn't there a nicer way to do this? */
                objele = createStringObjectFromLongLong(llele);
                addReplyBulk(c, objele);

                /* Replicate/AOF this command as an SREM commands */
                rewriteClientCommandVector(c, 3, aux, c->argv[1], objele);
                setTypeRemove(set, objele);

                /* We created it, we kill it. */
                decrRefCount(objele);
            }
            else {
                redisPanic("Unknown set encoding");
            }
        }
        setTypeReleaseIterator(si);

        decrRefCount(aux);
    }

    /* Free the auxiliary set - we need it no more. */
    freeSetObject(aux_set);
}

void spopCommand(redisClient *c) {
    robj *set, *ele, *aux;
    int64_t llele;
    int encoding;

    if (c->argc == 3) {
        spopWithCountCommand(c);
        return;
    } else if (c->argc > 3) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* Make sure a key with the name inputted exists, and that it's type is 
       indeed a set */
    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,set,REDIS_SET)) return;

    /* Get a random element from the set */
    encoding = setTypeRandomElement(set,&ele,&llele);

    /* Remove the element from the set */
    if (encoding == REDIS_ENCODING_INTSET) {
        ele = createStringObjectFromLongLong(llele);
        set->ptr = intsetRemove(set->ptr,llele,NULL);
    } else {
        incrRefCount(ele);
        setTypeRemove(set,ele);
    }

    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);

    /* Replicate/AOF this command as an SREM operation */
