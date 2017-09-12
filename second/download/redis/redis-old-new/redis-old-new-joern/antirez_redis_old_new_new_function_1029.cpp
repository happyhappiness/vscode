void sentinelSimFailureCrash(void) {
    serverLog(LL_WARNING,
        "Sentinel CRASH because of SENTINEL simulate-failure");
    exit(99);
}