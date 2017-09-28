        dstobj = createZiplistObject();
        dbAdd(c->db,dstkey,dstobj);
        signalListAsReady(c,dstkey);
    }
    signalModifiedKey(c->db,dstkey);
    listTypePush(dstobj,value,REDIS_HEAD);
    notifyKeyspaceEvent(REDIS_NOTIFY_LIST,"lpush",dstkey,c->db->id);
    /* Always send the pushed value to the client. */
    addReplyBulk(c,value);
}

void rpoplpushCommand(redisClient *c) {
    robj *sobj, *value;
