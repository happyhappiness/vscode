    removeExpire(c->db,c->argv[1]);
}

static int getBitOffsetFromArgument(redisClient *c, robj *o, size_t *offset) {
    long long loffset;
    char *err = "bit offset is not an integer or out of range";

    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != REDIS_OK)
        return REDIS_ERR;

    /* Limit offset to SIZE_T_MAX or 512MB in bytes */
    if ((loffset < 0) ||
        ((unsigned long long)loffset >= (unsigned)SIZE_T_MAX) ||
        ((unsigned long long)loffset >> 3) >= (512*1024*1024))
    {
        addReplyError(c,err);
        return REDIS_ERR;
    }

    *offset = (size_t)loffset;
    return REDIS_OK;
}

void setbitCommand(redisClient *c) {
    robj *o;
    char *err = "bit is not an integer or out of range";
    size_t bitoffset;
    long long bitvalue;
    int byte, bit, on;

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    if (getLongLongFromObjectOrReply(c,c->argv[3],&bitvalue,err) != REDIS_OK)
        return;

    /* A bit can only be set to be on or off... */
    if (bitvalue & ~1) {
        addReplyError(c,err);
        return;
    }

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        o = createObject(REDIS_STRING,sdsempty());
        dbAdd(c->db,c->argv[1],o);
    } else {
        if (checkType(c,o,REDIS_STRING)) return;

        /* Create a copy when the object is shared or encoded. */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);
            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dbReplace(c->db,c->argv[1],o);
        }
    }

    byte = bitoffset >> 3;
    bit = 7 - (bitoffset & 0x7);
    on = bitvalue & 0x1;
    o->ptr = sdsgrowzero(o->ptr,byte+1);
    ((char*)o->ptr)[byte] |= on << bit;
    ((char*)o->ptr)[byte] &= ~((!on) << bit);

    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.cone);
}

void getbitCommand(redisClient *c) {
    robj *o;
    size_t bitoffset, byte, bitmask;
    int on = 0;
    char llbuf[32];

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    byte = bitoffset >> 3;
    bitmask = 1 << (7 - (bitoffset & 0x7));
    if (o->encoding != REDIS_ENCODING_RAW) {
        if (byte < (size_t)ll2string(llbuf,sizeof(llbuf),(long)o->ptr))
            on = llbuf[byte] & bitmask;
    } else {
        if (byte < sdslen(o->ptr))
            on = ((sds)o->ptr)[byte] & bitmask;
    }
    addReply(c, on ? shared.cone : shared.czero);
}

void setrangeCommand(redisClient *c) {
    robj *o;
    long offset;
    sds value = c->argv[3]->ptr;

    if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
        return;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        /* Negative offset is always 0 for non-existing keys */
        if (offset < 0) offset = 0;

        /* Return 0 when setting nothing on a non-existing string */
        if (sdslen(value) == 0) {
            addReply(c,shared.czero);
            return;
        }

        /* Return when the resulting string exceeds allowed size */
        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
            return;

        o = createObject(REDIS_STRING,sdsempty());
        dbAdd(c->db,c->argv[1],o);
    } else {
        int olen;

        /* Key exists, check type */
        if (checkType(c,o,REDIS_STRING))
            return;

        /* Find out existing value length */
        if (o->encoding == REDIS_ENCODING_INT) {
            char llbuf[32];
            olen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
        } else {
            olen = sdslen(o->ptr);
        }

        /* Return existing string length when setting nothing */
        if (sdslen(value) == 0) {
            addReplyLongLong(c,olen);
            return;
        }

        /* Convert negative indexes. Note that for SETRANGE, the meaning of a
         * negative index is a little different than for other commands.
         * Here, an offset of -1 points to the trailing NULL byte of the
         * string instead of the last character. */
        if (offset < 0) {
            offset = olen+1+offset;
            if (offset < 0) offset = 0;
        }

        /* Return when the resulting string exceeds allowed size */
        if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
            return;

        /* Create a copy when the object is shared or encoded. */
        if (o->refcount != 1 || o->encoding != REDIS_ENCODING_RAW) {
            robj *decoded = getDecodedObject(o);
            o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
            decrRefCount(decoded);
            dbReplace(c->db,c->argv[1],o);
        }
    }

    if (sdslen(value) > 0) {
        o->ptr = sdsgrowzero(o->ptr,offset+sdslen(value));
        memcpy((char*)o->ptr+offset,value,sdslen(value));
        touchWatchedKey(c->db,c->argv[1]);
        server.dirty++;
    }
    addReplyLongLong(c,sdslen(o->ptr));
}

void getrangeCommand(redisClient *c) {
    robj *o;
    long start, end;
    char *str, llbuf[32];
    size_t strlen;

    if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
        return;
    if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
        return;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_STRING)) return;

    if (o->encoding == REDIS_ENCODING_INT) {
        str = llbuf;
        strlen = ll2string(llbuf,sizeof(llbuf),(long)o->ptr);
    } else {
        str = o->ptr;
        strlen = sdslen(str);
    }

    /* Convert negative indexes */
    if (start < 0) start = strlen+start;
    if (end < 0) end = strlen+end;
    if (start < 0) start = 0;
    if (end < 0) end = 0;
    if ((unsigned)end >= strlen) end = strlen-1;

    /* Precondition: end >= 0 && end < strlen, so the only condition where
     * nothing can be returned is: start > end. */
    if (start > end) {
        addReply(c,shared.nullbulk);
    } else {
        addReplyBulkCBuffer(c,(char*)str+start,end-start+1);
    }
}

void mgetCommand(redisClient *c) {
    int j;

