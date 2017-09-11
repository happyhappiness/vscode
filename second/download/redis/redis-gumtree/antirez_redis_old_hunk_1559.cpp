        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);

        /* Replicate/AOF this command as an SREM operation */
        rewriteClientCommandVector(c,2,shared.del,c->argv[1]);
        signalModifiedKey(c->db,c->argv[1]);
        server.dirty++;
        return;
    }

    /* CASE 2:
     * The number of requested elements is less than the number
     * of elements inside the set. */

    /* We need an auxiliary set. Optimistically, we create a set using an
     * Intset internally. */
    aux_set = createIntsetObject();

    /* Get the count requested of random elements from the set into our
     * auxiliary set. */
    elements_returned = setTypeRandomElements(set, count, aux_set);
    redisAssert(elements_returned == count);

    {
        setTypeIterator *si;
        robj *objele, *propargv[3];
        int element_encoding;

        addReplyMultiBulkLen(c, elements_returned);
        propargv[0] = createStringObject("SREM",4);
        propargv[1] = c->argv[1];

        si = setTypeInitIterator(aux_set);
        while ((element_encoding = setTypeNext(si, &objele, &llele)) != -1) {
            if (element_encoding == REDIS_ENCODING_HT) {
                incrRefCount(objele);
            } else if (element_encoding == REDIS_ENCODING_INTSET) {
                objele = createStringObjectFromLongLong(llele);
            } else {
                redisPanic("Unknown set encoding");
            }
            setTypeRemove(set, objele);
            addReplyBulk(c, objele);

            /* Replicate/AOF this command as an SREM operation */
            propargv[2] = objele;
            alsoPropagate(server.sremCommand,c->db->id,propargv,3,REDIS_PROPAGATE_AOF|REDIS_PROPAGATE_REPL);

            decrRefCount(objele);
            server.dirty++;
        }
        decrRefCount(propargv[0]);
        setTypeReleaseIterator(si);
    }

    /* Don't propagate the command itself even if we incremented the
     * dirty counter. We don't want to propagate an SPOP command since
     * we propagated the command as a set of SREMs operations using
     * the alsoPropagate() API. */
    preventCommandPropagation(c);
    decrRefCount(aux_set);
}

void spopCommand(redisClient *c) {
