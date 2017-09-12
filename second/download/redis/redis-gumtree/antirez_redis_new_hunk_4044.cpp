}

static void lremCommand(redisClient *c) {
    robj *subject, *obj = c->argv[3];
    int toremove = atoi(c->argv[2]->ptr);
    int removed = 0;
    int direction;

    subject = lookupKeyWriteOrReply(c,c->argv[1],shared.czero);
    if (subject == NULL || checkType(c,subject,REDIS_LIST)) return;

    /* Make sure obj is raw when we're dealing with a ziplist */
    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
        obj = getDecodedObject(obj);

    lIterator *li;
    if (toremove < 0) {
        toremove = -toremove;
        direction = REDIS_HEAD;
        li = lInitIterator(subject,-1);
    } else {
        direction = REDIS_TAIL;
        li = lInitIterator(subject,0);
    }

    while (toremove && lIsEntry(li)) {
        if (lEqualTo(li,obj)) {
            lDelete(li,direction);
            server.dirty++;
            toremove--;
            removed++;
        } else {
            lMove(li,direction);
        }
    }
    lReleaseIterator(li);

    /* Clean up raw encoded object */
    if (subject->encoding == REDIS_ENCODING_ZIPLIST)
        decrRefCount(obj);

    if (lLength(subject) == 0) deleteKey(c->db,c->argv[1]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

