    }
    signalModifiedKey(c->db,dstkey);
    listTypePush(dstobj,value,REDIS_HEAD);
    notifyKeyspaceEvent("lpush",dstkey,c->db->id);
    /* Always send the pushed value to the client. */
    addReplyBulk(c,value);
}
