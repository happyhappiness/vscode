/* Redis Object implementation.
 *
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "server.h"
#include <math.h>
#include <ctype.h>

#ifdef __CYGWIN__
#define strtold(a,b) ((long double)strtod((a),(b)))
#endif

/* ===================== Creation and parsing of objects ==================== */

robj *createObject(int type, void *ptr) {
    robj *o = zmalloc(sizeof(*o));
    o->type = type;
    o->encoding = OBJ_ENCODING_RAW;
    o->ptr = ptr;
    o->refcount = 1;

    /* Set the LRU to the current lruclock (minutes resolution), or
     * alternatively the LFU counter. */
    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
        o->lru = (LFUGetTimeInMinutes()<<8) | LFU_INIT_VAL;
    } else {
        o->lru = LRU_CLOCK();
    }
    return o;
}

/* Set a special refcount in the object to make it "shared":
 * incrRefCount and decrRefCount() will test for this special refcount
 * and will not touch the object. This way it is free to access shared
 * objects such as small integers from different threads without any
 * mutex.
 *
 * A common patter to create shared objects:
 *
 * robj *myobject = makeObjectShared(createObject(...));
 *
 */
robj *makeObjectShared(robj *o) {
    serverAssert(o->refcount == 1);
    o->refcount = OBJ_SHARED_REFCOUNT;
    return o;
}

/* Create a string object with encoding OBJ_ENCODING_RAW, that is a plain
 * string object where o->ptr points to a proper sds string. */
robj *createRawStringObject(const char *ptr, size_t len) {
    return createObject(OBJ_STRING,sdsnewlen(ptr,len));
}

/* Create a string object with encoding OBJ_ENCODING_EMBSTR, that is
 * an object where the sds string is actually an unmodifiable string
 * allocated in the same chunk as the object itself. */
robj *createEmbeddedStringObject(const char *ptr, size_t len) {
    robj *o = zmalloc(sizeof(robj)+sizeof(struct sdshdr8)+len+1);
    struct sdshdr8 *sh = (void*)(o+1);

    o->type = OBJ_STRING;
    o->encoding = OBJ_ENCODING_EMBSTR;
    o->ptr = sh+1;
    o->refcount = 1;
    if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
        o->lru = (LFUGetTimeInMinutes()<<8) | LFU_INIT_VAL;
    } else {
        o->lru = LRU_CLOCK();
    }

    sh->len = len;
    sh->alloc = len;
    sh->flags = SDS_TYPE_8;
    if (ptr) {
        memcpy(sh->buf,ptr,len);
        sh->buf[len] = '\0';
    } else {
        memset(sh->buf,0,len+1);
    }
    return o;
}

/* Create a string object with EMBSTR encoding if it is smaller than
 * OBJ_ENCODING_EMBSTR_SIZE_LIMIT, otherwise the RAW encoding is
 * used.
 *
 * The current limit of 39 is chosen so that the biggest string object
 * we allocate as EMBSTR will still fit into the 64 byte arena of jemalloc. */
#define OBJ_ENCODING_EMBSTR_SIZE_LIMIT 44
robj *createStringObject(const char *ptr, size_t len) {
    if (len <= OBJ_ENCODING_EMBSTR_SIZE_LIMIT)
        return createEmbeddedStringObject(ptr,len);
    else
        return createRawStringObject(ptr,len);
}

robj *createStringObjectFromLongLong(long long value) {
    robj *o;
    if (value >= 0 && value < OBJ_SHARED_INTEGERS) {
        incrRefCount(shared.integers[value]);
        o = shared.integers[value];
    } else {
        if (value >= LONG_MIN && value <= LONG_MAX) {
            o = createObject(OBJ_STRING, NULL);
            o->encoding = OBJ_ENCODING_INT;
            o->ptr = (void*)((long)value);
        } else {
            o = createObject(OBJ_STRING,sdsfromlonglong(value));
        }
    }
    return o;
}

/* Create a string object from a long double. If humanfriendly is non-zero
 * it does not use exponential format and trims trailing zeroes at the end,
 * however this results in loss of precision. Otherwise exp format is used
 * and the output of snprintf() is not modified.
 *
 * The 'humanfriendly' option is used for INCRBYFLOAT and HINCRBYFLOAT. */
