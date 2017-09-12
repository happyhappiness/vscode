    zrankGenericCommand(c, 1);
}

/* ========================= Hashes utility functions ======================= */
#define REDIS_HASH_KEY 1
#define REDIS_HASH_VALUE 2

/* Check the length of a number of objects to see if we need to convert a
 * zipmap to a real hash. Note that we only check string encoded objects
 * as their string length can be queried in constant time. */
static void hashTryConversion(robj *subject, robj **argv, int start, int end) {
    int i;
    if (subject->encoding != REDIS_ENCODING_ZIPMAP) return;

    for (i = start; i <= end; i++) {
        if (argv[i]->encoding == REDIS_ENCODING_RAW &&
            sdslen(argv[i]->ptr) > server.hash_max_zipmap_value)
        {
            convertToRealHash(subject);
            return;
        }
    }
}

/* Get the value from a hash identified by key. Returns either a string
 * object or NULL if the value cannot be found. The refcount of the object
 * is always increased by 1 when the value was found. */
static robj *hashGet(robj *o, robj *key) {
    robj *value = NULL;
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        unsigned char *v;
        unsigned int vlen;
        key = getDecodedObject(key);
        if (zipmapGet(o->ptr,key->ptr,sdslen(key->ptr),&v,&vlen)) {
            value = createStringObject((char*)v,vlen);
        }
        decrRefCount(key);
    } else {
        dictEntry *de = dictFind(o->ptr,key);
        if (de != NULL) {
            value = dictGetEntryVal(de);
            incrRefCount(value);
        }
    }
    return value;
}

/* Test if the key exists in the given hash. Returns 1 if the key
 * exists and 0 when it doesn't. */
static int hashExists(robj *o, robj *key) {
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        key = getDecodedObject(key);
        if (zipmapExists(o->ptr,key->ptr,sdslen(key->ptr))) {
            decrRefCount(key);
            return 1;
        }
        decrRefCount(key);
    } else {
        if (dictFind(o->ptr,key) != NULL) {
            return 1;
        }
    }
    return 0;
}

/* Add an element, discard the old if the key already exists.
 * Return 0 on insert and 1 on update. */
static int hashSet(robj *o, robj *key, robj *value) {
    int update = 0;
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        key = getDecodedObject(key);
        value = getDecodedObject(value);
        o->ptr = zipmapSet(o->ptr,
            key->ptr,sdslen(key->ptr),
            value->ptr,sdslen(value->ptr), &update);
        decrRefCount(key);
        decrRefCount(value);

        /* Check if the zipmap needs to be upgraded to a real hash table */
        if (zipmapLen(o->ptr) > server.hash_max_zipmap_entries)
            convertToRealHash(o);
    } else {
        value = tryObjectEncoding(value);
        if (dictReplace(o->ptr,key,value)) {
            /* Insert */
            incrRefCount(key);
        } else {
            /* Update */
            update = 1;
        }
        incrRefCount(value);
    }
    return update;
}

/* Delete an element from a hash.
 * Return 1 on deleted and 0 on not found. */
static int hashDelete(robj *o, robj *key) {
    int deleted = 0;
    if (o->encoding == REDIS_ENCODING_ZIPMAP) {
        key = getDecodedObject(key);
        o->ptr = zipmapDel(o->ptr,key->ptr,sdslen(key->ptr), &deleted);
        decrRefCount(key);
    } else {
        deleted = dictDelete((dict*)o->ptr,key) == DICT_OK;
        /* Always check if the dictionary needs a resize after a delete. */
        if (deleted && htNeedsResize(o->ptr)) dictResize(o->ptr);
    }
    return deleted;
}

/* Return the number of elements in a hash. */
static unsigned long hashLength(robj *o) {
    return (o->encoding == REDIS_ENCODING_ZIPMAP) ?
        zipmapLen((unsigned char*)o->ptr) : dictSize((dict*)o->ptr);
}

/* Structure to hold hash iteration abstration. Note that iteration over
 * hashes involves both fields and values. Because it is possible that
 * not both are required, store pointers in the iterator to avoid
 * unnecessary memory allocation for fields/values. */
typedef struct {
    int encoding;
    unsigned char *zi;
    unsigned char *zk, *zv;
    unsigned int zklen, zvlen;

    dictIterator *di;
    dictEntry *de;
} hashIterator;

static hashIterator *hashInitIterator(robj *subject) {
    hashIterator *hi = zmalloc(sizeof(hashIterator));
    hi->encoding = subject->encoding;
    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
        hi->zi = zipmapRewind(subject->ptr);
    } else if (hi->encoding == REDIS_ENCODING_HT) {
        hi->di = dictGetIterator(subject->ptr);
    } else {
        redisAssert(NULL);
    }
    return hi;
}

static void hashReleaseIterator(hashIterator *hi) {
    if (hi->encoding == REDIS_ENCODING_HT) {
        dictReleaseIterator(hi->di);
    }
    zfree(hi);
}

/* Move to the next entry in the hash. Return REDIS_OK when the next entry
 * could be found and REDIS_ERR when the iterator reaches the end. */
