    snprintf(payload,sizeof(payload),
        "%s,%d,%s,%llu," /* Info about this sentinel. */
        "%s,%s,%d,%llu", /* Info about current master. */
        announce_ip, announce_port, sentinel.myid,
        (unsigned long long) sentinel.current_epoch,
        /* --- */
        master->name,master_addr->ip,master_addr->port,
        (unsigned long long) master->config_epoch);
    retval = redisAsyncCommand(ri->link->cc,
        sentinelPublishReplyCallback, ri, "PUBLISH %s %s",
            SENTINEL_HELLO_CHANNEL,payload);
    if (retval != REDIS_OK) return REDIS_ERR;
    ri->link->pending_commands++;
    return REDIS_OK;
}

