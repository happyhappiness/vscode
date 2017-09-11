    o = c->argv[3];

    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        zfree(server.rdb_filename);
        server.rdb_filename = zstrdup(o->ptr);
    } else if (!strcasecmp(c->argv[2]->ptr,"requirepass")) {