robj *createStringObjectFromLongDouble(long double value, int humanfriendly) {
    char buf[256];
    int len = ld2string(buf,sizeof(buf),value,humanfriendly);
    return createStringObject(buf,len);
}

/* Duplicate a string object, with the guarantee that the returned object
 * has the same encoding as the original one.
 *
 * This function also guarantees that duplicating a small integere object
 * (or a string object that contains a representation of a small integer)
 * will always result in a fresh object that is unshared (refcount == 1).
 *
 * The resulting object always has refcount set to 1. */
robj *dupStringObject(const robj *o) {
    robj *d;

    serverAssert(o->type == OBJ_STRING);

    switch(o->encoding) {
    case OBJ_ENCODING_RAW:
        return createRawStringObject(o->ptr,sdslen(o->ptr));
    case OBJ_ENCODING_EMBSTR:
        return createEmbeddedStringObject(o->ptr,sdslen(o->ptr));
    case OBJ_ENCODING_INT:
        d = createObject(OBJ_STRING, NULL);
        d->encoding = OBJ_ENCODING_INT;
        d->ptr = o->ptr;
        return d;
    default:
        serverPanic("Wrong encoding.");
        break;
    }
}

robj *createQuicklistObject(void) {
    quicklist *l = quicklistCreate();
    robj *o = createObject(OBJ_LIST,l);
    o->encoding = OBJ_ENCODING_QUICKLIST;
    return o;
}

robj *createZiplistObject(void) {
    unsigned char *zl = ziplistNew();
    robj *o = createObject(OBJ_LIST,zl);
    o->encoding = OBJ_ENCODING_ZIPLIST;
    return o;
}

robj *createSetObject(void) {
    dict *d = dictCreate(&setDictType,NULL);
    robj *o = createObject(OBJ_SET,d);
    o->encoding = OBJ_ENCODING_HT;
    return o;
}

robj *createIntsetObject(void) {
    intset *is = intsetNew();
    robj *o = createObject(OBJ_SET,is);
    o->encoding = OBJ_ENCODING_INTSET;
    return o;
}

robj *createHashObject(void) {
    unsigned char *zl = ziplistNew();
    robj *o = createObject(OBJ_HASH, zl);
    o->encoding = OBJ_ENCODING_ZIPLIST;
    return o;
}

robj *createZsetObject(void) {
    zset *zs = zmalloc(sizeof(*zs));
    robj *o;

    zs->dict = dictCreate(&zsetDictType,NULL);
    zs->zsl = zslCreate();
    o = createObject(OBJ_ZSET,zs);
    o->encoding = OBJ_ENCODING_SKIPLIST;
    return o;
}

robj *createZsetZiplistObject(void) {
    unsigned char *zl = ziplistNew();
    robj *o = createObject(OBJ_ZSET,zl);
    o->encoding = OBJ_ENCODING_ZIPLIST;
    return o;
}

robj *createModuleObject(moduleType *mt, void *value) {
    moduleValue *mv = zmalloc(sizeof(*mv));
    mv->type = mt;
    mv->value = value;
    return createObject(OBJ_MODULE,mv);
}

void freeStringObject(robj *o) {
    if (o->encoding == OBJ_ENCODING_RAW) {
        sdsfree(o->ptr);
    }
}

void freeListObject(robj *o) {
    switch (o->encoding) {
    case OBJ_ENCODING_QUICKLIST:
        quicklistRelease(o->ptr);
        break;
    default:
        serverPanic("Unknown list encoding type");
    }
}

void freeSetObject(robj *o) {
    switch (o->encoding) {
    case OBJ_ENCODING_HT:
        dictRelease((dict*) o->ptr);
        break;
    case OBJ_ENCODING_INTSET:
        zfree(o->ptr);
        break;
    default:
        serverPanic("Unknown set encoding type");
    }
}

