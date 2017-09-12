#include "redis.h"

#include <signal.h>

/*-----------------------------------------------------------------------------
 * C-level DB API
 *----------------------------------------------------------------------------*/

robj *lookupKey(redisDb *db, robj *key) {
    dictEntry *de = dictFind(db->dict,key->ptr);
    if (de) {
        robj *val = dictGetEntryVal(de);

        if (server.vm_enabled) {
            if (val->storage == REDIS_VM_MEMORY ||
                val->storage == REDIS_VM_SWAPPING)
            {
                /* If we were swapping the object out, cancel the operation */
                if (val->storage == REDIS_VM_SWAPPING)
                    vmCancelThreadedIOJob(val);
                /* Update the access time for the aging algorithm. */
                val->lru = server.lruclock;
            } else {
                int notify = (val->storage == REDIS_VM_LOADING);

                /* Our value was swapped on disk. Bring it at home. */
                redisAssert(val->type == REDIS_VMPOINTER);
                val = vmLoadObject(val);
                dictGetEntryVal(de) = val;

                /* Clients blocked by the VM subsystem may be waiting for
                 * this key... */
                if (notify) handleClientsBlockedOnSwappedKey(db,key);
            }
        }
        return val;
    } else {
        return NULL;
    }
}

robj *lookupKeyRead(redisDb *db, robj *key) {
    expireIfNeeded(db,key);
    return lookupKey(db,key);
}

robj *lookupKeyWrite(redisDb *db, robj *key) {
    deleteIfVolatile(db,key);
    touchWatchedKey(db,key);
    return lookupKey(db,key);
}

robj *lookupKeyReadOrReply(redisClient *c, robj *key, robj *reply) {
    robj *o = lookupKeyRead(c->db, key);
    if (!o) addReply(c,reply);
    return o;
}

robj *lookupKeyWriteOrReply(redisClient *c, robj *key, robj *reply) {
    robj *o = lookupKeyWrite(c->db, key);
    if (!o) addReply(c,reply);
    return o;
}

/* Add the key to the DB. If the key already exists REDIS_ERR is returned,
 * otherwise REDIS_OK is returned, and the caller should increment the
 * refcount of 'val'. */
int dbAdd(redisDb *db, robj *key, robj *val) {
    /* Perform a lookup before adding the key, as we need to copy the
     * key value. */
    if (dictFind(db->dict, key->ptr) != NULL) {
        return REDIS_ERR;
    } else {
        sds copy = sdsdup(key->ptr);
        dictAdd(db->dict, copy, val);
        return REDIS_OK;
    }
}

/* If the key does not exist, this is just like dbAdd(). Otherwise
 * the value associated to the key is replaced with the new one.
 *
 * On update (key already existed) 0 is returned. Otherwise 1. */
int dbReplace(redisDb *db, robj *key, robj *val) {
    if (dictFind(db->dict,key->ptr) == NULL) {
        sds copy = sdsdup(key->ptr);
        dictAdd(db->dict, copy, val);
        return 1;
    } else {
        dictReplace(db->dict, key->ptr, val);
        return 0;
    }
}

int dbExists(redisDb *db, robj *key) {
    return dictFind(db->dict,key->ptr) != NULL;
}

/* Return a random key, in form of a Redis object.
 * If there are no keys, NULL is returned.
 *
 * The function makes sure to return keys not already expired. */
robj *dbRandomKey(redisDb *db) {
    struct dictEntry *de;

    while(1) {
        sds key;
        robj *keyobj;

        de = dictGetRandomKey(db->dict);
        if (de == NULL) return NULL;

        key = dictGetEntryKey(de);
        keyobj = createStringObject(key,sdslen(key));
        if (dictFind(db->expires,key)) {
            if (expireIfNeeded(db,keyobj)) {
                decrRefCount(keyobj);
                continue; /* search for another key. This expired. */
            }
        }
        return keyobj;
    }
}

/* Delete a key, value, and associated expiration entry if any, from the DB */
int dbDelete(redisDb *db, robj *key) {
    /* Deleting an entry from the expires dict will not free the sds of
     * the key, because it is shared with the main dictionary. */
    if (dictSize(db->expires) > 0) dictDelete(db->expires,key->ptr);
    return dictDelete(db->dict,key->ptr) == DICT_OK;
}

/* Empty the whole database */
long long emptyDb() {
    int j;
    long long removed = 0;

    for (j = 0; j < server.dbnum; j++) {
        removed += dictSize(server.db[j].dict);
        dictEmpty(server.db[j].dict);
        dictEmpty(server.db[j].expires);
    }
    return removed;
}

int selectDb(redisClient *c, int id) {
    if (id < 0 || id >= server.dbnum)
        return REDIS_ERR;
    c->db = &server.db[id];
    return REDIS_OK;
}

/*-----------------------------------------------------------------------------
 * Type agnostic commands operating on the key space
 *----------------------------------------------------------------------------*/

