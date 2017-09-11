            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.stop_writes_on_bgsave_err = yn;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
