    sdsfree(bitcounters);
}

/* PFGETREG
 * Return the registers values of the specified HLL. */
void pfgetregCommand(redisClient *c) {
    robj *o = lookupKeyRead(c->db,c->argv[1]);
    struct hllhdr *hdr;
    int j;

    if (o == NULL) {
        addReplyError(c,"The specified key does not exist");
        return;
    } else {
        if (isHLLObjectOrReply(c,o) != REDIS_OK) return;

        hdr = o->ptr;
        addReplyMultiBulkLen(c,HLL_REGISTERS);
        for (j = 0; j < HLL_REGISTERS; j++) {
            uint8_t val;

            HLL_DENSE_GET_REGISTER(val,hdr->registers,j);
            addReplyLongLong(c,val);
        }
    }
}