static int hashNext(hashIterator *hi) {
    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
        if ((hi->zi = zipmapNext(hi->zi, &hi->zk, &hi->zklen,
            &hi->zv, &hi->zvlen)) == NULL) return REDIS_ERR;
    } else {
        if ((hi->de = dictNext(hi->di)) == NULL) return REDIS_ERR;
    }
    return REDIS_OK;
}

/* Get key or value object at current iteration position.
 * This increases the refcount of the field object by 1. */
static robj *hashCurrent(hashIterator *hi, int what) {
    robj *o;
    if (hi->encoding == REDIS_ENCODING_ZIPMAP) {
        if (what & REDIS_HASH_KEY) {
            o = createStringObject((char*)hi->zk,hi->zklen);
        } else {
            o = createStringObject((char*)hi->zv,hi->zvlen);
        }
    } else {
        if (what & REDIS_HASH_KEY) {
            o = dictGetEntryKey(hi->de);
        } else {
            o = dictGetEntryVal(hi->de);
        }
        incrRefCount(o);
    }
    return o;
}

static robj *hashLookupWriteOrCreate(redisClient *c, robj *key) {
    robj *o = lookupKeyWrite(c->db,key);
    if (o == NULL) {
        o = createHashObject();
        dictAdd(c->db->dict,key,o);
        incrRefCount(key);
    } else {
        if (o->type != REDIS_HASH) {
            addReply(c,shared.wrongtypeerr);
            return NULL;
        }
    }
    return o;
}

/* ============================= Hash commands ============================== */
static void hsetCommand(redisClient *c) {
    int update;
    robj *o;

    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    hashTryConversion(o,c->argv,2,3);
    update = hashSet(o,c->argv[2],c->argv[3]);
    addReply(c, update ? shared.czero : shared.cone);
    server.dirty++;
}

static void hsetnxCommand(redisClient *c) {
    robj *o;
    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    hashTryConversion(o,c->argv,2,3);

    if (hashExists(o, c->argv[2])) {
        addReply(c, shared.czero);
    } else {
        hashSet(o,c->argv[2],c->argv[3]);
        addReply(c, shared.cone);
        server.dirty++;
    }
}

static void hmsetCommand(redisClient *c) {
    int i;
    robj *o;

    if ((c->argc % 2) == 1) {
        addReplySds(c,sdsnew("-ERR wrong number of arguments for HMSET\r\n"));
        return;
    }

    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    hashTryConversion(o,c->argv,2,c->argc-1);
    for (i = 2; i < c->argc; i += 2) {
        hashSet(o,c->argv[i],c->argv[i+1]);
    }
    addReply(c, shared.ok);
}

static void hincrbyCommand(redisClient *c) {
    long long value, incr;
    robj *o, *current, *new;

    if (getLongLongFromObject(c,c->argv[3],&incr) != REDIS_OK) return;
    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    if ((current = hashGet(o,c->argv[2])) != NULL) {
        if (current->encoding == REDIS_ENCODING_RAW)
            value = strtoll(current->ptr,NULL,10);
        else if (current->encoding == REDIS_ENCODING_INT)
            value = (long)current->ptr;
        else
            redisAssert(1 != 1);
        decrRefCount(current);
    } else {
        value = 0;
    }

    value += incr;
    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    hashSet(o,c->argv[2],new);
    decrRefCount(new);
    addReplyLongLong(c,value);
    server.dirty++;
}

static void hgetCommand(redisClient *c) {
    robj *o, *value;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if ((value = hashGet(o,c->argv[2])) != NULL) {
        addReplyBulk(c,value);
        decrRefCount(value);
    } else {
        addReply(c,shared.nullbulk);
    }
}

static void hmgetCommand(redisClient *c) {
    int i;
    robj *o, *value;
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o != NULL && o->type != REDIS_HASH) {
        addReply(c,shared.wrongtypeerr);
    }

    /* Note the check for o != NULL happens inside the loop. This is
     * done because objects that cannot be found are considered to be
     * an empty hash. The reply should then be a series of NULLs. */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
    for (i = 2; i < c->argc; i++) {
        if (o != NULL && (value = hashGet(o,c->argv[i])) != NULL) {
            addReplyBulk(c,value);
            decrRefCount(value);
        } else {
            addReply(c,shared.nullbulk);
        }
    }
}

static void hdelCommand(redisClient *c) {
    robj *o;
    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    if (hashDelete(o,c->argv[2])) {
        if (hashLength(o) == 0) deleteKey(c->db,c->argv[1]);
        addReply(c,shared.cone);
        server.dirty++;
    } else {
        addReply(c,shared.czero);
    }
}

static void hlenCommand(redisClient *c) {
    robj *o;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    addReplyUlong(c,hashLength(o));
}

static void genericHgetallCommand(redisClient *c, int flags) {
    robj *o, *lenobj, *obj;
    unsigned long count = 0;
    hashIterator *hi;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
        || checkType(c,o,REDIS_HASH)) return;
