
        if (yn == -1) goto badfmt;
        server.stop_writes_on_bgsave_err = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