void freeZsetObject(robj *o) {
    zset *zs;
    switch (o->encoding) {
    case OBJ_ENCODING_SKIPLIST:
        zs = o->ptr;
        dictRelease(zs->dict);
        zslFree(zs->zsl);
        zfree(zs);
        break;
    case OBJ_ENCODING_ZIPLIST:
        zfree(o->ptr);
        break;
    default:
        serverPanic("Unknown sorted set encoding");
    }
}

void freeHashObject(robj *o) {
    switch (o->encoding) {
    case OBJ_ENCODING_HT:
        dictRelease((dict*) o->ptr);
        break;
    case OBJ_ENCODING_ZIPLIST:
        zfree(o->ptr);
        break;
    default:
        serverPanic("Unknown hash encoding type");
        break;
    }
}

void freeModuleObject(robj *o) {
    moduleValue *mv = o->ptr;
    mv->type->free(mv->value);
    zfree(mv);
}

void incrRefCount(robj *o) {
    if (o->refcount != OBJ_SHARED_REFCOUNT) o->refcount++;
}

void decrRefCount(robj *o) {
    if (o->refcount == 1) {
        switch(o->type) {
        case OBJ_STRING: freeStringObject(o); break;
        case OBJ_LIST: freeListObject(o); break;
        case OBJ_SET: freeSetObject(o); break;
        case OBJ_ZSET: freeZsetObject(o); break;
        case OBJ_HASH: freeHashObject(o); break;
        case OBJ_MODULE: freeModuleObject(o); break;
        default: serverPanic("Unknown object type"); break;
        }
        zfree(o);
    } else {
        if (o->refcount <= 0) serverPanic("decrRefCount against refcount <= 0");
        if (o->refcount != OBJ_SHARED_REFCOUNT) o->refcount--;
    }
}

/* This variant of decrRefCount() gets its argument as void, and is useful
 * as free method in data structures that expect a 'void free_object(void*)'
 * prototype for the free method. */
void decrRefCountVoid(void *o) {
    decrRefCount(o);
}

/* This function set the ref count to zero without freeing the object.
 * It is useful in order to pass a new object to functions incrementing
 * the ref count of the received object. Example:
 *
 *    functionThatWillIncrementRefCount(resetRefCount(CreateObject(...)));
 *
 * Otherwise you need to resort to the less elegant pattern:
 *
 *    *obj = createObject(...);
 *    functionThatWillIncrementRefCount(obj);
 *    decrRefCount(obj);
 */
robj *resetRefCount(robj *obj) {
    obj->refcount = 0;
    return obj;
}

int checkType(client *c, robj *o, int type) {
    if (o->type != type) {
        addReply(c,shared.wrongtypeerr);
        return 1;
    }
    return 0;
}

int isSdsRepresentableAsLongLong(sds s, long long *llval) {
    return string2ll(s,sdslen(s),llval) ? C_OK : C_ERR;
}

int isObjectRepresentableAsLongLong(robj *o, long long *llval) {
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
    if (o->encoding == OBJ_ENCODING_INT) {
        if (llval) *llval = (long) o->ptr;
        return C_OK;
    } else {
        return isSdsRepresentableAsLongLong(o->ptr,llval);
    }
}

