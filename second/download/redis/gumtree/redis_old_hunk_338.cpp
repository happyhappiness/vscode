badfmt: /* Bad format errors */
    if (changes) sentinelFlushConfig();
    addReplyErrorFormat(c,"Invalid argument '%s' for SENTINEL SET '%s'",
            value, option);
}

/* ===================== SENTINEL availability checks ======================= */

/* Is this instance down from our point of view? */
void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
    mstime_t elapsed = mstime() - ri->last_avail_time;

    /* Check if we are in need for a reconnection of one of the 
     * links, because we are detecting low activity.
     *
     * 1) Check if the command link seems connected, was connected not less
     *    than SENTINEL_MIN_LINK_RECONNECT_PERIOD, but still we have an
     *    idle time that is greater than down_after_period / 2 seconds. */
    if (ri->cc &&
        (mstime() - ri->cc_conn_time) > SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
        (mstime() - ri->last_pong_time) > (ri->down_after_period/2))
    {
        sentinelKillLink(ri,ri->cc);
    }

    /* 2) Check if the pubsub link seems connected, was connected not less
