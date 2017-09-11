    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.slowlog_max_len = (unsigned)ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