/* Try to encode a string object in order to save space */
robj *tryObjectEncoding(robj *o) {
    long value;
    sds s = o->ptr;
    size_t len;

    /* Make sure this is a string object, the only type we encode
     * in this function. Other types use encoded memory efficient
     * representations but are handled by the commands implementing
     * the type. */
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);

    /* We try some specialized encoding only for objects that are
     * RAW or EMBSTR encoded, in other words objects that are still
     * in represented by an actually array of chars. */
    if (!sdsEncodedObject(o)) return o;

    /* It's not safe to encode shared objects: shared objects can be shared
     * everywhere in the "object space" of Redis and may end in places where
     * they are not handled. We handle them only as values in the keyspace. */
     if (o->refcount > 1) return o;

    /* Check if we can represent this string as a long integer.
     * Note that we are sure that a string larger than 20 chars is not
     * representable as a 32 nor 64 bit integer. */
    len = sdslen(s);
    if (len <= 20 && string2l(s,len,&value)) {
        /* This object is encodable as a long. Try to use a shared object.
         * Note that we avoid using shared integers when maxmemory is used
         * because every object needs to have a private LRU field for the LRU
         * algorithm to work well. */
        if ((server.maxmemory == 0 ||
            !(server.maxmemory_policy & MAXMEMORY_FLAG_NO_SHARED_INTEGERS)) &&
            value >= 0 &&
            value < OBJ_SHARED_INTEGERS)
        {
            decrRefCount(o);
            incrRefCount(shared.integers[value]);
            return shared.integers[value];
        } else {
            if (o->encoding == OBJ_ENCODING_RAW) sdsfree(o->ptr);
            o->encoding = OBJ_ENCODING_INT;
            o->ptr = (void*) value;
            return o;
        }
    }

    /* If the string is small and is still RAW encoded,
     * try the EMBSTR encoding which is more efficient.
     * In this representation the object and the SDS string are allocated
     * in the same chunk of memory to save space and cache misses. */
    if (len <= OBJ_ENCODING_EMBSTR_SIZE_LIMIT) {
        robj *emb;

        if (o->encoding == OBJ_ENCODING_EMBSTR) return o;
        emb = createEmbeddedStringObject(s,sdslen(s));
        decrRefCount(o);
        return emb;
    }

    /* We can't encode the object...
     *
     * Do the last try, and at least optimize the SDS string inside
     * the string object to require little space, in case there
     * is more than 10% of free space at the end of the SDS string.
     *
     * We do that only for relatively large strings as this branch
     * is only entered if the length of the string is greater than
     * OBJ_ENCODING_EMBSTR_SIZE_LIMIT. */
    if (o->encoding == OBJ_ENCODING_RAW &&
        sdsavail(s) > len/10)
    {
        o->ptr = sdsRemoveFreeSpace(o->ptr);
    }

    /* Return the original object. */
    return o;
}

/* Get a decoded version of an encoded object (returned as a new object).
 * If the object is already raw-encoded just increment the ref count. */
robj *getDecodedObject(robj *o) {
    robj *dec;

    if (sdsEncodedObject(o)) {
        incrRefCount(o);
        return o;
    }
    if (o->type == OBJ_STRING && o->encoding == OBJ_ENCODING_INT) {
        char buf[32];

        ll2string(buf,32,(long)o->ptr);
        dec = createStringObject(buf,strlen(buf));
        return dec;
    } else {
        serverPanic("Unknown encoding type");
    }
}

/* Compare two string objects via strcmp() or strcoll() depending on flags.
 * Note that the objects may be integer-encoded. In such a case we
 * use ll2string() to get a string representation of the numbers on the stack
 * and compare the strings, it's much faster than calling getDecodedObject().
 *
 * Important note: when REDIS_COMPARE_BINARY is used a binary-safe comparison
 * is used. */

#define REDIS_COMPARE_BINARY (1<<0)
#define REDIS_COMPARE_COLL (1<<1)

int compareStringObjectsWithFlags(robj *a, robj *b, int flags) {
    serverAssertWithInfo(NULL,a,a->type == OBJ_STRING && b->type == OBJ_STRING);
    char bufa[128], bufb[128], *astr, *bstr;
    size_t alen, blen, minlen;

    if (a == b) return 0;
    if (sdsEncodedObject(a)) {
        astr = a->ptr;
        alen = sdslen(astr);
    } else {
        alen = ll2string(bufa,sizeof(bufa),(long) a->ptr);
        astr = bufa;
    }
    if (sdsEncodedObject(b)) {
        bstr = b->ptr;
        blen = sdslen(bstr);
    } else {
        blen = ll2string(bufb,sizeof(bufb),(long) b->ptr);
        bstr = bufb;
    }
    if (flags & REDIS_COMPARE_COLL) {
        return strcoll(astr,bstr);
    } else {
        int cmp;

        minlen = (alen < blen) ? alen : blen;
        cmp = memcmp(astr,bstr,minlen);
        if (cmp == 0) return alen-blen;
        return cmp;
    }
}

/* Wrapper for compareStringObjectsWithFlags() using binary comparison. */
int compareStringObjects(robj *a, robj *b) {
    return compareStringObjectsWithFlags(a,b,REDIS_COMPARE_BINARY);
}

