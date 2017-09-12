void sentinelSimFailureCrash(void) {
    serverLog(REDIS_WARNING,
        "Sentinel CRASH because of SENTINEL simulate-failure");
    exit(99);
}