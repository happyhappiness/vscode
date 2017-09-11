    }
}

void sentinelPingInstance(sentinelRedisInstance *ri) {
    mstime_t now = mstime();
    mstime_t info_period;