/* Wrapper for compareStringObjectsWithFlags() using collation. */
int collateStringObjects(robj *a, robj *b) {
    return compareStringObjectsWithFlags(a,b,REDIS_COMPARE_COLL);
}

/* Equal string objects return 1 if the two objects are the same from the
 * point of view of a string comparison, otherwise 0 is returned. Note that
 * this function is faster then checking for (compareStringObject(a,b) == 0)
 * because it can perform some more optimization. */
int equalStringObjects(robj *a, robj *b) {
    if (a->encoding == OBJ_ENCODING_INT &&
        b->encoding == OBJ_ENCODING_INT){
        /* If both strings are integer encoded just check if the stored
         * long is the same. */
        return a->ptr == b->ptr;
    } else {
        return compareStringObjects(a,b) == 0;
    }
}

size_t stringObjectLen(robj *o) {
    serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
    if (sdsEncodedObject(o)) {
        return sdslen(o->ptr);
    } else {
        return sdigits10((long)o->ptr);
    }
}

int getDoubleFromObject(const robj *o, double *target) {
    double value;
    char *eptr;

    if (o == NULL) {
        value = 0;
    } else {
        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
        if (sdsEncodedObject(o)) {
            errno = 0;
            value = strtod(o->ptr, &eptr);
            if (isspace(((const char*)o->ptr)[0]) ||
                eptr[0] != '\0' ||
                (errno == ERANGE &&
                    (value == HUGE_VAL || value == -HUGE_VAL || value == 0)) ||
                errno == EINVAL ||
                isnan(value))
                return C_ERR;
        } else if (o->encoding == OBJ_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            serverPanic("Unknown string encoding");
        }
    }
    *target = value;
    return C_OK;
}

int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg) {
    double value;
    if (getDoubleFromObject(o, &value) != C_OK) {
        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not a valid float");
        }
        return C_ERR;
    }
    *target = value;
    return C_OK;
}

int getLongDoubleFromObject(robj *o, long double *target) {
    long double value;
    char *eptr;

    if (o == NULL) {
        value = 0;
    } else {
        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
        if (sdsEncodedObject(o)) {
            errno = 0;
            value = strtold(o->ptr, &eptr);
            if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' ||
                errno == ERANGE || isnan(value))
                return C_ERR;
        } else if (o->encoding == OBJ_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            serverPanic("Unknown string encoding");
        }
    }
    *target = value;
    return C_OK;
}

int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg) {
    long double value;
    if (getLongDoubleFromObject(o, &value) != C_OK) {
        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not a valid float");
        }
        return C_ERR;
    }
    *target = value;
    return C_OK;
}

int getLongLongFromObject(robj *o, long long *target) {
    long long value;

    if (o == NULL) {
        value = 0;
    } else {
        serverAssertWithInfo(NULL,o,o->type == OBJ_STRING);
        if (sdsEncodedObject(o)) {
            if (string2ll(o->ptr,sdslen(o->ptr),&value) == 0) return C_ERR;
        } else if (o->encoding == OBJ_ENCODING_INT) {
            value = (long)o->ptr;
        } else {
            serverPanic("Unknown string encoding");
        }
    }
    if (target) *target = value;
    return C_OK;
}

int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg) {
    long long value;
    if (getLongLongFromObject(o, &value) != C_OK) {
        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is not an integer or out of range");
        }
        return C_ERR;
    }
    *target = value;
    return C_OK;
}

int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg) {
    long long value;

    if (getLongLongFromObjectOrReply(c, o, &value, msg) != C_OK) return C_ERR;
    if (value < LONG_MIN || value > LONG_MAX) {
        if (msg != NULL) {
            addReplyError(c,(char*)msg);
        } else {
            addReplyError(c,"value is out of range");
        }
        return C_ERR;
    }
    *target = value;
    return C_OK;
}

