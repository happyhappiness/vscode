        addReplyBulkCString(c,s);
        matches++;
    }
    if (stringmatch(pattern,"client-output-buffer-limit",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
            buf = sdscatprintf(buf,"%s %llu %llu %ld",
                    getClientLimitClassName(j),
                    server.client_obuf_limits[j].hard_limit_bytes,
                    server.client_obuf_limits[j].soft_limit_bytes,
                    (long) server.client_obuf_limits[j].soft_limit_seconds);
            if (j != REDIS_CLIENT_LIMIT_NUM_CLASSES-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"client-output-buffer-limit");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}

