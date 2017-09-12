serverLog(REDIS_WARNING,
                "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                (unsigned long long) myself->configEpoch);