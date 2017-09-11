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
