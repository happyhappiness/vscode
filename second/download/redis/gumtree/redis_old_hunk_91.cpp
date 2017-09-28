
    /* If the element cannot be removed from the src set, return 0. */
    if (!setTypeRemove(srcset,ele)) {
        addReply(c,shared.czero);
        return;
    }

    /* Remove the src set from the database when empty */
    if (setTypeSize(srcset) == 0) dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[2]);
    server.dirty++;

    /* Create the destination set when it doesn't exist */
    if (!dstset) {
        dstset = setTypeCreate(ele);
        dbAdd(c->db,c->argv[2],dstset);
    }

    /* An extra key has changed when ele was successfully added to dstset */
    if (setTypeAdd(dstset,ele)) server.dirty++;
    addReply(c,shared.cone);
}

void sismemberCommand(redisClient *c) {
    robj *set;