char *strEncoding(int encoding) {
    switch(encoding) {
    case OBJ_ENCODING_RAW: return "raw";
    case OBJ_ENCODING_INT: return "int";
    case OBJ_ENCODING_HT: return "hashtable";
    case OBJ_ENCODING_QUICKLIST: return "quicklist";
    case OBJ_ENCODING_ZIPLIST: return "ziplist";
    case OBJ_ENCODING_INTSET: return "intset";
    case OBJ_ENCODING_SKIPLIST: return "skiplist";
    case OBJ_ENCODING_EMBSTR: return "embstr";
    default: return "unknown";
    }
}

/* ========================== Objects introspection ========================= */

/* Returns the size in bytes consumed by the key's value in RAM.
 * Note that the returned value is just an approximation, especially in the
 * case of aggregated data types where only "sample_size" elements
 * are checked and averaged to estimate the total size. */
#define OBJ_COMPUTE_SIZE_DEF_SAMPLES 5 /* Default sample size. */
size_t objectComputeSize(robj *o, size_t sample_size) {
    sds ele, ele2;
    dict *d;
    dictIterator *di;
    struct dictEntry *de;
    size_t asize = 0, elesize = 0, samples = 0;

    if (o->type == OBJ_STRING) {
        if(o->encoding == OBJ_ENCODING_INT) {
            asize = sizeof(*o);
        } else if(o->encoding == OBJ_ENCODING_RAW) {
            asize = sdsAllocSize(o->ptr)+sizeof(*o);
        } else if(o->encoding == OBJ_ENCODING_EMBSTR) {
            asize = sdslen(o->ptr)+2+sizeof(*o);
        } else {
            serverPanic("Unknown string encoding");
        }
    } else if (o->type == OBJ_LIST) {
        if (o->encoding == OBJ_ENCODING_QUICKLIST) {
            quicklist *ql = o->ptr;
            quicklistNode *node = ql->head;
            asize = sizeof(*o)+sizeof(quicklist);
            do {
                elesize += sizeof(quicklistNode)+ziplistBlobLen(node->zl);
                samples++;
            } while ((node = node->next) && samples < sample_size);
            asize += (double)elesize/samples*listTypeLength(o);
        } else if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+ziplistBlobLen(o->ptr);
        } else {
            serverPanic("Unknown list encoding");
        }
    } else if (o->type == OBJ_SET) {
        if (o->encoding == OBJ_ENCODING_HT) {
            d = o->ptr;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL && samples < sample_size) {
                ele = dictGetKey(de);
                elesize += sizeof(struct dictEntry) + sdsAllocSize(ele);
                samples++;
            }
            dictReleaseIterator(di);
            if (samples) asize += (double)elesize/samples*dictSize(d);
        } else if (o->encoding == OBJ_ENCODING_INTSET) {
            intset *is = o->ptr;
            asize = sizeof(*o)+sizeof(*is)+is->encoding*is->length;
        } else {
            serverPanic("Unknown set encoding");
        }
    } else if (o->type == OBJ_ZSET) {
        if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+(ziplistBlobLen(o->ptr));
        } else if (o->encoding == OBJ_ENCODING_SKIPLIST) {
            d = ((zset*)o->ptr)->dict;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(zset)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL && samples < sample_size) {
                ele = dictGetKey(de);
                elesize += sdsAllocSize(ele);
                elesize += sizeof(struct dictEntry) + sizeof(zskiplistNode);
                samples++;
            }
            dictReleaseIterator(di);
            if (samples) asize += (double)elesize/samples*dictSize(d);
        } else {
            serverPanic("Unknown sorted set encoding");
        }
    } else if (o->type == OBJ_HASH) {
        if (o->encoding == OBJ_ENCODING_ZIPLIST) {
            asize = sizeof(*o)+(ziplistBlobLen(o->ptr));
        } else if (o->encoding == OBJ_ENCODING_HT) {
            d = o->ptr;
            di = dictGetIterator(d);
            asize = sizeof(*o)+sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
            while((de = dictNext(di)) != NULL && samples < sample_size) {
                ele = dictGetKey(de);
                ele2 = dictGetVal(de);
                elesize += sdsAllocSize(ele) + sdsAllocSize(ele2);
                elesize += sizeof(struct dictEntry);
                samples++;
            }
            dictReleaseIterator(di);
            if (samples) asize += (double)elesize/samples*dictSize(d);
        } else {
            serverPanic("Unknown hash encoding");
        }
    } else {
        serverPanic("Unknown object type");
    }
    return asize;
}

