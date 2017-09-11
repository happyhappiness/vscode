    return REDIS_OK;
}

/* Send a PING to the specified instance and refresh the act_ping_time
 * if it is zero (that is, if we received a pong for the previous ping).
 *
 * On error zero is returned, and we can't consider the PING command
 * queued in the connection. */
int sentinelSendPing(sentinelRedisInstance *ri) {
    static unsigned long long counters[256];
    static time_t last;
    // printf("(%lld) PING %s\n", mstime(), sentinelGetInstanceTypeString(ri));
    counters[ri->flags & (SRI_SLAVE|SRI_MASTER|SRI_SENTINEL)]++;
    if (time(NULL)-last >= 5) {
        printf("slave: %llu master: %llu sentinel: %llu\n",
            counters[SRI_SLAVE], counters[SRI_MASTER], counters[SRI_SENTINEL]);
        last = time(NULL);
    }
    int retval = redisAsyncCommand(ri->link->cc,
        sentinelPingReplyCallback, ri, "PING");
    if (retval == REDIS_OK) {
        ri->link->pending_commands++;
        ri->link->last_ping_time = mstime();
        /* We update the active ping time only if we received the pong for
         * the previous ping, otherwise we are technically waiting since the
         * first ping that did not received a reply. */
        if (ri->link->act_ping_time == 0)
            ri->link->act_ping_time = ri->link->last_ping_time;
        return 1;
    } else {
        return 0;
