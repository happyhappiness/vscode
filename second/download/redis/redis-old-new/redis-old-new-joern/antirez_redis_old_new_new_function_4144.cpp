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