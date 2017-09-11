        return;
    }

    /* Get the size of the set. It is always > 0, as empty sets get
     * deleted.  */
    size = setTypeSize(set);

    /* Generate an SPOP keyspace notification */
    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);

    /* CASE 1:
     * The number of requested elements is greater than or equal to
