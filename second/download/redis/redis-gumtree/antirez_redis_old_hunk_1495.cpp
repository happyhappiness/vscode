void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
    char name[64];

    snprintf(name,sizeof(name),"sentinel-%.8s-%s",server.runid,type);
    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
        "CLIENT SETNAME %s", name) == REDIS_OK)
    {
        ri->pending_commands++;
    }
}

/* Create the async connections for the specified instance if the instance
 * is disconnected. Note that the SRI_DISCONNECTED flag is set even if just
 * one of the two links (commands and pub/sub) is missing. */
void sentinelReconnectInstance(sentinelRedisInstance *ri) {
    if (!(ri->flags & SRI_DISCONNECTED)) return;

    /* Commands connection. */
    if (ri->cc == NULL) {
        ri->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
        if (ri->cc->err) {
            sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
                ri->cc->errstr);
            sentinelKillLink(ri,ri->cc);
        } else {
            ri->cc_conn_time = mstime();
            ri->cc->data = ri;
            redisAeAttach(server.el,ri->cc);
            redisAsyncSetConnectCallback(ri->cc,
                                            sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(ri->cc,
                                            sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,ri->cc);
            sentinelSetClientName(ri,ri->cc,"cmd");

            /* Send a PING ASAP when reconnecting. */
            sentinelSendPing(ri);
        }
    }
    /* Pub / Sub */
    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && ri->pc == NULL) {
        ri->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
        if (ri->pc->err) {
            sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
                ri->pc->errstr);
            sentinelKillLink(ri,ri->pc);
        } else {
            int retval;

            ri->pc_conn_time = mstime();
            ri->pc->data = ri;
            redisAeAttach(server.el,ri->pc);
            redisAsyncSetConnectCallback(ri->pc,
                                            sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(ri->pc,
                                            sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,ri->pc);
            sentinelSetClientName(ri,ri->pc,"pubsub");
            /* Now we subscribe to the Sentinels "Hello" channel. */
            retval = redisAsyncCommand(ri->pc,
                sentinelReceiveHelloMessages, NULL, "SUBSCRIBE %s",
                    SENTINEL_HELLO_CHANNEL);
            if (retval != REDIS_OK) {
                /* If we can't subscribe, the Pub/Sub connection is useless
                 * and we can simply disconnect it and try again. */
                sentinelKillLink(ri,ri->pc);
                return;
            }
        }
    }
    /* Clear the DISCONNECTED flags only if we have both the connections
     * (or just the commands connection if this is a sentinel instance). */
    if (ri->cc && (ri->flags & SRI_SENTINEL || ri->pc))
        ri->flags &= ~SRI_DISCONNECTED;
}

/* ======================== Redis instances pinging  ======================== */
