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
                                             NULL : ri->master;

            snprintf(payload,sizeof(payload),
                "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
                "%s,%s,%d,%lld",    /* Info about current master. */
                ip, server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0,
                (unsigned long long) sentinel.current_epoch,
                /* --- */
                master->name,master->addr->ip,master->addr->port,
                master->config_epoch);
            retval = redisAsyncCommand(ri->cc,
                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
                    SENTINEL_HELLO_CHANNEL,payload);
            if (retval != REDIS_OK) return;
            ri->pending_commands++;
        }
