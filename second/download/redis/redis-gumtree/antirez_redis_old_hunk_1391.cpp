
/* Crash because of user request via SENTINEL simulate-failure command. */
void sentinelSimFailureCrash(void) {
    redisLog(REDIS_WARNING,
        "Sentinel CRASH because of SENTINEL simulate-failure");
    exit(99);
}
