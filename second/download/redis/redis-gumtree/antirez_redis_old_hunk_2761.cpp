
        if (yn == -1) goto badfmt;
        server.repl_serve_stale_data = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
        if (chdir((char*)o->ptr) == -1) {
            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hash_max_zipmap_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-zipmap-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.hash_max_zipmap_value = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.list_max_ziplist_entries = ll;
