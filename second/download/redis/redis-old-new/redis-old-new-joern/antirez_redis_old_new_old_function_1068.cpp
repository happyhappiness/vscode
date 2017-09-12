void redisOutOfMemoryHandler(size_t allocation_size) {
    serverLog(REDIS_WARNING,"Out Of Memory allocating %zu bytes!",
        allocation_size);
    redisPanic("Redis aborting for OUT OF MEMORY");
}