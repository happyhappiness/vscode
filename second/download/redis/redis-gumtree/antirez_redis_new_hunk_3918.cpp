    return c;
}

int _ensureFileEvent(redisClient *c) {
    if (c->bufpos == 0 && listLength(c->reply) == 0 &&
        (c->replstate == REDIS_REPL_NONE ||
         c->replstate == REDIS_REPL_ONLINE) &&
        aeCreateFileEvent(server.el, c->fd, AE_WRITABLE,
        sendReplyToClient, c) == AE_ERR) return REDIS_ERR;
    return REDIS_OK;
}

void _addReplyObjectToList(redisClient *c, robj *obj) {
    redisAssert(obj->type == REDIS_STRING &&
                obj->encoding == REDIS_ENCODING_RAW);
    listAddNodeTail(c->reply,obj);
}

void _ensureBufferInReplyList(redisClient *c) {
    sds buffer = sdsnewlen(NULL,REDIS_REPLY_CHUNK_SIZE);
    sdsupdatelen(buffer); /* sdsnewlen expects non-empty string */
    listAddNodeTail(c->reply,createObject(REDIS_REPLY_NODE,buffer));
}

void _addReplyStringToBuffer(redisClient *c, char *s, size_t len) {
    size_t available = 0;
    redisAssert(len < REDIS_REPLY_CHUNK_THRESHOLD);
    if (listLength(c->reply) > 0) {
        robj *o = listNodeValue(listLast(c->reply));

        /* Make sure to append to a reply node with enough bytes available. */
        if (o->type == REDIS_REPLY_NODE) available = sdsavail(o->ptr);
        if (o->type != REDIS_REPLY_NODE || len > available) {
            _ensureBufferInReplyList(c);
            _addReplyStringToBuffer(c,s,len);
        } else {
            o->ptr = sdscatlen(o->ptr,s,len);
        }
    } else {
        available = c->buflen-c->bufpos;
        if (len > available) {
            _ensureBufferInReplyList(c);
            _addReplyStringToBuffer(c,s,len);
        } else {
            memcpy(c->buf+c->bufpos,s,len);
            c->bufpos += len;
        }
    }
}

void addReply(redisClient *c, robj *obj) {
    if (_ensureFileEvent(c) != REDIS_OK) return;
    if (server.vm_enabled && obj->storage != REDIS_VM_MEMORY) {
        /* Returns a new object with refcount 1 */
        obj = dupStringObject(obj);
    } else {
        /* This increments the refcount. */
        obj = getDecodedObject(obj);
    }

    if (sdslen(obj->ptr) < REDIS_REPLY_CHUNK_THRESHOLD) {
        _addReplyStringToBuffer(c,obj->ptr,sdslen(obj->ptr));
        decrRefCount(obj);
    } else {
        _addReplyObjectToList(c,obj);
    }
}

void addReplySds(redisClient *c, sds s) {
    if (_ensureFileEvent(c) != REDIS_OK) return;
    if (sdslen(s) < REDIS_REPLY_CHUNK_THRESHOLD) {
        _addReplyStringToBuffer(c,s,sdslen(s));
        sdsfree(s);
    } else {
        _addReplyObjectToList(c,createObject(REDIS_STRING,s));
    }
}

void addReplyString(redisClient *c, char *s, size_t len) {
    if (_ensureFileEvent(c) != REDIS_OK) return;
    if (len < REDIS_REPLY_CHUNK_THRESHOLD) {
        _addReplyStringToBuffer(c,s,len);
    } else {
        _addReplyObjectToList(c,createStringObject(s,len));
    }
}

void addReplyDouble(redisClient *c, double d) {
    char dbuf[128], sbuf[128];
    int dlen, slen;
    dlen = snprintf(dbuf,sizeof(dbuf),"%.17g",d);
    slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",dlen,dbuf);
    addReplyString(c,sbuf,slen);
}

void _addReplyLongLong(redisClient *c, long long ll, char prefix) {
    char buf[128];
    int len;
    buf[0] = prefix;
    len = ll2string(buf+1,sizeof(buf)-1,ll);
    buf[len+1] = '\r';
    buf[len+2] = '\n';
    addReplyString(c,buf,len+3);
}

void addReplyLongLong(redisClient *c, long long ll) {
    _addReplyLongLong(c,ll,':');
}

void addReplyUlong(redisClient *c, unsigned long ul) {
    _addReplyLongLong(c,(long long)ul,':');
}

void addReplyBulkLen(redisClient *c, robj *obj) {
    size_t len;

    if (obj->encoding == REDIS_ENCODING_RAW) {
        len = sdslen(obj->ptr);
