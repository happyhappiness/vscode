
    /* display error stack */
    for (i = 0; i < errors.level; i++) {
        redisLog(REDIS_WARNING, "0x%08lx - %s",
            (unsigned long) errors.offset[i], errors.error[i]);
    }
}
