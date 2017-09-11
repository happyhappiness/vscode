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
