    decrRefCount(cmdobj);
}

void syncCommand(redisClient *c) {
    /* ignore SYNC if already slave or in monitor mode */
    if (c->flags & REDIS_SLAVE) return;
