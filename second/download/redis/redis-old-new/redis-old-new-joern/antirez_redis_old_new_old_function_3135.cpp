static int processItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
    char *p;
    sds byte;

    /* check if we need to read type */
    if (cur->type < 0) {
        if ((p = readBytes(r,1)) != NULL) {
            switch (p[0]) {
            case '-':
                cur->type = REDIS_REPLY_ERROR;
                break;
            case '+':
                cur->type = REDIS_REPLY_STATUS;
                break;
            case ':':
                cur->type = REDIS_REPLY_INTEGER;
                break;
            case '$':
                cur->type = REDIS_REPLY_STRING;
                break;
            case '*':
                cur->type = REDIS_REPLY_ARRAY;
                break;
            default:
                byte = sdscatrepr(sdsempty(),p,1);
                redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
                    "protocol error, got %s as reply type byte", byte));
                sdsfree(byte);
                return -1;
            }
        } else {
            /* could not consume 1 byte */
            return -1;
        }
    }

    /* process typed item */
    switch(cur->type) {
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
    case REDIS_REPLY_INTEGER:
        return processLineItem(r);
    case REDIS_REPLY_STRING:
        return processBulkItem(r);
    case REDIS_REPLY_ARRAY:
        return processMultiBulkItem(r);
    default:
        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "unknown item type '%d'", cur->type));
        return -1;
    }
}