               (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
    {
        /* PUBLISH hello messages only to masters. */
        struct sockaddr_in sa;
        socklen_t salen = sizeof(sa);

        if (getsockname(ri->cc->c.fd,(struct sockaddr*)&sa,&salen) != -1) {
            char myaddr[128];

            snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
                inet_ntoa(sa.sin_addr), server.port, server.runid,
                (ri->flags & SRI_CAN_FAILOVER) != 0);
            retval = redisAsyncCommand(ri->cc,
                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
