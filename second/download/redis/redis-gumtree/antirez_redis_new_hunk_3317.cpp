    } else if (!strcasecmp(c->argv[2]->ptr,"set-max-intset-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.set_max_intset_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-entries")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.zset_max_ziplist_entries = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.zset_max_ziplist_value = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
