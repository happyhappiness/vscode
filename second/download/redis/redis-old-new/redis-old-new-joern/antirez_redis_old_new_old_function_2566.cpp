void configGetCommand(redisClient *c) {
    robj *o = c->argv[2];
    void *replylen = addDeferredMultiBulkLength(c);
    char *pattern = o->ptr;
    char buf[128];
    int matches = 0;
    redisAssertWithInfo(c,o,o->encoding == REDIS_ENCODING_RAW);

    if (stringmatch(pattern,"dir",0)) {
        char buf[1024];

        if (getcwd(buf,sizeof(buf)) == NULL)
            buf[0] = '\0';

        addReplyBulkCString(c,"dir");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"dbfilename",0)) {
        addReplyBulkCString(c,"dbfilename");
        addReplyBulkCString(c,server.rdb_filename);
        matches++;
    }
    if (stringmatch(pattern,"requirepass",0)) {
        addReplyBulkCString(c,"requirepass");
        addReplyBulkCString(c,server.requirepass);
        matches++;
    }
    if (stringmatch(pattern,"masterauth",0)) {
        addReplyBulkCString(c,"masterauth");
        addReplyBulkCString(c,server.masterauth);
        matches++;
    }
    if (stringmatch(pattern,"maxmemory",0)) {
        ll2string(buf,sizeof(buf),server.maxmemory);
        addReplyBulkCString(c,"maxmemory");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"maxmemory-policy",0)) {
        char *s;

        switch(server.maxmemory_policy) {
        case REDIS_MAXMEMORY_VOLATILE_LRU: s = "volatile-lru"; break;
        case REDIS_MAXMEMORY_VOLATILE_TTL: s = "volatile-ttl"; break;
        case REDIS_MAXMEMORY_VOLATILE_RANDOM: s = "volatile-random"; break;
        case REDIS_MAXMEMORY_ALLKEYS_LRU: s = "allkeys-lru"; break;
        case REDIS_MAXMEMORY_ALLKEYS_RANDOM: s = "allkeys-random"; break;
        case REDIS_MAXMEMORY_NO_EVICTION: s = "noeviction"; break;
        default: s = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"maxmemory-policy");
        addReplyBulkCString(c,s);
        matches++;
    }
    if (stringmatch(pattern,"maxmemory-samples",0)) {
        ll2string(buf,sizeof(buf),server.maxmemory_samples);
        addReplyBulkCString(c,"maxmemory-samples");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"timeout",0)) {
        ll2string(buf,sizeof(buf),server.maxidletime);
        addReplyBulkCString(c,"timeout");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"appendonly",0)) {
        addReplyBulkCString(c,"appendonly");
        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
        matches++;
    }
    if (stringmatch(pattern,"no-appendfsync-on-rewrite",0)) {
        addReplyBulkCString(c,"no-appendfsync-on-rewrite");
        addReplyBulkCString(c,server.aof_no_fsync_on_rewrite ? "yes" : "no");
        matches++;
    }
    if (stringmatch(pattern,"appendfsync",0)) {
        char *policy;

        switch(server.aof_fsync) {
        case AOF_FSYNC_NO: policy = "no"; break;
        case AOF_FSYNC_EVERYSEC: policy = "everysec"; break;
        case AOF_FSYNC_ALWAYS: policy = "always"; break;
        default: policy = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"appendfsync");
        addReplyBulkCString(c,policy);
        matches++;
    }
    if (stringmatch(pattern,"save",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < server.saveparamslen; j++) {
            buf = sdscatprintf(buf,"%ld %d",
                    server.saveparams[j].seconds,
                    server.saveparams[j].changes);
            if (j != server.saveparamslen-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"save");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"auto-aof-rewrite-percentage",0)) {
        addReplyBulkCString(c,"auto-aof-rewrite-percentage");
        addReplyBulkLongLong(c,server.aof_rewrite_perc);
        matches++;
    }
    if (stringmatch(pattern,"auto-aof-rewrite-min-size",0)) {
        addReplyBulkCString(c,"auto-aof-rewrite-min-size");
        addReplyBulkLongLong(c,server.aof_rewrite_min_size);
        matches++;
    }
    if (stringmatch(pattern,"slave-serve-stale-data",0)) {
        addReplyBulkCString(c,"slave-serve-stale-data");
        addReplyBulkCString(c,server.repl_serve_stale_data ? "yes" : "no");
        matches++;
    }
    if (stringmatch(pattern,"hash-max-zipmap-entries",0)) {
        addReplyBulkCString(c,"hash-max-zipmap-entries");
        addReplyBulkLongLong(c,server.hash_max_zipmap_entries);
        matches++;
    }
    if (stringmatch(pattern,"hash-max-zipmap-value",0)) {
        addReplyBulkCString(c,"hash-max-zipmap-value");
        addReplyBulkLongLong(c,server.hash_max_zipmap_value);
        matches++;
    }
    if (stringmatch(pattern,"list-max-ziplist-entries",0)) {
        addReplyBulkCString(c,"list-max-ziplist-entries");
        addReplyBulkLongLong(c,server.list_max_ziplist_entries);
        matches++;
    }
    if (stringmatch(pattern,"list-max-ziplist-value",0)) {
        addReplyBulkCString(c,"list-max-ziplist-value");
        addReplyBulkLongLong(c,server.list_max_ziplist_value);
        matches++;
    }
    if (stringmatch(pattern,"set-max-intset-entries",0)) {
        addReplyBulkCString(c,"set-max-intset-entries");
        addReplyBulkLongLong(c,server.set_max_intset_entries);
        matches++;
    }
    if (stringmatch(pattern,"zset-max-ziplist-entries",0)) {
        addReplyBulkCString(c,"zset-max-ziplist-entries");
        addReplyBulkLongLong(c,server.zset_max_ziplist_entries);
        matches++;
    }
    if (stringmatch(pattern,"zset-max-ziplist-value",0)) {
        addReplyBulkCString(c,"zset-max-ziplist-value");
        addReplyBulkLongLong(c,server.zset_max_ziplist_value);
        matches++;
    }
    if (stringmatch(pattern,"lua-time-limit",0)) {
        addReplyBulkCString(c,"lua-time-limit");
        addReplyBulkLongLong(c,server.lua_time_limit);
        matches++;
    }
    if (stringmatch(pattern,"slowlog-log-slower-than",0)) {
        addReplyBulkCString(c,"slowlog-log-slower-than");
        addReplyBulkLongLong(c,server.slowlog_log_slower_than);
        matches++;
    }
    if (stringmatch(pattern,"slowlog-max-len",0)) {
        addReplyBulkCString(c,"slowlog-max-len");
        addReplyBulkLongLong(c,server.slowlog_max_len);
        matches++;
    }
    if (stringmatch(pattern,"loglevel",0)) {
        char *s;

        switch(server.verbosity) {
        case REDIS_WARNING: s = "warning"; break;
        case REDIS_VERBOSE: s = "verbose"; break;
        case REDIS_NOTICE: s = "notice"; break;
        case REDIS_DEBUG: s = "debug"; break;
        default: s = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"loglevel");
        addReplyBulkCString(c,s);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}