    decrRefCount(ele);
    decrRefCount(aux);

    /* Add the element to the reply */
    addReplyBulk(c,ele);

    /* Delete the set if it's empty */
    if (setTypeSize(set) == 0) {
        dbDelete(c->db,c->argv[1]);
        notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",c->argv[1],c->db->id);
    }

    /* Set has been modified */
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
}
