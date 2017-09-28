        refreshGoodSlavesCount();
    } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-max-lag")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.repl_min_slaves_max_lag = ll;
        refreshGoodSlavesCount();
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
        return;
    }
    addReply(c,shared.ok);
