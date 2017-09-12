    zrankGenericCommand(c, 1);
}

/* =================================== Hashes =============================== */
static void hsetCommand(redisClient *c) {
    int update = 0;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,c->argv[1],o);
        incrRefCount(c->argv[1]);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }
    /* We want to convert the zipmap into an hash table right now if the
     * entry to be added is too big. Note that we check if the object
     * is integer encoded before to try fetching the length in the test below.
     * This is because integers are small, but currently stringObjectLen()
     * performs a slow conversion: not worth it. */
    if (o->encoding == REDIS_ENCODING_ZIPMAP &&
        ((c->argv[2]->encoding == REDIS_ENCODING_RAW &&
          sdslen(c->argv[2]->ptr) > server.hash_max_zipmap_value) ||
         (c->argv[3]->encoding == REDIS_ENCODING_RAW &&
          sdslen(c->argv[3]->ptr) > server.hash_max_zipmap_value)))
    {
        convertToRealHash(o);
    }

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        robj *valobj = getDecodedObject(c->argv[3]);

        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            valobj->ptr,sdslen(valobj->ptr),&update);
        decrRefCount(valobj);
        o->ptr = zm;

        /* And here there is the second check for hash conversion. */
        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        c->argv[2] = tryObjectEncoding(c->argv[2]);
        /* note that c->argv[3] is already encoded, as the latest arg
         * of a bulk command is always integer encoded if possible. */
        if (dictReplace(o->ptr,c->argv[2],c->argv[3])) {
            incrRefCount(c->argv[2]);
        } else {
            update = 1;
        }
        incrRefCount(c->argv[3]);
    }
    server.dirty++;
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",update == 0));
}

static void hmsetCommand(redisClient *c) {
    int i;
    robj *o, *key, *val;

    if ((c->argc % 2) == 1) {
        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
        return;
    }

    if ((o = lookupKeyWrite(c->db,c->argv[1])) == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,c->argv[1],o);
        incrRefCount(c->argv[1]);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    /* We want to convert the zipmap into an hash table right now if the
     * entry to be added is too big. */
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        for (i = 2; i < c->argc; i+=2) {
            if ((c->argv[i]->encoding == REDIS_ENCODING_RAW &&
                  sdslen(c->argv[i]->ptr) > server.hash_max_zipmap_value) ||
                (c->argv[i+1]->encoding == REDIS_ENCODING_RAW &&
                  sdslen(c->argv[i+1]->ptr) > server.hash_max_zipmap_value)) {
                convertToRealHash(o);
                break;
            }
        }
    }

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;

        for (i = 2; i < c->argc; i+=2) {
            key = getDecodedObject(c->argv[i]);
            val = getDecodedObject(c->argv[i+1]);
            zm = zipmapSet(zm,key->ptr,sdslen(key->ptr),
                              val->ptr,sdslen(val->ptr),NULL);
            decrRefCount(key);
            decrRefCount(val);
            o->ptr = zm;
        }

        /* And here there is the second check for hash conversion. */
        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        for (i = 2; i < c->argc; i+=2) {
            key = tryObjectEncoding(c->argv[i]);
            val = tryObjectEncoding(c->argv[i+1]);
            if (dictReplace(o->ptr,key,val)) {
                incrRefCount(key);
            }
            incrRefCount(val);
        }
    }

    addReply(c, shared.ok);
}

static void hincrbyCommand(redisClient *c) {
    long long value = 0, incr = 0;
    robj *o = lookupKeyWrite(c->db,c->argv[1]);

    if (o == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,c->argv[1],o);
        incrRefCount(c->argv[1]);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    if (getLongLongFromObject(c, c->argv[3], &incr) != REDIS_OK) return;

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *zval;
        unsigned int zvlen;

        /* Find value if already present in hash */
        if (zipmapGet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            &zval,&zvlen)) {
            /* strtoll needs the char* to have a trailing \0, but
             * the zipmap doesn't include them. */
            sds szval = sdsnewlen(zval, zvlen);
            value = strtoll(szval,NULL,10);
            sdsfree(szval);
        }

        value += incr;
        sds svalue = sdscatprintf(sdsempty(),"%lld",value);
        zm = zipmapSet(zm,c->argv[2]->ptr,sdslen(c->argv[2]->ptr),
            (unsigned char*)svalue,sdslen(svalue),NULL);
        sdsfree(svalue);
        o->ptr = zm;

        /* Check if the zipmap needs to be converted. */
        if (zipmapLen(zm) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        robj *hval;
        dictEntry *de;

        /* Find value if already present in hash */
        de = dictFind(o->ptr,c->argv[2]);
        if (de != NULL) {
            hval = dictGetEntryVal(de);
            if (hval->encoding == REDIS_ENCODING_RAW)
                value = strtoll(hval->ptr,NULL,10);
            else if (hval->encoding == REDIS_ENCODING_INT)
                value = (long)hval->ptr;
            else
                redisAssert(1 != 1);
        }

        value += incr;
        hval = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
        hval = tryObjectEncoding(hval);
        if (dictReplace(o->ptr,c->argv[2],hval)) {
            incrRefCount(c->argv[2]);
        }
    }

    server.dirty++;
    addReplyLongLong(c, value);
}

