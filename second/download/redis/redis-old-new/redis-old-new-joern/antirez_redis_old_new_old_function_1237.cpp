int sentinelSendPing(sentinelRedisInstance *ri) {
    int retval = redisAsyncCommand(ri->link->cc,
        sentinelPingReplyCallback, ri, "PING");
    if (retval == REDIS_OK) {
        ri->link->pending_commands++;
        /* We update the ping time only if we received the pong for
         * the previous ping, otherwise we are technically waiting
         * since the first ping that did not received a reply. */
        if (ri->link->last_ping_time == 0) ri->link->last_ping_time = mstime();
        return 1;
    } else {
        return 0;
    }
}