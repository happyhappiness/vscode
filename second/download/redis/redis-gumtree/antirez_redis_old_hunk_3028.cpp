#endif
}

void _redisPanic(char *msg, char *file, int line) {
    redisLog(REDIS_WARNING,"------------------------------------------------");
    redisLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");
