        }
        addReplyBulkCString(c,"save");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"loglevel",0)) {
        char *s;

        switch(server.verbosity) {
        case REDIS_WARNING: s = "warning"; break;
        case REDIS_VERBOSE: s = "verbose"; break;
        case REDIS_NOTICE: s = "notice"; break;
        case REDIS_DEBUG: s = "debug"; break;
        default: s = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"loglevel");
        addReplyBulkCString(c,s);
        matches++;
    }
    if (stringmatch(pattern,"client-output-buffer-limit",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++) {
            buf = sdscatprintf(buf,"%s %llu %llu %ld",
                    getClientTypeName(j),
                    server.client_obuf_limits[j].hard_limit_bytes,
                    server.client_obuf_limits[j].soft_limit_bytes,
                    (long) server.client_obuf_limits[j].soft_limit_seconds);
            if (j != REDIS_CLIENT_TYPE_COUNT-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"client-output-buffer-limit");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
