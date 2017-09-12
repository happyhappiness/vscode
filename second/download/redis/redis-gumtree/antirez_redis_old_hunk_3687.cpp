    c->pubsub_patterns = listCreate();
    listSetFreeMethod(c->pubsub_patterns,decrRefCount);
    listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
    if (aeCreateFileEvent(server.el, c->fd, AE_READABLE,
        readQueryFromClient, c) == AE_ERR) {
        freeClient(c);
        return NULL;
    }
    listAddNodeTail(server.clients,c);
    initClientMultiState(c);
    return c;
}

void addReply(redisClient *c, robj *obj) {
    if (listLength(c->reply) == 0 &&
        (c->replstate == REDIS_REPL_NONE ||
         c->replstate == REDIS_REPL_ONLINE) &&
        aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
        sendReplyToClient, c) == AE_ERR) return;

    if (server.vm_enabled && obj->storage != REDIS_VM_MEMORY) {
        obj = dupStringObject(obj);
        obj->refcount = 0; /* getDecodedObject() will increment the refcount */
    }
    listAddNodeTail(c->reply,getDecodedObject(obj));
}

void addReplySds(redisClient *c, sds s) {
    robj *o = createObject(REDIS_STRING,s);
    addReply(c,o);
    decrRefCount(o);
}

void addReplyDouble(redisClient *c, double d) {
    char buf[128];

    snprintf(buf,sizeof(buf),"%.17g",d);
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
        (unsigned long) strlen(buf),buf));
}

void addReplyLongLong(redisClient *c, long long ll) {
    char buf[128];
    size_t len;

    if (ll == 0) {
        addReply(c,shared.czero);
        return;
    } else if (ll == 1) {
        addReply(c,shared.cone);
        return;
    }
    buf[0] = ':';
    len = ll2string(buf+1,sizeof(buf)-1,ll);
    buf[len+1] = '\r';
    buf[len+2] = '\n';
    addReplySds(c,sdsnewlen(buf,len+3));
}

void addReplyUlong(redisClient *c, unsigned long ul) {
    char buf[128];
    size_t len;

    if (ul == 0) {
        addReply(c,shared.czero);
        return;
    } else if (ul == 1) {
        addReply(c,shared.cone);
        return;
    }
    len = snprintf(buf,sizeof(buf),":%lu\r\n",ul);
    addReplySds(c,sdsnewlen(buf,len));
}

void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len, intlen;
    char buf[128];

    if (obj->encoding == REDIS_ENCODING_RAW) {
        len = sdslen(obj->ptr);
