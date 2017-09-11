    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_timeout = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
