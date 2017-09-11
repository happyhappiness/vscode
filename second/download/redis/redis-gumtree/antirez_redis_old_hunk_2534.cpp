    /* An extra key has changed when ele was successfully added to dstset */
    if (setTypeAdd(dstset,ele)) {
        server.dirty++;
        notifyKeyspaceEvent("sadd",c->argv[2],c->db->id);
    }
    addReply(c,shared.cone);
}
