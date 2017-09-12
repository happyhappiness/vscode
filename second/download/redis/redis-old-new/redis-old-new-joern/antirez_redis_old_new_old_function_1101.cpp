void rpoplpushHandlePush(client *c, robj *dstkey, robj *dstobj, robj *value) {
    /* Create the list if the key does not exist */
    if (!dstobj) {
        dstobj = createQuicklistObject();
        quicklistSetOptions(dstobj->ptr, server.list_max_ziplist_size,
                            server.list_compress_depth);
        dbAdd(c->db,dstkey,dstobj);
    }
    signalModifiedKey(c->db,dstkey);
    listTypePush(dstobj,value,REDIS_HEAD);
    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lpush",dstkey,c->db->id);
    /* Always send the pushed value to the client. */
    addReplyBulk(c,value);
}