    } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.lua_time_limit = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-log-slower-than")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR) goto badfmt;
        server.slowlog_log_slower_than = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.slowlog_max_len = (unsigned)ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
