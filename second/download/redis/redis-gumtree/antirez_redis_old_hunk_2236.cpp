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

