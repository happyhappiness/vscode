void sentinelPingInstance(sentinelRedisInstance *ri) {
    mstime_t now = mstime();
    mstime_t info_period;
    int retval;

    /* Return ASAP if we have already a PING or INFO already pending, or
     * in the case the instance is not properly connected. */
    if (ri->flags & SRI_DISCONNECTED) return;

    /* For INFO, PING, PUBLISH that are not critical commands to send we
     * also have a limit of SENTINEL_MAX_PENDING_COMMANDS. We don't
     * want to use a lot of memory just because a link is not working
     * properly (note that anyway there is a redundant protection about this,
     * that is, the link will be disconnected and reconnected if a long
     * timeout condition is detected. */
    if (ri->pending_commands >= SENTINEL_MAX_PENDING_COMMANDS) return;

    /* If this is a slave of a master in O_DOWN condition we start sending
     * it INFO every second, instead of the usual SENTINEL_INFO_PERIOD
     * period. In this state we want to closely monitor slaves in case they
     * are turned into masters by another Sentinel, or by the sysadmin. */
    if ((ri->flags & SRI_SLAVE) &&
        (ri->master->flags & (SRI_O_DOWN|SRI_FAILOVER_IN_PROGRESS))) {
        info_period = 1000;
    } else {
        info_period = SENTINEL_INFO_PERIOD;
    }

    if ((ri->flags & SRI_SENTINEL) == 0 &&
        (ri->info_refresh == 0 ||
        (now - ri->info_refresh) > info_period))
    {
        /* Send INFO to masters and slaves, not sentinels. */
        retval = redisAsyncCommand(ri->cc,
            sentinelInfoReplyCallback, NULL, "INFO");
        if (retval != REDIS_OK) return;
        ri->pending_commands++;
    } else if ((now - ri->last_pong_time) > SENTINEL_PING_PERIOD) {
        /* Send PING to all the three kinds of instances. */
        retval = redisAsyncCommand(ri->cc,
            sentinelPingReplyCallback, NULL, "PING");
        if (retval != REDIS_OK) return;
        ri->pending_commands++;
    } else if ((ri->flags & SRI_SENTINEL) == 0 &&
               (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
    {
        /* PUBLISH hello messages to masters and slaves. */
        char ip[REDIS_IP_STR_LEN];
        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
            char payload[REDIS_IP_STR_LEN+1024];
            sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                             ri : ri->master;
            sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);

            snprintf(payload,sizeof(payload),
                "%s,%d,%s,%llu," /* Info about this sentinel. */
                "%s,%s,%d,%lld",    /* Info about current master. */
                ip, server.port, server.runid,
                (unsigned long long) sentinel.current_epoch,
                /* --- */
                master->name,master_addr->ip,master_addr->port,
                master->config_epoch);
            retval = redisAsyncCommand(ri->cc,
                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
                    SENTINEL_HELLO_CHANNEL,payload);
            if (retval != REDIS_OK) return;
            ri->pending_commands++;
        }
    }
}