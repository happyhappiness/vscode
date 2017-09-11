    return REDIS_OK;
}

/* Send a PING to the specified instance and refresh the last_ping_time
 * if it is zero (that is, if we received a pong for the previous ping).
 *
 * On error zero is returned, and we can't consider the PING command
 * queued in the connection. */
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
