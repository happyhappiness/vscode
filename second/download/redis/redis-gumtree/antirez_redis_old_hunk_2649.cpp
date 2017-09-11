
        if (yn == -1) goto badfmt;
        server.rdb_checksum = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
