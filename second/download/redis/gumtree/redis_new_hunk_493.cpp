                        mixObjectDigest(eledigest,eleobj);
                        mixDigest(eledigest,buf,strlen(buf));
                        xorDigest(digest,eledigest,20);
                    }
                    dictReleaseIterator(di);
                } else {
                    serverPanic("Unknown sorted set encoding");
                }
            } else if (o->type == OBJ_HASH) {
                hashTypeIterator *hi;
                robj *obj;

                hi = hashTypeInitIterator(o);
                while (hashTypeNext(hi) != C_ERR) {
                    unsigned char eledigest[20];

                    memset(eledigest,0,20);
                    obj = hashTypeCurrentObject(hi,OBJ_HASH_KEY);
                    mixObjectDigest(eledigest,obj);
                    decrRefCount(obj);
                    obj = hashTypeCurrentObject(hi,OBJ_HASH_VALUE);
                    mixObjectDigest(eledigest,obj);
                    decrRefCount(obj);
                    xorDigest(digest,eledigest,20);
                }
                hashTypeReleaseIterator(hi);
            } else {
                serverPanic("Unknown object type");
            }
            /* If the key has an expire, add it to the mix */
            if (expiretime != -1) xorDigest(digest,"!!expire!!",10);
            /* We can finally xor the key-val digest to the final digest */
            xorDigest(final,digest,20);
            decrRefCount(keyobj);
        }
        dictReleaseIterator(di);
    }
}

#if defined(USE_JEMALLOC)
void inputCatSds(void *result, const char *str) {
    /* result is actually a (sds *), so re-cast it here */
    sds *info = (sds *)result;
    *info = sdscat(*info, str);
}
#endif

void debugCommand(client *c) {
    if (c->argc == 1) {
        addReplyError(c,"You must specify a subcommand for DEBUG. Try DEBUG HELP for info.");
        return;
    }

    if (!strcasecmp(c->argv[1]->ptr,"help")) {
        void *blenp = addDeferredMultiBulkLength(c);
        int blen = 0;
        blen++; addReplyStatus(c,
        "DEBUG <subcommand> arg arg ... arg. Subcommands:");
        blen++; addReplyStatus(c,
        "segfault -- Crash the server with sigsegv.");
        blen++; addReplyStatus(c,
        "restart  -- Graceful restart: save config, db, restart.");
        blen++; addReplyStatus(c,
        "crash-and-recovery <milliseconds> -- Hard crash and restart after <milliseconds> delay.");
        blen++; addReplyStatus(c,
        "assert   -- Crash by assertion failed.");
        blen++; addReplyStatus(c,
        "reload   -- Save the RDB on disk and reload it back in memory.");
        blen++; addReplyStatus(c,
        "loadaof  -- Flush the AOF buffers on disk and reload the AOF in memory.");
        blen++; addReplyStatus(c,
        "object <key> -- Show low level info about key and associated value.");
        blen++; addReplyStatus(c,
        "sdslen <key> -- Show low level SDS string info representing key and value.");
        blen++; addReplyStatus(c,
        "populate <count> [prefix] -- Create <count> string keys named key:<num>. If a prefix is specified is used instead of the 'key' prefix.");
        blen++; addReplyStatus(c,
        "digest   -- Outputs an hex signature representing the current DB content.");
        blen++; addReplyStatus(c,
        "sleep <seconds> -- Stop the server for <seconds>. Decimals allowed.");
        blen++; addReplyStatus(c,
        "set-active-expire (0|1) -- Setting it to 0 disables expiring keys in background when they are not accessed (otherwise the Redis behavior). Setting it to 1 reenables back the default.");
        blen++; addReplyStatus(c,
        "lua-always-replicate-commands (0|1) -- Setting it to 1 makes Lua replication defaulting to replicating single commands, without the script having to enable effects replication.");
        blen++; addReplyStatus(c,
        "error <string> -- Return a Redis protocol error with <string> as message. Useful for clients unit tests to simulate Redis errors.");
        blen++; addReplyStatus(c,
        "structsize -- Return the size of different Redis core C structures.");
        blen++; addReplyStatus(c,
        "htstats <dbid> -- Return hash table statistics of the specified Redis database.");
        blen++; addReplyStatus(c,
        "jemalloc info  -- Show internal jemalloc statistics.");
        blen++; addReplyStatus(c,
        "jemalloc purge -- Force jemalloc to release unused memory.");
        setDeferredMultiBulkLength(c,blenp,blen);
    } else if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"restart") ||
               !strcasecmp(c->argv[1]->ptr,"crash-and-recover"))
    {
        long long delay = 0;
        if (c->argc >= 3) {
            if (getLongLongFromObjectOrReply(c, c->argv[2], &delay, NULL)
                != C_OK) return;
            if (delay < 0) delay = 0;
        }
        int flags = !strcasecmp(c->argv[1]->ptr,"restart") ?
            (RESTART_SERVER_GRACEFULLY|RESTART_SERVER_CONFIG_REWRITE) :
             RESTART_SERVER_NONE;
        restartServer(flags,delay);
        addReplyError(c,"failed to restart the server. Check server logs.");
    } else if (!strcasecmp(c->argv[1]->ptr,"oom")) {
        void *ptr = zmalloc(ULONG_MAX); /* Should trigger an out of memory. */
        zfree(ptr);
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"assert")) {
        if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
        serverAssertWithInfo(c,c->argv[0],1 == 2);
    } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
        if (rdbSave(server.rdb_filename) != C_OK) {
            addReply(c,shared.err);
            return;
        }
        emptyDb(NULL);
        if (rdbLoad(server.rdb_filename) != C_OK) {
            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }
        serverLog(LL_WARNING,"DB reloaded by DEBUG RELOAD");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        if (server.aof_state == AOF_ON) flushAppendOnlyFile(1);
        emptyDb(NULL);
        if (loadAppendOnlyFile(server.aof_filename) != C_OK) {
            addReply(c,shared.err);
            return;
        }
        server.dirty = 0; /* Prevent AOF / replication */
        serverLog(LL_WARNING,"Append Only File loaded by DEBUG LOADAOF");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"object") && c->argc == 3) {
        dictEntry *de;
        robj *val;
        char *strenc;

