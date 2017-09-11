
    /* Create the destination set when it doesn't exist */
    if (!dstset) {
        dstset = setTypeCreate(ele->ptr);
        dbAdd(c->db,c->argv[2],dstset);
    }

    /* An extra key has changed when ele was successfully added to dstset */
    if (setTypeAdd(dstset,ele->ptr)) {
        server.dirty++;
        notifyKeyspaceEvent(NOTIFY_SET,"sadd",c->argv[2],c->db->id);
    }
