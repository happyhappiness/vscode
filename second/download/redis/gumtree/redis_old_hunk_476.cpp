}

/*-----------------------------------------------------------------------------
 * CONFIG SET implementation
 *----------------------------------------------------------------------------*/

void configSetCommand(redisClient *c) {
    robj *o;
    long long ll;
    int err;
    redisAssertWithInfo(c,c->argv[2],sdsEncodedObject(c->argv[2]));
    redisAssertWithInfo(c,c->argv[3],sdsEncodedObject(c->argv[3]));
    o = c->argv[3];

    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        if (!pathIsBaseName(o->ptr)) {
            addReplyError(c, "dbfilename can't be a path, just a filename");
            return;
        }
        zfree(server.rdb_filename);
        server.rdb_filename = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
        if (sdslen(o->ptr) > REDIS_AUTHPASS_MAX_LEN) goto badfmt;
        zfree(server.requirepass);
        server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } else if (!strcasecmp(c->argv[2]->ptr,"masterauth")) {
        zfree(server.masterauth);
        server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
        ll = memtoll(o->ptr,&err);
        if (err || ll < 0) goto badfmt;
        server.maxmemory = ll;
        if (server.maxmemory) {
            if (server.maxmemory < zmalloc_used_memory()) {
                redisLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
            }
            freeMemoryIfNeeded();
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"maxclients")) {
        int orig_value = server.maxclients;

        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 1) goto badfmt;

        /* Try to check if the OS is capable of supporting so many FDs. */
        server.maxclients = ll;
        if (ll > orig_value) {
            adjustOpenFilesLimit();
            if (server.maxclients != ll) {
                addReplyErrorFormat(c,"The operating system is not able to handle the specified number of clients, try with %d", server.maxclients);
                server.maxclients = orig_value;
                return;
            }
            if ((unsigned int) aeGetSetSize(server.el) <
                server.maxclients + REDIS_EVENTLOOP_FDSET_INCR)
            {
                if (aeResizeSetSize(server.el,
                    server.maxclients + REDIS_EVENTLOOP_FDSET_INCR) == AE_ERR)
                {
                    addReplyError(c,"The event loop API used by Redis is not able to handle the specified number of clients");
                    server.maxclients = orig_value;
                    return;
                }
            }
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"hz")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hz = ll;
        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-policy")) {
        if (!strcasecmp(o->ptr,"volatile-lru")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
        } else if (!strcasecmp(o->ptr,"volatile-random")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_RANDOM;
        } else if (!strcasecmp(o->ptr,"volatile-ttl")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_TTL;
        } else if (!strcasecmp(o->ptr,"allkeys-lru")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_LRU;
        } else if (!strcasecmp(o->ptr,"allkeys-random")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_ALLKEYS_RANDOM;
        } else if (!strcasecmp(o->ptr,"noeviction")) {
            server.maxmemory_policy = REDIS_MAXMEMORY_NO_EVICTION;
        } else {
            goto badfmt;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-samples")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll <= 0) goto badfmt;
        server.maxmemory_samples = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0 || ll > LONG_MAX) goto badfmt;
        server.maxidletime = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"tcp-keepalive")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0 || ll > INT_MAX) goto badfmt;
        server.tcpkeepalive = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"appendfsync")) {
        if (!strcasecmp(o->ptr,"no")) {
            server.aof_fsync = AOF_FSYNC_NO;
        } else if (!strcasecmp(o->ptr,"everysec")) {
            server.aof_fsync = AOF_FSYNC_EVERYSEC;
        } else if (!strcasecmp(o->ptr,"always")) {
            server.aof_fsync = AOF_FSYNC_ALWAYS;
        } else {
            goto badfmt;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"no-appendfsync-on-rewrite")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.aof_no_fsync_on_rewrite = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
        int enable = yesnotoi(o->ptr);

        if (enable == -1) goto badfmt;
        if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
            stopAppendOnly();
        } else if (enable && server.aof_state == REDIS_AOF_OFF) {
            if (startAppendOnly() == REDIS_ERR) {
                addReplyError(c,
                    "Unable to turn on AOF. Check server logs.");
                return;
            }
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-percentage")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.aof_rewrite_perc = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-min-size")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.aof_rewrite_min_size = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"aof-rewrite-incremental-fsync")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.aof_rewrite_incremental_fsync = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"aof-load-truncated")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.aof_load_truncated = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);

        /* Perform sanity check before setting the new config:
         * - Even number of args
         * - Seconds >= 1, changes >= 0 */
