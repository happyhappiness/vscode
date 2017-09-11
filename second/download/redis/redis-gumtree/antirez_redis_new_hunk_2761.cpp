
        if (yn == -1) goto badfmt;
        server.repl_serve_stale_data = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-read-only")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_slave_ro = yn;
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
