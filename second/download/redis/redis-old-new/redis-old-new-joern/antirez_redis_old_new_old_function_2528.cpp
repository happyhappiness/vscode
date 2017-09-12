static void __connect(redisContext **target) {
    *target = blocking_context = (use_unix ?
        redisConnectUnix("/tmp/redis.sock") : redisConnect((char*)"127.0.0.1", 6379));
    if (blocking_context->err) {
        printf("Connection error: %s\n", blocking_context->errstr);
        exit(1);
    }
}