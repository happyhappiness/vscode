               (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
    {
        /* PUBLISH hello messages only to masters. */
        char ip[INET6_ADDRSTRLEN];
        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
            char myaddr[128];

            // FIXME: IPv6 will break this due to nested : characters -geoffgarside
            snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
                ip, server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);
            retval = redisAsyncCommand(ri->cc,
                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
