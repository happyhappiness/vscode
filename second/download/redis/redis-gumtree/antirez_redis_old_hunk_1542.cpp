            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.slowlog_max_len = (unsigned)ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
        if (!strcasecmp(o->ptr,"warning")) {
            server.verbosity = REDIS_WARNING;