/* ======================= The OBJECT and MEMORY commands =================== */

/* This is a helper function for the OBJECT command. We need to lookup keys
 * without any modification of LRU or other parameters. */
robj *objectCommandLookup(client *c, robj *key) {
    dictEntry *de;

    if ((de = dictFind(c->db->dict,key->ptr)) == NULL) return NULL;
    return (robj*) dictGetVal(de);
}

robj *objectCommandLookupOrReply(client *c, robj *key, robj *reply) {
    robj *o = objectCommandLookup(c,key);

    if (!o) addReply(c, reply);
    return o;
}

/* Object command allows to inspect the internals of an Redis Object.
 * Usage: OBJECT <refcount|encoding|idletime> <key> */
void objectCommand(client *c) {
    robj *o;

    if (!strcasecmp(c->argv[1]->ptr,"refcount") && c->argc == 3) {
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        addReplyLongLong(c,o->refcount);
    } else if (!strcasecmp(c->argv[1]->ptr,"encoding") && c->argc == 3) {
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        addReplyBulkCString(c,strEncoding(o->encoding));
    } else if (!strcasecmp(c->argv[1]->ptr,"idletime") && c->argc == 3) {
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        if (server.maxmemory_policy & MAXMEMORY_FLAG_LFU) {
            addReplyError(c,"An LFU maxmemory policy is selected, idle time not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
            return;
        }
        addReplyLongLong(c,estimateObjectIdleTime(o)/1000);
    } else if (!strcasecmp(c->argv[1]->ptr,"freq") && c->argc == 3) {
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        if (server.maxmemory_policy & MAXMEMORY_FLAG_LRU) {
            addReplyError(c,"An LRU maxmemory policy is selected, access frequency not tracked. Please note that when switching between policies at runtime LRU and LFU data will take some time to adjust.");
            return;
        }
        addReplyLongLong(c,o->lru&255);
    } else {
        addReplyError(c,"Syntax error. Try OBJECT (refcount|encoding|idletime|freq)");
    }
}

/* Release data obtained with getMemoryOverheadData(). */
void freeMemoryOverheadData(struct redisMemOverhead *mh) {
    zfree(mh->db);
    zfree(mh);
}

/* Return a struct redisMemOverhead filled with memory overhead
 * information used for the MEMORY OVERHEAD and INFO command. The returned
 * structure pointer should be freed calling freeMemoryOverheadData(). */
struct redisMemOverhead *getMemoryOverheadData(void) {
    int j;
    size_t mem_total = 0;
    size_t mem = 0;
    size_t zmalloc_used = zmalloc_used_memory();
    struct redisMemOverhead *mh = zcalloc(sizeof(*mh));

    mh->total_allocated = zmalloc_used;
    mh->startup_allocated = server.initial_memory_usage;
    mem_total += server.initial_memory_usage;

    mem = 0;
    if (server.repl_backlog)
        mem += zmalloc_size(server.repl_backlog);
    mh->repl_backlog = mem;
    mem_total += mem;

    mem = 0;
    if (listLength(server.slaves)) {
        listIter li;
        listNode *ln;

        listRewind(server.slaves,&li);
        while((ln = listNext(&li))) {
            client *client = listNodeValue(ln);
            mem += getClientOutputBufferMemoryUsage(client);
            mem += sdsAllocSize(client->querybuf);
            mem += sizeof(client);
        }
    }
    mh->clients_slaves = mem;
    mem_total+=mem;

    mem = 0;
    if (listLength(server.clients)) {
        listIter li;
        listNode *ln;

        listRewind(server.clients,&li);
        while((ln = listNext(&li))) {
            client *client = listNodeValue(ln);
            if (client->flags & CLIENT_SLAVE)
                continue;
            mem += getClientOutputBufferMemoryUsage(client);
            mem += sdsAllocSize(client->querybuf);
            mem += sizeof(client);
        }
    }
    mh->clients_normal = mem;
    mem_total+=mem;

    mem = 0;
    if (server.aof_state != AOF_OFF) {
        mem += sdslen(server.aof_buf);
        mem += aofRewriteBufferSize();
    }
    mh->aof_buffer = mem;
    mem_total+=mem;

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
        long long keyscount = dictSize(db->dict);
        if (keyscount==0) continue;

        mh->db = zrealloc(mh->db,sizeof(mh->db[0])*(mh->num_dbs+1));
        mh->db[mh->num_dbs].dbid = j;

        mem = dictSize(db->dict) * sizeof(dictEntry) +
              dictSlots(db->dict) * sizeof(dictEntry*) +
              dictSize(db->dict) * sizeof(robj);
        mh->db[mh->num_dbs].overhead_ht_main = mem;
        mem_total+=mem;

        mem = dictSize(db->expires) * sizeof(dictEntry) +
              dictSlots(db->expires) * sizeof(dictEntry*);
        mh->db[mh->num_dbs].overhead_ht_expires = mem;
        mem_total+=mem;

        mh->num_dbs++;
    }

    mh->overhead_total = mem_total;
    mh->dataset = zmalloc_used - mem_total;
    return mh;
}

