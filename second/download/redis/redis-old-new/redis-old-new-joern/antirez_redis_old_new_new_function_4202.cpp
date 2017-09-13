static void zrangebyscoreCommand(redisClient *c) {
    robj *o;
    double min = strtod(c->argv[2]->ptr,NULL);
    double max = strtod(c->argv[3]->ptr,NULL);
    int offset = 0, limit = -1;
    int withscores = 0;
    int badsyntax = 0;

    if (c->argc == 5 || c->argc == 8) {
        if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0) withscores = 1;
        else badsyntax = 1;
    }

    if (c->argc != (4 + withscores) && c->argc != (7 + withscores)) {
        badsyntax = 1;
    }


    if (badsyntax) {
        addReplySds(c,
            sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
        return;
    }

    if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
        addReply(c,shared.syntaxerr);
        return;
    } else if (c->argc == (7 + withscores)) {
        offset = atoi(c->argv[5]->ptr);
        limit = atoi(c->argv[6]->ptr);
        if (offset < 0) offset = 0;
    }

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
            decrRefCount(lenobj);

            while(ln && ln->score <= max) {
                if (offset) {
                    offset--;
                    ln = ln->forward[0];
                    continue;
                }
                if (limit == 0) break;
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                if (withscores)
                    addReplyDouble(c,ln->score);
                ln = ln->forward[0];
                rangelen++;
                if (limit > 0) limit--;
            }
            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",
		 withscores ? (rangelen*2) : rangelen);
        }
    }
}