
        if (yn == -1) goto badfmt;
        server.repl_serve_stale_data = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
