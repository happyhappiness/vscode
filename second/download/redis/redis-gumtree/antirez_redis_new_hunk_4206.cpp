    }
}

/* =========================== Remote Configuration ========================= */

static void configSetCommand(redisClient *c) {
    robj *o = getDecodedObject(c->argv[3]);
    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        zfree(server.dbfilename);
        server.dbfilename = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
        zfree(server.requirepass);
        server.requirepass = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"masterauth")) {
        zfree(server.masterauth);
        server.masterauth = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
        server.maxmemory = strtoll(o->ptr, NULL, 10);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),
            "-ERR not supported CONFIG parameter %s\r\n",
            (char*)c->argv[2]->ptr));
        decrRefCount(o);
        return;
    }
    decrRefCount(o);
    addReply(c,shared.ok);
}

static void configGetCommand(redisClient *c) {
    robj *o = getDecodedObject(c->argv[2]);
    robj *lenobj = createObject(REDIS_STRING,NULL);
    char *pattern = o->ptr;
    int matches = 0;

    addReply(c,lenobj);
    decrRefCount(lenobj);

    if (stringmatch(pattern,"dbfilename",0)) {
        addReplyBulkCString(c,"dbfilename");
        addReplyBulkCString(c,server.dbfilename);
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
        char buf[128];

        snprintf(buf,128,"%llu\n",server.maxmemory);
        addReplyBulkCString(c,"maxmemory");
        addReplyBulkCString(c,buf);
        matches++;
    }
    decrRefCount(o);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
}

static void configCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc != 4) goto badarity;
        configSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"get")) {
        if (c->argc != 3) goto badarity;
        configGetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"resetstat")) {
        if (c->argc != 2) goto badarity;
        server.stat_numcommands = 0;
        server.stat_numconnections = 0;
        server.stat_expiredkeys = 0;
        server.stat_starttime = time(NULL);
        addReply(c,shared.ok);
    } else {
        addReplySds(c,sdscatprintf(sdsempty(),
            "-ERR CONFIG subcommand must be one of GET, SET, RESETSTAT\r\n"));
    }
    return;

badarity:
    addReplySds(c,sdscatprintf(sdsempty(),
        "-ERR Wrong number of arguments for CONFIG %s\r\n",
        (char*) c->argv[1]->ptr));
}

/* ================================= Debugging ============================== */

static void debugCommand(redisClient *c) {
