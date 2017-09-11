    long ttl;

    /* Make sure this key does not already exist here... */
    if (dbExists(c->db,c->argv[1])) {
        addReplyError(c,"Target key name is busy.");
        return;
    }
