            sentinelPingReplyCallback, NULL, "PING");
        if (retval != REDIS_OK) return;
        ri->pending_commands++;
    } else if ((ri->flags & SRI_MASTER) &&
               (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
    {
        /* PUBLISH hello messages only to masters. */
        char ip[REDIS_IP_STR_LEN];
        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
            char myaddr[REDIS_IP_STR_LEN+128];

            snprintf(myaddr,sizeof(myaddr),"%s,%d,%s,%d",
                ip, server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);
            retval = redisAsyncCommand(ri->cc,
                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
                    SENTINEL_HELLO_CHANNEL,myaddr);
            if (retval != REDIS_OK) return;
            ri->pending_commands++;
        }
