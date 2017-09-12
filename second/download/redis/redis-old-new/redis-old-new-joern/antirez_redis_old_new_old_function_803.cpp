void manualFailoverCheckTimeout(void) {
    if (server.cluster->mf_end && server.cluster->mf_end < mstime()) {
        serverLog(REDIS_WARNING,"Manual failover timed out.");
        resetManualFailover();
    }
}