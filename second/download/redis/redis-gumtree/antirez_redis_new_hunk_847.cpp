            addReplyError(c,"Node config epoch is already non-zero");
        } else {
            myself->configEpoch = epoch;
            serverLog(LL_WARNING,
                "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                (unsigned long long) myself->configEpoch);

