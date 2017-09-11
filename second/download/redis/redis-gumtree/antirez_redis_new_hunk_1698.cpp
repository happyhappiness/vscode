        return;
    }

    /* Make sure a key with the name inputted exists, and that it's type is
     * indeed a set. Otherwise, return nil */
    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk))
        == NULL || checkType(c,set,REDIS_SET)) return;

    /* If count is zero, serve an empty multibulk ASAP to avoid special
     * cases later. */
    if (count == 0) {
        addReply(c,shared.emptymultibulk);
        return;
    }

    /* Get the size of the set. It is always > 0, as empty sets get
     * deleted.  */
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
