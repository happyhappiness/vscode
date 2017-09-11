            enableWatchdog(ll);
        else
            disableWatchdog();
    } else if (!strcasecmp(c->argv[2]->ptr,"rdbcompression")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.rdb_compression = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"rdbchecksum")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.rdb_checksum = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
