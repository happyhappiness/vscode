    addReply(c,shared.cone);
}

/* Helper function for dbSwapDatabases(): scans the list of keys that have
 * one or more blocked clients for B[LR]POP or other list blocking commands
 * and signal the keys are ready if they are lists. See the comment where
 * the function is used for more info. */
void scanDatabaseForReadyLists(redisDb *db) {
    dictEntry *de;
    dictIterator *di = dictGetSafeIterator(db->blocking_keys);
    while((de = dictNext(di)) != NULL) {
        robj *key = dictGetKey(de);
        robj *value = lookupKey(db,key,LOOKUP_NOTOUCH);
        if (value && value->type == OBJ_LIST)
            signalListAsReady(db, key);
    }
    dictReleaseIterator(di);
}

/* Swap two databases at runtime so that all clients will magically see
 * the new database even if already connected. Note that the client
 * structure c->db points to a given DB, so we need to be smarter and
 * swap the underlying referenced structures, otherwise we would need
 * to fix all the references to the Redis DB structure.
 *
 * Returns C_ERR if at least one of the DB ids are out of range, otherwise
 * C_OK is returned. */
int dbSwapDatabases(int id1, int id2) {
    if (id1 < 0 || id1 >= server.dbnum ||
        id2 < 0 || id2 >= server.dbnum) return C_ERR;
    if (id1 == id2) return C_OK;
    redisDb aux = server.db[id1];
    redisDb *db1 = &server.db[id1], *db2 = &server.db[id2];

    /* Swap hash tables. Note that we don't swap blocking_keys,
     * ready_keys and watched_keys, since we want clients to
     * remain in the same DB they were. */
    db1->dict = db2->dict;
    db1->expires = db2->expires;
    db1->avg_ttl = db2->avg_ttl;

    db2->dict = aux.dict;
    db2->expires = aux.expires;
    db2->avg_ttl = aux.avg_ttl;

    /* Now we need to handle clients blocked on lists: as an effect
     * of swapping the two DBs, a client that was waiting for list
     * X in a given DB, may now actually be unblocked if X happens
     * to exist in the new version of the DB, after the swap.
     *
     * However normally we only do this check for efficiency reasons
     * in dbAdd() when a list is created. So here we need to rescan
     * the list of clients blocked on lists and signal lists as ready
     * if needed. */
    scanDatabaseForReadyLists(db1);
    scanDatabaseForReadyLists(db2);
    return C_OK;
}

/* SWAPDB db1 db2 */
void swapdbCommand(client *c) {
    long id1, id2;

    /* Not allowed in cluster mode: we have just DB 0 there. */
    if (server.cluster_enabled) {
        addReplyError(c,"SWAPDB is not allowed in cluster mode");
        return;
    }

    /* Get the two DBs indexes. */
    if (getLongFromObjectOrReply(c, c->argv[1], &id1,
        "invalid first DB index") != C_OK)
        return;

    if (getLongFromObjectOrReply(c, c->argv[2], &id2,
        "invalid second DB index") != C_OK)
        return;

    /* Swap... */
    if (dbSwapDatabases(id1,id2) == C_ERR) {
        addReplyError(c,"DB index is out of range");
        return;
    } else {
        server.dirty++;
        addReply(c,shared.ok);
    }
}

/*-----------------------------------------------------------------------------
 * Expires API
 *----------------------------------------------------------------------------*/
