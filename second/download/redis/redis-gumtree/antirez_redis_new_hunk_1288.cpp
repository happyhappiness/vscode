                c->argv[j]->type, c->argv[j]->encoding);
            arg = buf;
        }
        serverLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
            j, arg, c->argv[j]->refcount);
    }
}

void serverLogObjectDebugInfo(robj *o) {
    serverLog(REDIS_WARNING,"Object type: %d", o->type);
    serverLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
    serverLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
    if (o->type == REDIS_STRING && sdsEncodedObject(o)) {
        serverLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
        if (sdslen(o->ptr) < 4096) {
            sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));
            serverLog(REDIS_WARNING,"Object raw string content: %s", repr);
            sdsfree(repr);
        }
    } else if (o->type == REDIS_LIST) {
        serverLog(REDIS_WARNING,"List length: %d", (int) listTypeLength(o));
    } else if (o->type == REDIS_SET) {
        serverLog(REDIS_WARNING,"Set size: %d", (int) setTypeSize(o));
    } else if (o->type == REDIS_HASH) {
        serverLog(REDIS_WARNING,"Hash size: %d", (int) hashTypeLength(o));
    } else if (o->type == REDIS_ZSET) {
        serverLog(REDIS_WARNING,"Sorted set size: %d", (int) zsetLength(o));
        if (o->encoding == REDIS_ENCODING_SKIPLIST)
            serverLog(REDIS_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
    }
}

void _redisAssertPrintObject(robj *o) {
    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
    serverLogObjectDebugInfo(o);
}

void _redisAssertWithInfo(redisClient *c, robj *o, char *estr, char *file, int line) {
