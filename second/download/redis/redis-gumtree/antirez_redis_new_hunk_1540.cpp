    redisAssertWithInfo(c,c->argv[3],sdsEncodedObject(c->argv[3]));
    o = c->argv[3];

    if (0) { /* this starts the config_set macros else-if chain. */

    /* Special fields that can't be handled with general macros. */
    config_set_special_field("dbfilename") {
        if (!pathIsBaseName(o->ptr)) {
            addReplyError(c, "dbfilename can't be a path, just a filename");
            return;
        }
        zfree(server.rdb_filename);
        server.rdb_filename = zstrdup(o->ptr);
    } config_set_special_field("requirepass") {
        if (sdslen(o->ptr) > REDIS_AUTHPASS_MAX_LEN) goto badfmt;
        zfree(server.requirepass);
        server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } config_set_special_field("masterauth") {
        zfree(server.masterauth);
        server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } config_set_special_field("maxclients") {
        int orig_value = server.maxclients;

        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 1) goto badfmt;
