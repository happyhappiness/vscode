               (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
    {
        /* PUBLISH hello messages to masters and slaves. */
        sentinelSendHello(ri);
    }
}

