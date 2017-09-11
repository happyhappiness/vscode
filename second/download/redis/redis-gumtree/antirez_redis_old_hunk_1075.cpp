    if (clusterGetMaxEpoch() > server.cluster->currentEpoch) {
        server.cluster->currentEpoch = clusterGetMaxEpoch();
    }
    return REDIS_OK;

fmterr:
    serverLog(REDIS_WARNING,
