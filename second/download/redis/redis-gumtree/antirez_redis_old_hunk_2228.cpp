    /* Format and send the Hello message. */
    snprintf(payload,sizeof(payload),
        "%s,%d,%s,%llu," /* Info about this sentinel. */
        "%s,%s,%d,%lld", /* Info about current master. */
        ip, server.port, server.runid,
        (unsigned long long) sentinel.current_epoch,
        /* --- */
        master->name,master_addr->ip,master_addr->port,
        master->config_epoch);
    retval = redisAsyncCommand(ri->cc,
        sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
            SENTINEL_HELLO_CHANNEL,payload);
