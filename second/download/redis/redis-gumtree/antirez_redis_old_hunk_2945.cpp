    return retval;
}

static void latencyMode(void) {
    redisReply *reply;
    long long start, latency, min, max, tot, count = 0;