void flushdbCommand(redisClient *c) {
    server.dirty += dictSize(c->db->dict);
    touchWatchedKeysOnFlush(c->db->id);
    dictEmpty(c->db->dict);
    dictEmpty(c->db->expires);
    addReply(c,shared.ok);
}

void flushallCommand(redisClient *c) {
    touchWatchedKeysOnFlush(-1);
    server.dirty += emptyDb();
    addReply(c,shared.ok);
    if (server.bgsavechildpid != -1) {
        kill(server.bgsavechildpid,SIGKILL);
        rdbRemoveTempFile(server.bgsavechildpid);
    }
    rdbSave(server.dbfilename);
    server.dirty++;
}

void delCommand(redisClient *c) {
    int deleted = 0, j;

    for (j = 1; j < c->argc; j++) {
        if (dbDelete(c->db,c->argv[j])) {
            touchWatchedKey(c->db,c->argv[j]);
            server.dirty++;
            deleted++;
        }
    }
    addReplyLongLong(c,deleted);
}

void existsCommand(redisClient *c) {
    expireIfNeeded(c->db,c->argv[1]);
    if (dbExists(c->db,c->argv[1])) {
        addReply(c, shared.cone);
    } else {
        addReply(c, shared.czero);
    }
}

void selectCommand(redisClient *c) {
    int id = atoi(c->argv[1]->ptr);

    if (selectDb(c,id) == REDIS_ERR) {
        addReplySds(c,sdsnew("-ERR invalid DB index\r\n"));
    } else {
        addReply(c,shared.ok);
    }
}

void randomkeyCommand(redisClient *c) {
    robj *key;

    if ((key = dbRandomKey(c->db)) == NULL) {
        addReply(c,shared.nullbulk);
        return;
    }

    addReplyBulk(c,key);
    decrRefCount(key);
}

void keysCommand(redisClient *c) {
    dictIterator *di;
    dictEntry *de;
    sds pattern = c->argv[1]->ptr;
    int plen = sdslen(pattern);
    unsigned long numkeys = 0;
    robj *lenobj = createObject(REDIS_STRING,NULL);

    di = dictGetIterator(c->db->dict);
    addReply(c,lenobj);
    decrRefCount(lenobj);
    while((de = dictNext(di)) != NULL) {
        sds key = dictGetEntryKey(de);
        robj *keyobj;

        if ((pattern[0] == '*' && pattern[1] == '\0') ||
            stringmatchlen(pattern,plen,key,sdslen(key),0)) {
            keyobj = createStringObject(key,sdslen(key));
            if (expireIfNeeded(c->db,keyobj) == 0) {
                addReplyBulk(c,keyobj);
                numkeys++;
            }
            decrRefCount(keyobj);
        }
    }
    dictReleaseIterator(di);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
}

void dbsizeCommand(redisClient *c) {
    addReplySds(c,
        sdscatprintf(sdsempty(),":%lu\r\n",dictSize(c->db->dict)));
}

void lastsaveCommand(redisClient *c) {
    addReplySds(c,
        sdscatprintf(sdsempty(),":%lu\r\n",server.lastsave));
}

void typeCommand(redisClient *c) {
    robj *o;
    char *type;

    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        type = "+none";
    } else {
        switch(o->type) {
        case REDIS_STRING: type = "+string"; break;
        case REDIS_LIST: type = "+list"; break;
        case REDIS_SET: type = "+set"; break;
        case REDIS_ZSET: type = "+zset"; break;
        case REDIS_HASH: type = "+hash"; break;
        default: type = "+unknown"; break;
        }
    }
    addReplySds(c,sdsnew(type));
    addReply(c,shared.crlf);
}

void saveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1) {
        addReplySds(c,sdsnew("-ERR background save in progress\r\n"));
        return;
    }
    if (rdbSave(server.dbfilename) == REDIS_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
    }
}

void bgsaveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1) {
        addReplySds(c,sdsnew("-ERR background save already in progress\r\n"));
        return;
    }
    if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
        char *status = "+Background saving started\r\n";
        addReplySds(c,sdsnew(status));
    } else {
        addReply(c,shared.err);
    }
}

void shutdownCommand(redisClient *c) {
    if (prepareForShutdown() == REDIS_OK)
        exit(0);
    addReplySds(c, sdsnew("-ERR Errors trying to SHUTDOWN. Check logs.\r\n"));
}

void renameGenericCommand(redisClient *c, int nx) {
    robj *o;

    /* To use the same key as src and dst is probably an error */
    if (sdscmp(c->argv[1]->ptr,c->argv[2]->ptr) == 0) {
        addReply(c,shared.sameobjecterr);
        return;
    }

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL)
        return;

    incrRefCount(o);
    deleteIfVolatile(c->db,c->argv[2]);
    if (dbAdd(c->db,c->argv[2],o) == REDIS_ERR) {
        if (nx) {
            decrRefCount(o);
            addReply(c,shared.czero);
            return;
        }
        dbReplace(c->db,c->argv[2],o);
    }
    dbDelete(c->db,c->argv[1]);
