        return;
    }

    size = setTypeSize(set);

    /* Generate an SPOP keyspace notification */
    notifyKeyspaceEvent(REDIS_NOTIFY_SET,"spop",c->argv[1],c->db->id);
    server.dirty += count;

    /* CASE 1:
     * The number of requested elements is greater than or equal to
