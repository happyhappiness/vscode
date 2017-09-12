            appendServerSaveParams(seconds, changes);
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-serve-stale-data")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_serve_stale_data = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
