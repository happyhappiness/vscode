    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.zset_max_ziplist_value = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.lua_time_limit = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
