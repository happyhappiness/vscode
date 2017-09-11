    membersOfAllNeighbors(zobj, georadius, xy[0], xy[1], radius_meters, ga);

    /* If no matching results, the user gets an empty reply. */
    if (ga->used == 0 && storekey == NULL) {
        addReply(c, shared.emptymultibulk);
        geoArrayFree(ga);
        return;
    }

    long result_length = ga->used;
    long returned_items = (count == 0 || result_length < count) ?
                          result_length : count;
    long option_length = 0;

    /* Process [optional] requested sorting */
    if (sort == SORT_ASC) {
        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_asc);
    } else if (sort == SORT_DESC) {
        qsort(ga->array, result_length, sizeof(geoPoint), sort_gp_desc);
    }

    if (storekey == NULL) {
        /* No target key, return results to user. */

        /* Our options are self-contained nested multibulk replies, so we
         * only need to track how many of those nested replies we return. */
        if (withdist)
            option_length++;

        if (withcoords)
            option_length++;

        if (withhash)
            option_length++;

        /* The multibulk len we send is exactly result_length. The result is
         * either all strings of just zset members  *or* a nested multi-bulk
         * reply containing the zset member string _and_ all the additional
         * options the user enabled for this request. */
        addReplyMultiBulkLen(c, returned_items);

        /* Finally send results back to the caller */
        int i;
        for (i = 0; i < returned_items; i++) {
            geoPoint *gp = ga->array+i;
            gp->dist /= conversion; /* Fix according to unit. */

            /* If we have options in option_length, return each sub-result
             * as a nested multi-bulk.  Add 1 to account for result value
             * itself. */
            if (option_length)
                addReplyMultiBulkLen(c, option_length + 1);

            addReplyBulkSds(c,gp->member);
            gp->member = NULL;

            if (withdist)
                addReplyDoubleDistance(c, gp->dist);

            if (withhash)
                addReplyLongLong(c, gp->score);

            if (withcoords) {
                addReplyMultiBulkLen(c, 2);
                addReplyDouble(c, gp->longitude);
                addReplyDouble(c, gp->latitude);
            }
        }
    } else {
        /* Target key, create a sorted set with the results. */
        robj *zobj;
        zset *zs;
        int i;
        size_t maxelelen = 0;

        if (returned_items) {
            zobj = createZsetObject();
            zs = zobj->ptr;
        }

        for (i = 0; i < returned_items; i++) {
            zskiplistNode *znode;
            geoPoint *gp = ga->array+i;
            gp->dist /= conversion; /* Fix according to unit. */
            double score = storedist ? gp->dist : gp->score;
            size_t elelen = sdslen(gp->member);

            if (maxelelen < elelen) maxelelen = elelen;
            znode = zslInsert(zs->zsl,score,gp->member);
            serverAssert(dictAdd(zs->dict,gp->member,&znode->score) == DICT_OK);
            gp->member = NULL;
        }

        if (returned_items) {
            zsetConvertToZiplistIfNeeded(zobj,maxelelen);
            setKey(c->db,storekey,zobj);
            decrRefCount(zobj);
            notifyKeyspaceEvent(NOTIFY_LIST,"georadiusstore",storekey,
                                c->db->id);
            server.dirty += returned_items;
        } else if (dbDelete(c->db,storekey)) {
            signalModifiedKey(c->db,storekey);
            notifyKeyspaceEvent(NOTIFY_GENERIC,"del",storekey,c->db->id);
            server.dirty++;
        }
        addReplyLongLong(c, returned_items);
    }
    geoArrayFree(ga);
}
