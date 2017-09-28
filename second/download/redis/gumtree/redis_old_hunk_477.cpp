
            seconds = strtoll(v[j],NULL,10);
            changes = strtoll(v[j+1],NULL,10);
            appendServerSaveParams(seconds, changes);
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-serve-stale-data")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_serve_stale_data = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-read-only")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_slave_ro = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"activerehashing")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.activerehashing = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
        if (chdir((char*)o->ptr) == -1) {
            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hash_max_ziplist_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hash_max_ziplist_value = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.list_max_ziplist_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.list_max_ziplist_value = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"set-max-intset-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.set_max_intset_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.zset_max_ziplist_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.zset_max_ziplist_value = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"hll-sparse-max-bytes")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hll_sparse_max_bytes = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.lua_time_limit = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-log-slower-than")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR) goto badfmt;
        server.slowlog_log_slower_than = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.slowlog_max_len = (unsigned)ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"latency-monitor-threshold")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.latency_monitor_threshold = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
        if (!strcasecmp(o->ptr,"warning")) {
            server.verbosity = REDIS_WARNING;
        } else if (!strcasecmp(o->ptr,"notice")) {
            server.verbosity = REDIS_NOTICE;
        } else if (!strcasecmp(o->ptr,"verbose")) {
            server.verbosity = REDIS_VERBOSE;
        } else if (!strcasecmp(o->ptr,"debug")) {
            server.verbosity = REDIS_DEBUG;
        } else {
            goto badfmt;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"client-output-buffer-limit")) {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);

        /* We need a multiple of 4: <class> <hard> <soft> <soft_seconds> */
        if (vlen % 4) {
            sdsfreesplitres(v,vlen);
