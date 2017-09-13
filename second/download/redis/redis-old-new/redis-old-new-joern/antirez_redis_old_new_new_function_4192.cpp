static void substrCommand(redisClient *c) {
    robj *o;
    long start = atoi(c->argv[2]->ptr);
    long end = atoi(c->argv[3]->ptr);

    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
        } else {
            size_t rangelen, strlen = sdslen(o->ptr);
            sds range;

            /* convert negative indexes */
            if (start < 0) start = strlen+start;
            if (end < 0) end = strlen+end;
            if (start < 0) start = 0;
            if (end < 0) end = 0;

            /* indexes sanity checks */
            if (start > end || (size_t)start >= strlen) {
                /* Out of range start or start > end result in null reply */
                addReply(c,shared.nullbulk);
                return;
            }
            if ((size_t)end >= strlen) end = strlen-1;
            rangelen = (end-start)+1;

            /* Return the result */
            addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",rangelen));
            range = sdsnewlen((char*)o->ptr+start,rangelen);
            addReplySds(c,range);
            addReply(c,shared.crlf);
        }
    }
}