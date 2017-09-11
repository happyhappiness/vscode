    if (clusterGetMaxEpoch() > server.cluster->currentEpoch) {
        server.cluster->currentEpoch = clusterGetMaxEpoch();
    }
    return C_OK;

fmterr:
    serverLog(REDIS_WARNING,