static void hgetCommand(redisClient *c) {
    robj *o;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *val;
        unsigned int vlen;
        robj *field;

        field = getDecodedObject(c->argv[2]);
        if (zipmapGet(zm,field->ptr,sdslen(field->ptr), &val,&vlen)) {
            addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
            addReplySds(c,sdsnewlen(val,vlen));
            addReply(c,shared.crlf);
            decrRefCount(field);
            return;
        } else {
            addReply(c,shared.nullbulk);
            decrRefCount(field);
            return;
        }
    } else {
        struct dictEntry *de;

        de = dictFind(o->ptr,c->argv[2]);
        if (de == NULL) {
            addReply(c,shared.nullbulk);
        } else {
            robj *e = dictGetEntryVal(de);

            addReplyBulk(c,e);
        }
    }
}

static void hmgetCommand(redisClient *c) {
    int i;

    robj *o = lookupKeyRead(c->db, c->argv[1]);
    if (o == NULL) {
        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
        for (i = 2; i < c->argc; i++) {
            addReply(c,shared.nullbulk);
        }
        return;
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *zm = o->ptr;
        unsigned char *v;
        unsigned int vlen;
        robj *field;

        for (i = 2; i < c->argc; i++) {
            field = getDecodedObject(c->argv[i]);
            if (zipmapGet(zm,field->ptr,sdslen(field->ptr),&v,&vlen)) {
                addReplySds(c,sdscatprintf(sdsempty(),"$%u\r\n", vlen));
                addReplySds(c,sdsnewlen(v,vlen));
                addReply(c,shared.crlf);
            } else {
                addReply(c,shared.nullbulk);
            }
            decrRefCount(field);
        }
    } else {
        dictEntry *de;

        for (i = 2; i < c->argc; i++) {
            de = dictFind(o->ptr,c->argv[i]);
            if (de != NULL) {
                addReplyBulk(c,(robj*)dictGetEntryVal(de));
            } else {
                addReply(c,shared.nullbulk);
            }
        }
    }
}

static void hdelCommand(redisClient *c) {
    robj *o;
    int deleted = 0;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        robj *field = getDecodedObject(c->argv[2]);

        o->ptr = zipmapDel((unsigned char*) o->ptr,
            (unsigned char*) field->ptr,
            sdslen(field->ptr), &deleted);
        decrRefCount(field);
        if (zipmapLen((unsigned char*) o->ptr) == 0)
            deleteKey(c->db,c->argv[1]);
    } else {
        deleted = dictDelete((dict*)o->ptr,c->argv[2]) == DICT_OK;
        if (htNeedsResize(o->ptr)) dictResize(o->ptr);
        if (dictSize((dict*)o->ptr) == 0) deleteKey(c->db,c->argv[1]);
    }
    if (deleted) server.dirty++;
    addReply(c,deleted ? shared.cone : shared.czero);
}

static void hlenCommand(redisClient *c) {
    robj *o;
    unsigned long len;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    len = (o->encoding == REDIS_ENCODING_ZIPMAP) ?
            zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
    addReplyUlong(c,len);
}

#define REDIS_GETALL_KEYS 1
#define REDIS_GETALL_VALS 2
static void genericHgetallCommand(redisClient *c, int flags) {
    robj *o, *lenobj;
    unsigned long count = 0;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
        || checkType(c,o,REDIS_HASH)) return;