/* The memory command will eventually be a complete interface for the
 * memory introspection capabilities of Redis.
 *
 * Usage: MEMORY usage <key> */
void memoryCommand(client *c) {
    robj *o;

    if (!strcasecmp(c->argv[1]->ptr,"usage") && c->argc >= 3) {
        long long samples = OBJ_COMPUTE_SIZE_DEF_SAMPLES;
        for (int j = 3; j < c->argc; j++) {
            if (!strcasecmp(c->argv[j]->ptr,"samples") &&
                j+1 < c->argc)
            {
                if (getLongLongFromObjectOrReply(c,c->argv[j+1],&samples,NULL)
                     == C_ERR) return;
                if (samples < 0) {
                    addReply(c,shared.syntaxerr);
                    return;
                }
                if (samples == 0) samples = LLONG_MAX;;
                j++; /* skip option argument. */
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }
        if ((o = objectCommandLookupOrReply(c,c->argv[2],shared.nullbulk))
                == NULL) return;
        size_t usage = objectComputeSize(o,samples);
        usage += sdsAllocSize(c->argv[1]->ptr);
        usage += sizeof(dictEntry);
        addReplyLongLong(c,usage);
    } else if (!strcasecmp(c->argv[1]->ptr,"overhead") && c->argc == 2) {
        struct redisMemOverhead *mh = getMemoryOverheadData();

        addReplyMultiBulkLen(c,(8+mh->num_dbs)*2);

        addReplyBulkCString(c,"total.allocated");
        addReplyLongLong(c,mh->total_allocated);

        addReplyBulkCString(c,"startup.allocated");
        addReplyLongLong(c,mh->startup_allocated);

        addReplyBulkCString(c,"replication.backlog");
        addReplyLongLong(c,mh->repl_backlog);

        addReplyBulkCString(c,"clients.slaves");
        addReplyLongLong(c,mh->clients_slaves);

        addReplyBulkCString(c,"clients.normal");
        addReplyLongLong(c,mh->clients_normal);

        addReplyBulkCString(c,"aof.buffer");
        addReplyLongLong(c,mh->aof_buffer);

        for (size_t j = 0; j < mh->num_dbs; j++) {
            char dbname[32];
            snprintf(dbname,sizeof(dbname),"db.%zd",mh->db[j].dbid);
            addReplyBulkCString(c,dbname);
            addReplyMultiBulkLen(c,4);

            addReplyBulkCString(c,"overhead.hashtable.main");
            addReplyLongLong(c,mh->db[j].overhead_ht_main);

            addReplyBulkCString(c,"overhead.hashtable.expires");
            addReplyLongLong(c,mh->db[j].overhead_ht_expires);
        }

        addReplyBulkCString(c,"overhead.total");
        addReplyLongLong(c,mh->overhead_total);

        addReplyBulkCString(c,"dataset");
        addReplyLongLong(c,mh->dataset);

        freeMemoryOverheadData(mh);
    } else {
        addReplyError(c,"Syntax error. Try MEMORY [usage <key>] | [overhead]");
    }
}
