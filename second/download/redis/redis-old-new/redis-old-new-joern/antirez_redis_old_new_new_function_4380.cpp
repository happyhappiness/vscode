static void zrangebyscoreCommand(redisClient *c) {
    robj *o;
    double min = strtod(c->argv[2]->ptr,NULL);
    double max = strtod(c->argv[3]->ptr,NULL);

    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullmultibulk);
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            zset *zsetobj = o->ptr;
            zskiplist *zsl = zsetobj->zsl;
            zskiplistNode *ln;
            robj *ele, *lenobj;
            unsigned int rangelen = 0;

            /* Get the first node with the score >= min */
            ln = zslFirstWithScore(zsl,min);
            if (ln == NULL) {
                /* No element matching the speciifed interval */
                addReply(c,shared.emptymultibulk);
                return;
            }

            /* We don't know in advance how many matching elements there
             * are in the list, so we push this object that will represent
             * the multi-bulk length in the output buffer, and will "fix"
             * it later */
            lenobj = createObject(REDIS_STRING,NULL);
            addReply(c,lenobj);

            while(ln->score <= max) {
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = ln->forward[0];
                rangelen++;
            }
            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
        }
    }
}