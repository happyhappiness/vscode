            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.stop_writes_on_bgsave_err = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-ping-slave-period")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_ping_slave_period = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_timeout = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
