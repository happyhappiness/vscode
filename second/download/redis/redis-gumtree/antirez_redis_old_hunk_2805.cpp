            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);

    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
