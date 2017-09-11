
        if (yn == -1) goto badfmt;
        server.rdb_checksum = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll <= 0) goto badfmt;
        server.slave_priority = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
