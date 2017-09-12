    blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
}

void blpopCommand(redisClient *c) {
    blockingPopGenericCommand(c,REDIS_HEAD);
}
