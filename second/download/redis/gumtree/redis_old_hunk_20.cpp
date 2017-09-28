    }
    loadServerConfigFromString(config);
    sdsfree(config);
}

/*-----------------------------------------------------------------------------
 * CONFIG command for remote configuration
 *----------------------------------------------------------------------------*/

void configSetCommand(redisClient *c) {
    robj *o;
    long long ll;
    redisAssertWithInfo(c,c->argv[2],c->argv[2]->encoding == REDIS_ENCODING_RAW);
    redisAssertWithInfo(c,c->argv[2],c->argv[3]->encoding == REDIS_ENCODING_RAW);
    o = c->argv[3];

    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        zfree(server.rdb_filename);
        server.rdb_filename = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
        if (sdslen(o->ptr) > REDIS_AUTHPASS_MAX_LEN) goto badfmt;
        zfree(server.requirepass);
        server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
