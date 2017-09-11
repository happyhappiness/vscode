
    /* Make sure this key does not already exist here... */
    if (!replace && lookupKeyWrite(c->db,c->argv[1]) != NULL) {
        addReplyError(c,"Target key name is busy.");
        return;
    }

