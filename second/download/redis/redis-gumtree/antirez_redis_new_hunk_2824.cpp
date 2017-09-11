    case REDIS_REPLY_INTEGER:
        break; /* Nothing to free */
    case REDIS_REPLY_ARRAY:
        if (r->element != NULL) {
            for (j = 0; j < r->elements; j++)
                if (r->element[j] != NULL)
                    freeReplyObject(r->element[j]);
            free(r->element);
        }
        break;
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_STRING:
        if (r->str != NULL)
            free(r->str);
        break;
    }
    free(r);
}

static void *createStringObject(const redisReadTask *task, char *str, size_t len) {
    redisReply *r, *parent;
    char *buf;

    r = createReplyObject(task->type);
    if (r == NULL)
        return NULL;

    buf = malloc(len+1);
    if (buf == NULL) {
        freeReplyObject(r);
        return NULL;
    }

    assert(task->type == REDIS_REPLY_ERROR  ||
           task->type == REDIS_REPLY_STATUS ||
           task->type == REDIS_REPLY_STRING);

    /* Copy string value */
    memcpy(buf,str,len);
    buf[len] = '\0';
    r->str = buf;
    r->len = len;

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY);
        parent->element[task->idx] = r;
    }
    return r;
}

static void *createArrayObject(const redisReadTask *task, int elements) {
    redisReply *r, *parent;

    r = createReplyObject(REDIS_REPLY_ARRAY);
    if (r == NULL)
        return NULL;

    if (elements > 0) {
        r->element = calloc(elements,sizeof(redisReply*));
        if (r->element == NULL) {
            freeReplyObject(r);
            return NULL;
        }
    }

    r->elements = elements;

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY);
        parent->element[task->idx] = r;
    }
    return r;
}

static void *createIntegerObject(const redisReadTask *task, long long value) {
    redisReply *r, *parent;

    r = createReplyObject(REDIS_REPLY_INTEGER);
    if (r == NULL)
        return NULL;

    r->integer = value;

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY);
        parent->element[task->idx] = r;
    }
    return r;
}

static void *createNilObject(const redisReadTask *task) {
    redisReply *r, *parent;

    r = createReplyObject(REDIS_REPLY_NIL);
    if (r == NULL)
        return NULL;

    if (task->parent) {
        parent = task->parent->obj;
        assert(parent->type == REDIS_REPLY_ARRAY);
        parent->element[task->idx] = r;
    }
    return r;
}

static void __redisReaderSetError(redisReader *r, int type, const char *str) {
    size_t len;

    if (r->reply != NULL && r->fn && r->fn->freeObject) {
        r->fn->freeObject(r->reply);
        r->reply = NULL;
    }

    /* Clear input buffer on errors. */
    if (r->buf != NULL) {
        sdsfree(r->buf);
        r->buf = NULL;
        r->pos = r->len = 0;
    }

    /* Reset task stack. */
    r->ridx = -1;

    /* Set error. */
    r->err = type;
    len = strlen(str);
    len = len < (sizeof(r->errstr)-1) ? len : (sizeof(r->errstr)-1);
    memcpy(r->errstr,str,len);
    r->errstr[len] = '\0';
}

static size_t chrtos(char *buf, size_t size, char byte) {
    size_t len = 0;

    switch(byte) {
    case '\\':
    case '"':
        len = snprintf(buf,size,"\"\\%c\"",byte);
        break;
    case '\n': len = snprintf(buf,size,"\"\\n\""); break;
    case '\r': len = snprintf(buf,size,"\"\\r\""); break;
    case '\t': len = snprintf(buf,size,"\"\\t\""); break;
    case '\a': len = snprintf(buf,size,"\"\\a\""); break;
    case '\b': len = snprintf(buf,size,"\"\\b\""); break;
    default:
        if (isprint(byte))
            len = snprintf(buf,size,"\"%c\"",byte);
        else
            len = snprintf(buf,size,"\"\\x%02x\"",(unsigned char)byte);
        break;
    }

    return len;
}

static void __redisReaderSetErrorProtocolByte(redisReader *r, char byte) {
    char cbuf[8], sbuf[128];

    chrtos(cbuf,sizeof(cbuf),byte);
    snprintf(sbuf,sizeof(sbuf),
        "Protocol error, got %s as reply type byte", cbuf);
    __redisReaderSetError(r,REDIS_ERR_PROTOCOL,sbuf);
}

static void __redisReaderSetErrorOOM(redisReader *r) {
    __redisReaderSetError(r,REDIS_ERR_OOM,"Out of memory");
}

static char *readBytes(redisReader *r, unsigned int bytes) {
    char *p;
    if (r->len-r->pos >= bytes) {
