    redisLog(REDIS_WARNING,"Currently unable to failover: %s", msg);
}

/* This function is called if we are a slave node and our master serving
 * a non-zero amount of hash slots is in FAIL state.
 *
