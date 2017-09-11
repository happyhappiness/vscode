        return processMultiBulkItem(r);
    default:
        assert(NULL);
        return -1;
    }
}

void *redisReplyReaderCreate(void) {
    redisReader *r = calloc(sizeof(redisReader),1);
    r->error = NULL;
    r->fn = &defaultFunctions;
    r->buf = sdsempty();
    r->ridx = -1;
    return r;
}

/* Set the function set to build the reply. Returns REDIS_OK when there
 * is no temporary object and it can be set, REDIS_ERR otherwise. */
int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn) {
    redisReader *r = reader;
    if (r->reply == NULL) {
        r->fn = fn;
        return REDIS_OK;
    }
    return REDIS_ERR;
}

/* Set the private data field that is used in the read tasks. This argument can
 * be used to curry arbitrary data to the custom reply object functions. */
int redisReplyReaderSetPrivdata(void *reader, void *privdata) {
    redisReader *r = reader;
    if (r->reply == NULL) {
        r->privdata = privdata;
        return REDIS_OK;
    }
    return REDIS_ERR;
}

/* External libraries wrapping hiredis might need access to the temporary
 * variable while the reply is built up. When the reader contains an
 * object in between receiving some bytes to parse, this object might
 * otherwise be free'd by garbage collection. */
void *redisReplyReaderGetObject(void *reader) {
    redisReader *r = reader;
    return r->reply;
}

void redisReplyReaderFree(void *reader) {
    redisReader *r = reader;
    if (r->error != NULL)
        sdsfree(r->error);
    if (r->reply != NULL && r->fn)
        r->fn->freeObject(r->reply);
    if (r->buf != NULL)
        sdsfree(r->buf);
    free(r);
}

static void redisSetReplyReaderError(redisReader *r, sds err) {
    if (r->reply != NULL)
        r->fn->freeObject(r->reply);

    /* Clear remaining buffer when we see a protocol error. */
    if (r->buf != NULL) {
        sdsfree(r->buf);
        r->buf = sdsempty();
        r->pos = r->len = 0;
    }
    r->ridx = -1;
    r->error = err;
}

char *redisReplyReaderGetError(void *reader) {
    redisReader *r = reader;
    return r->error;
}

void redisReplyReaderFeed(void *reader, const char *buf, size_t len) {
    redisReader *r = reader;

    /* Copy the provided buffer. */
    if (buf != NULL && len >= 1) {
#if 0
        /* Destroy internal buffer when it is empty and is quite large. */
        if (r->len == 0 && sdsavail(r->buf) > 16*1024) {
            sdsfree(r->buf);
            r->buf = sdsempty();
            r->pos = 0;
        }
#endif
        r->buf = sdscatlen(r->buf,buf,len);
        r->len = sdslen(r->buf);
    }
}

int redisReplyReaderGetReply(void *reader, void **reply) {
    redisReader *r = reader;
    if (reply != NULL) *reply = NULL;

    /* When the buffer is empty, there will never be a reply. */
    if (r->len == 0)
