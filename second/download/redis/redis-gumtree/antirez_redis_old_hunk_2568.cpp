    }
    signalModifiedKey(c->db,dstkey);
    listTypePush(dstobj,value,REDIS_HEAD);
    /* Always send the pushed value to the client. */
    addReplyBulk(c,value);
}
